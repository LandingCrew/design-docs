# Error Handling & Serialization

**Subsystem:** Core Engine - Error Management & Data Persistence
**Owner:** Engine Team
**Dependencies:** Game Loop, Resource Management, ECS
**Status:** Design Phase

---

## Overview

The Error Handling System provides robust crash recovery, logging, and graceful degradation, while the Serialization System handles save/load functionality with version migration and integrity validation.

**Core Principles:**
- **Fail Gracefully**: Never crash without saving player progress
- **Detailed Logging**: Track all errors for debugging
- **Version Migration**: Support loading old save files
- **Integrity Validation**: Detect corrupted data
- **Async Serialization**: Never block the main thread

---

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                  Error Handling System                       │
│  - Exception handling & logging                              │
│  - Crash detection & recovery                                │
│  - Auto-save on error                                        │
│  - Safe mode for corrupt data                                │
└─────────────────────────────────────────────────────────────┘
                              ↕
┌──────────────┬──────────────┬──────────────┬────────────────┐
│  Logger      │  Exception   │  Crash       │  Safe Mode     │
│  System      │  Handler     │  Logger      │  Manager       │
│              │              │              │                │
│  - Async     │  - SEH/Sig   │  - Stack     │  - Fallback    │
│  - Rotating  │  - Recovery  │    Trace     │  - Validation  │
│  - Category  │  - Hooks     │  - Symbols   │  - Repair      │
└──────────────┴──────────────┴──────────────┴────────────────┘
                              ↕
┌─────────────────────────────────────────────────────────────┐
│                 Serialization System                         │
│  - Save/load framework                                       │
│  - Version migration                                         │
│  - Compression & encryption                                  │
│  - Integrity validation                                      │
└─────────────────────────────────────────────────────────────┘
```

---

# PART 1: ERROR HANDLING

## Logging System

### Logger Architecture

```cpp
// Logger.h

enum class LogLevel {
    TRACE,      // Verbose debugging
    DEBUG,      // Development info
    INFO,       // Normal runtime info
    WARNING,    // Recoverable issues
    ERROR,      // Serious errors
    FATAL       // Unrecoverable errors
};

class Logger {
public:
    // Initialize logger
    void Initialize(const char* logFilePath, LogLevel minLevel = LogLevel::INFO) {
        this->logFilePath = logFilePath;
        this->minLevel = minLevel;

        // Open log file
        logFile = fopen(logFilePath, "a");
        if (!logFile) {
            fprintf(stderr, "Failed to open log file: %s\n", logFilePath);
        }

        // Start async logging thread
        loggingThread = std::thread([this]() { LoggingThreadFunc(); });

        // Write session header
        Log(LogLevel::INFO, "System", "=== Logging session started ===");
        Log(LogLevel::INFO, "System", "Build: %s", GetBuildVersion());
        Log(LogLevel::INFO, "System", "Platform: %s", GetPlatformName());
    }

    // Log message (thread-safe)
    void Log(LogLevel level, const char* category, const char* format, ...) {
        if (level < minLevel) return;

        // Format message
        va_list args;
        va_start(args, format);
        char message[MAX_LOG_MESSAGE];
        vsnprintf(message, MAX_LOG_MESSAGE, format, args);
        va_end(args);

        // Create log entry
        LogEntry entry{
            level,
            category,
            message,
            GetCurrentTime(),
            std::this_thread::get_id()
        };

        // Queue for async writing
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            logQueue.push(entry);
        }
        queueCV.notify_one();

        // Fire log event
        DispatchEvent(ErrorAPI::LogEvent{level, category, message});

        // Also write to console if error/fatal
        if (level >= LogLevel::ERROR) {
            fprintf(stderr, "[%s] %s: %s\n",
                   GetLevelName(level), category, message);
        }
    }

    // Convenience methods
    void Trace(const char* category, const char* format, ...) {
        va_list args;
        va_start(args, format);
        LogV(LogLevel::TRACE, category, format, args);
        va_end(args);
    }

    void Debug(const char* category, const char* format, ...) {
        va_list args;
        va_start(args, format);
        LogV(LogLevel::DEBUG, category, format, args);
        va_end(args);
    }

    void Info(const char* category, const char* format, ...) {
        va_list args;
        va_start(args, format);
        LogV(LogLevel::INFO, category, format, args);
        va_end(args);
    }

    void Warning(const char* category, const char* format, ...) {
        va_list args;
        va_start(args, format);
        LogV(LogLevel::WARNING, category, format, args);
        va_end(args);
    }

    void Error(const char* category, const char* format, ...) {
        va_list args;
        va_start(args, format);
        LogV(LogLevel::ERROR, category, format, args);
        va_end(args);
    }

    void Fatal(const char* category, const char* format, ...) {
        va_list args;
        va_start(args, format);
        LogV(LogLevel::FATAL, category, format, args);
        va_end(args);
    }

    // Flush logs to disk (for crash recovery)
    void Flush() {
        if (logFile) {
            fflush(logFile);
        }
    }

    void Shutdown() {
        Log(LogLevel::INFO, "System", "=== Logging session ended ===");

        // Stop logging thread
        isRunning = false;
        queueCV.notify_one();

        if (loggingThread.joinable()) {
            loggingThread.join();
        }

        // Close log file
        if (logFile) {
            fclose(logFile);
            logFile = nullptr;
        }
    }

private:
    struct LogEntry {
        LogLevel level;
        const char* category;
        std::string message;
        double timestamp;
        std::thread::id threadId;
    };

    const char* logFilePath;
    FILE* logFile = nullptr;
    LogLevel minLevel;

    // Async logging
    std::queue<LogEntry> logQueue;
    std::mutex queueMutex;
    std::condition_variable queueCV;
    std::thread loggingThread;
    std::atomic<bool> isRunning{true};

    static const int MAX_LOG_MESSAGE = 1024;

    void LoggingThreadFunc() {
        // BACKGROUND THREAD: Async log writing

        while (isRunning) {
            std::unique_lock<std::mutex> lock(queueMutex);

            // Wait for log entries
            queueCV.wait(lock, [this]() {
                return !logQueue.empty() || !isRunning;
            });

            // Process all queued entries
            while (!logQueue.empty()) {
                LogEntry entry = logQueue.front();
                logQueue.pop();

                lock.unlock();

                // Write to file
                WriteLogEntry(entry);

                lock.lock();
            }
        }
    }

    void WriteLogEntry(const LogEntry& entry) {
        if (!logFile) return;

        // Format: [Timestamp] [Level] [Thread] Category: Message
        fprintf(logFile, "[%.3f] [%s] [T:%lu] %s: %s\n",
               entry.timestamp,
               GetLevelName(entry.level),
               std::hash<std::thread::id>{}(entry.threadId),
               entry.category,
               entry.message.c_str());

        // Flush after errors
        if (entry.level >= LogLevel::ERROR) {
            fflush(logFile);
        }
    }

    const char* GetLevelName(LogLevel level) {
        switch (level) {
            case LogLevel::TRACE: return "TRACE";
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARN";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::FATAL: return "FATAL";
            default: return "UNKNOWN";
        }
    }

    void LogV(LogLevel level, const char* category, const char* format, va_list args) {
        if (level < minLevel) return;

        char message[MAX_LOG_MESSAGE];
        vsnprintf(message, MAX_LOG_MESSAGE, format, args);

        Log(level, category, "%s", message);
    }
};

// Global logger instance
Logger* g_Logger = nullptr;

Logger* GetLogger() {
    return g_Logger;
}
```

---

## Crash Logger System

### Comprehensive Crash Reporter

```cpp
// CrashLogger.h - Inspired by CrashLoggerSSE

/**
 * Production-grade crash logging system that captures:
 * - Exception type and address
 * - Full call stack with symbols
 * - System information (CPU, GPU, memory)
 * - Process state (uptime, loaded modules)
 * - Game state snapshot
 */

class CrashLogger {
public:
    void Initialize() {
        // Set up platform-specific exception handlers
#ifdef _WIN32
        // Windows Structured Exception Handling
        SetUnhandledExceptionFilter(WindowsExceptionHandler);
        _set_purecall_handler(PureCallHandler);
        _set_invalid_parameter_handler(InvalidParameterHandler);
#else
        // Unix signals
        signal(SIGSEGV, UnixSignalHandler);
        signal(SIGABRT, UnixSignalHandler);
        signal(SIGFPE, UnixSignalHandler);
        signal(SIGILL, UnixSignalHandler);
#endif

        // Initialize symbol handler for stack traces
        InitializeSymbolHandler();

        GetLogger()->Info("CrashLogger", "Crash logger initialized");
    }

    // Platform-specific exception filter
    static LONG WINAPI WindowsExceptionHandler(EXCEPTION_POINTERS* exceptionInfo) {
        // This runs in the crashing thread

        CrashReport report = GenerateCrashReport(exceptionInfo);
        WriteCrashLog(report);

        // Emergency save
        EmergencySave();

        // Fire crash event (if hook system still alive)
        try {
            DispatchEvent(ErrorAPI::CrashEvent{report.exceptionType});
        } catch (...) {
            // Hook system may be corrupted, ignore
        }

        // Continue to default handler (terminate)
        return EXCEPTION_CONTINUE_SEARCH;
    }

private:
    struct CrashReport {
        // Exception Info
        const char* exceptionType;
        uint64_t exceptionAddress;
        uint32_t exceptionCode;
        uint32_t exceptionFlags;
        uint32_t threadId;
        const char* moduleName;
        uint64_t moduleOffset;

        // Access Violation Details (if applicable)
        bool isAccessViolation;
        bool wasRead;           // true = read, false = write
        uint64_t accessAddress;

        // Stack Trace
        std::vector<StackFrame> callStack;

        // System Info
        SystemInfo system;

        // Process Info
        ProcessInfo process;

        // Game State
        GameStateSnapshot gameState;

        // Loaded Modules (DLLs/plugins)
        std::vector<ModuleInfo> loadedModules;
    };

    struct StackFrame {
        uint64_t address;
        const char* moduleName;
        uint64_t moduleOffset;
        const char* symbolName;     // Function name
        const char* fileName;       // Source file
        uint32_t lineNumber;        // Source line
    };

    struct SystemInfo {
        const char* osName;         // "Microsoft Windows 10 Pro"
        const char* osVersion;      // "v10.0.19045"
        const char* cpuName;        // "AMD Ryzen 7 3700X"
        uint32_t cpuCores;          // 8 physical
        uint32_t logicalCores;      // 16 logical
        const char* gpuName;        // "NVIDIA GeForce RTX 5090"
        uint64_t physicalMemory;    // Total RAM
        uint64_t virtualMemory;     // Total virtual
    };

    struct ProcessInfo {
        uint32_t processId;
        uint32_t threadId;
        uint64_t uptimeMs;          // Process uptime
        const char* workingDir;
        const char* commandLine;
        const char* executableMD5;
        uint64_t executableSize;
        const char* executableModTime;
        bool isElevated;

        // Memory usage
        uint64_t workingSetMB;
        uint64_t privateMB;
        uint64_t peakWorkingSetMB;
        uint64_t pageFaults;

        // GPU memory
        uint64_t gpuMemoryUsedMB;
        uint64_t gpuMemoryTotalMB;
    };

    struct GameStateSnapshot {
        const char* currentLevel;
        FVector playerPosition;
        float playtimeSeconds;
        uint32_t characterLevel;
        uint32_t activeMods;
        uint32_t loadedPlugins;
        const char* lastModAction;  // "Casting spell", "Loading cell", etc.
    };

    struct ModuleInfo {
        const char* name;
        uint64_t baseAddress;
        uint64_t size;
        const char* version;
        const char* path;
    };

    static CrashReport GenerateCrashReport(EXCEPTION_POINTERS* exceptionInfo) {
        CrashReport report{};

        // Exception info
        EXCEPTION_RECORD* record = exceptionInfo->ExceptionRecord;
        CONTEXT* context = exceptionInfo->ContextRecord;

        report.exceptionCode = record->ExceptionCode;
        report.exceptionAddress = reinterpret_cast<uint64_t>(record->ExceptionAddress);
        report.exceptionFlags = record->ExceptionFlags;
        report.threadId = GetCurrentThreadId();

        // Exception type string
        report.exceptionType = GetExceptionName(record->ExceptionCode);

        // Module info for crash location
        report.moduleName = GetModuleNameForAddress(report.exceptionAddress);
        report.moduleOffset = GetModuleOffset(report.exceptionAddress);

        // Access violation details
        if (record->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {
            report.isAccessViolation = true;
            report.wasRead = (record->ExceptionInformation[0] == 0);
            report.accessAddress = record->ExceptionInformation[1];
        }

        // Capture call stack
        report.callStack = CaptureCallStack(context);

        // System info
        report.system = CaptureSystemInfo();

        // Process info
        report.process = CaptureProcessInfo();

        // Game state
        report.gameState = CaptureGameState();

        // Loaded modules
        report.loadedModules = EnumerateLoadedModules();

        return report;
    }

    static void WriteCrashLog(const CrashReport& report) {
        // Generate crash log filename
        char filename[256];
        time_t now = time(nullptr);
        struct tm* t = localtime(&now);
        snprintf(filename, sizeof(filename),
                "Logs/crash-%04d-%02d-%02d_%02d-%02d-%02d.log",
                t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                t->tm_hour, t->tm_min, t->tm_sec);

        FILE* f = fopen(filename, "w");
        if (!f) return;

        // Write crash header
        fprintf(f, "CRASH TIME: %04d-%02d-%02d %02d:%02d:%02d\n",
                t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                t->tm_hour, t->tm_min, t->tm_sec);
        fprintf(f, "Game v%s\n", GetGameVersion());
        fprintf(f, "CrashLogger v%s\n\n", CRASH_LOGGER_VERSION);

        // Exception details
        fprintf(f, "Unhandled exception \"%s\" at 0x%016llX %s+%06llX",
                report.exceptionType,
                report.exceptionAddress,
                report.moduleName,
                report.moduleOffset);

        if (report.callStack.size() > 0) {
            auto& topFrame = report.callStack[0];
            if (topFrame.symbolName) {
                fprintf(f, " %s", topFrame.symbolName);
            }
            if (topFrame.fileName && topFrame.lineNumber > 0) {
                fprintf(f, " (%s:%d)", topFrame.fileName, topFrame.lineNumber);
            }
        }
        fprintf(f, "\n");

        // Exception flags
        fprintf(f, "Exception Flags: 0x%08X (%s)\n",
                report.exceptionFlags,
                report.exceptionFlags == 0 ? "Continuable" : "Non-Continuable");

        fprintf(f, "Exception Thread ID: %u\n", report.threadId);

        // Access violation details
        if (report.isAccessViolation) {
            fprintf(f, "Access Violation: Tried to %s memory at 0x%016llX\n",
                    report.wasRead ? "read" : "write",
                    report.accessAddress);
        }

        fprintf(f, "\n");

        // Process info
        fprintf(f, "PROCESS INFO:\n");
        fprintf(f, "Process ID: %u\n", report.process.processId);
        fprintf(f, "Crash Thread ID: %u\n", report.threadId);
        fprintf(f, "Process Uptime: %02llu:%02llu:%02llu (%llums)\n",
                report.process.uptimeMs / 3600000,
                (report.process.uptimeMs / 60000) % 60,
                (report.process.uptimeMs / 1000) % 60,
                report.process.uptimeMs);
        fprintf(f, "Working Directory: %s\n", report.process.workingDir);
        fprintf(f, "Command Line: %s\n", report.process.commandLine);
        fprintf(f, "Executable MD5: %s\n", report.process.executableMD5);
        fprintf(f, "Executable Size: %llu bytes\n", report.process.executableSize);
        fprintf(f, "Executable Modified: %s\n", report.process.executableModTime);
        fprintf(f, "Elevated: %s\n\n", report.process.isElevated ? "Yes" : "No");

        // System specs
        fprintf(f, "SYSTEM SPECS:\n");
        fprintf(f, "OS: %s %s\n", report.system.osName, report.system.osVersion);
        fprintf(f, "CPU: %s\n", report.system.cpuName);
        fprintf(f, "CPU Cores: %u logical, %u physical\n",
                report.system.logicalCores, report.system.cpuCores);
        fprintf(f, "GPU: %s\n", report.system.gpuName);
        fprintf(f, "PHYSICAL MEMORY: %.2f GB/%.2f GB\n",
                report.process.workingSetMB / 1024.0,
                report.system.physicalMemory / 1024.0 / 1024.0 / 1024.0);
        fprintf(f, "VIRTUAL MEMORY: %.2f GB/%.2f GB\n",
                report.process.privateMB / 1024.0,
                report.system.virtualMemory / 1024.0 / 1024.0 / 1024.0);
        fprintf(f, "PROCESS MEMORY: Working Set: %.2f MB, Private: %.2f MB, Peak: %.2f MB\n",
                report.process.workingSetMB,
                report.process.privateMB,
                report.process.peakWorkingSetMB);
        fprintf(f, "PAGE FAULTS: %llu\n", report.process.pageFaults);
        fprintf(f, "GPU MEMORY: %.2f/%.2f GB\n\n",
                report.process.gpuMemoryUsedMB / 1024.0,
                report.process.gpuMemoryTotalMB / 1024.0);

        // Game state
        fprintf(f, "GAME STATE:\n");
        fprintf(f, "Current Level: %s\n", report.gameState.currentLevel);
        fprintf(f, "Player Position: (%.1f, %.1f, %.1f)\n",
                report.gameState.playerPosition.x,
                report.gameState.playerPosition.y,
                report.gameState.playerPosition.z);
        fprintf(f, "Playtime: %.1f hours\n", report.gameState.playtimeSeconds / 3600.0f);
        fprintf(f, "Character Level: %u\n", report.gameState.characterLevel);
        fprintf(f, "Active Mods: %u\n", report.gameState.activeMods);
        fprintf(f, "Loaded Plugins: %u\n", report.gameState.loadedPlugins);
        if (report.gameState.lastModAction) {
            fprintf(f, "Last Action: %s\n", report.gameState.lastModAction);
        }
        fprintf(f, "\n");

        // Call stack
        fprintf(f, "PROBABLE CALL STACK:\n");
        for (size_t i = 0; i < report.callStack.size(); ++i) {
            const auto& frame = report.callStack[i];

            fprintf(f, "[%2zu] 0x%016llX ", i, frame.address);

            if (frame.moduleName) {
                fprintf(f, "%30s+%06llX ", frame.moduleName, frame.moduleOffset);
            } else {
                fprintf(f, "%39s ", "");
            }

            if (frame.symbolName) {
                fprintf(f, "%s", frame.symbolName);
            }

            if (frame.fileName && frame.lineNumber > 0) {
                fprintf(f, " (%s:%u)", frame.fileName, frame.lineNumber);
            }

            fprintf(f, "\n");
        }
        fprintf(f, "\n");

        // Loaded modules
        fprintf(f, "LOADED MODULES (%zu):\n", report.loadedModules.size());
        for (const auto& module : report.loadedModules) {
            fprintf(f, "0x%016llX - 0x%016llX  %s  %s\n",
                    module.baseAddress,
                    module.baseAddress + module.size,
                    module.name,
                    module.version ? module.version : "");

            if (module.path) {
                fprintf(f, "    %s\n", module.path);
            }
        }
        fprintf(f, "\n");

        // Plugins (if modding system)
        if (GetModManager()) {
            fprintf(f, "ACTIVE PLUGINS:\n");
            for (auto* plugin : GetModManager()->GetActivePlugins()) {
                fprintf(f, "[%s] %s v%s\n",
                        plugin->IsEnabled() ? "X" : " ",
                        plugin->GetName(),
                        plugin->GetVersion());
            }
            fprintf(f, "\n");
        }

        fclose(f);

        // Also write to stderr for debugger
        fprintf(stderr, "\nCRASH DETECTED! Log written to: %s\n", filename);
    }

    static std::vector<StackFrame> CaptureCallStack(CONTEXT* context) {
        std::vector<StackFrame> frames;

#ifdef _WIN32
        STACKFRAME64 stackFrame{};
        stackFrame.AddrPC.Offset = context->Rip;
        stackFrame.AddrPC.Mode = AddrModeFlat;
        stackFrame.AddrFrame.Offset = context->Rbp;
        stackFrame.AddrFrame.Mode = AddrModeFlat;
        stackFrame.AddrStack.Offset = context->Rsp;
        stackFrame.AddrStack.Mode = AddrModeFlat;

        HANDLE process = GetCurrentProcess();
        HANDLE thread = GetCurrentThread();

        // Walk the stack
        for (int i = 0; i < MAX_STACK_FRAMES; ++i) {
            if (!StackWalk64(
                IMAGE_FILE_MACHINE_AMD64,
                process,
                thread,
                &stackFrame,
                context,
                nullptr,
                SymFunctionTableAccess64,
                SymGetModuleBase64,
                nullptr)) {
                break;
            }

            if (stackFrame.AddrPC.Offset == 0) break;

            StackFrame frame{};
            frame.address = stackFrame.AddrPC.Offset;

            // Get module info
            DWORD64 moduleBase = SymGetModuleBase64(process, frame.address);
            if (moduleBase) {
                char moduleName[MAX_PATH];
                if (GetModuleFileNameEx(process, (HMODULE)moduleBase, moduleName, MAX_PATH)) {
                    frame.moduleName = _strdup(PathFindFileName(moduleName));
                    frame.moduleOffset = frame.address - moduleBase;
                }
            }

            // Get symbol info
            char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
            SYMBOL_INFO* symbol = (SYMBOL_INFO*)buffer;
            symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
            symbol->MaxNameLen = MAX_SYM_NAME;

            DWORD64 displacement = 0;
            if (SymFromAddr(process, frame.address, &displacement, symbol)) {
                frame.symbolName = _strdup(symbol->Name);
            }

            // Get source file/line
            IMAGEHLP_LINE64 line{};
            line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
            DWORD lineDisplacement = 0;
            if (SymGetLineFromAddr64(process, frame.address, &lineDisplacement, &line)) {
                frame.fileName = _strdup(line.FileName);
                frame.lineNumber = line.LineNumber;
            }

            frames.push_back(frame);
        }
#endif

        return frames;
    }

    static const char* GetExceptionName(DWORD code) {
        switch (code) {
            case EXCEPTION_ACCESS_VIOLATION: return "EXCEPTION_ACCESS_VIOLATION";
            case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
            case EXCEPTION_BREAKPOINT: return "EXCEPTION_BREAKPOINT";
            case EXCEPTION_DATATYPE_MISALIGNMENT: return "EXCEPTION_DATATYPE_MISALIGNMENT";
            case EXCEPTION_FLT_DIVIDE_BY_ZERO: return "EXCEPTION_FLT_DIVIDE_BY_ZERO";
            case EXCEPTION_FLT_OVERFLOW: return "EXCEPTION_FLT_OVERFLOW";
            case EXCEPTION_FLT_UNDERFLOW: return "EXCEPTION_FLT_UNDERFLOW";
            case EXCEPTION_ILLEGAL_INSTRUCTION: return "EXCEPTION_ILLEGAL_INSTRUCTION";
            case EXCEPTION_IN_PAGE_ERROR: return "EXCEPTION_IN_PAGE_ERROR";
            case EXCEPTION_INT_DIVIDE_BY_ZERO: return "EXCEPTION_INT_DIVIDE_BY_ZERO";
            case EXCEPTION_INT_OVERFLOW: return "EXCEPTION_INT_OVERFLOW";
            case EXCEPTION_INVALID_DISPOSITION: return "EXCEPTION_INVALID_DISPOSITION";
            case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "EXCEPTION_NONCONTINUABLE_EXCEPTION";
            case EXCEPTION_PRIV_INSTRUCTION: return "EXCEPTION_PRIV_INSTRUCTION";
            case EXCEPTION_SINGLE_STEP: return "EXCEPTION_SINGLE_STEP";
            case EXCEPTION_STACK_OVERFLOW: return "EXCEPTION_STACK_OVERFLOW";
            default: return "UNKNOWN_EXCEPTION";
        }
    }

    static void InitializeSymbolHandler() {
#ifdef _WIN32
        HANDLE process = GetCurrentProcess();

        SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);

        if (!SymInitialize(process, nullptr, TRUE)) {
            GetLogger()->Error("CrashLogger", "Failed to initialize symbol handler");
        }
#endif
    }

    static SystemInfo CaptureSystemInfo() {
        // Capture CPU, GPU, OS info
        // ... platform-specific implementation ...
        return SystemInfo{};
    }

    static ProcessInfo CaptureProcessInfo() {
        // Capture process memory, uptime, etc.
        // ... platform-specific implementation ...
        return ProcessInfo{};
    }

    static GameStateSnapshot CaptureGameState() {
        // Capture game-specific state
        GameStateSnapshot snapshot{};

        try {
            if (auto* world = GetWorldManager()) {
                snapshot.currentLevel = world->GetCurrentLevelName();
            }

            if (auto* player = GetPlayerController()) {
                snapshot.playerPosition = player->GetPosition();
                snapshot.characterLevel = player->GetLevel();
            }

            if (auto* modMgr = GetModManager()) {
                snapshot.activeMods = modMgr->GetActiveModCount();
                snapshot.loadedPlugins = modMgr->GetLoadedPluginCount();
            }

            snapshot.playtimeSeconds = GetTotalPlaytime();
            snapshot.lastModAction = GetLastAction();

        } catch (...) {
            // Game state may be corrupted, ignore errors
        }

        return snapshot;
    }

    static std::vector<ModuleInfo> EnumerateLoadedModules() {
        std::vector<ModuleInfo> modules;

#ifdef _WIN32
        HANDLE process = GetCurrentProcess();
        HMODULE moduleHandles[1024];
        DWORD needed;

        if (EnumProcessModules(process, moduleHandles, sizeof(moduleHandles), &needed)) {
            int count = needed / sizeof(HMODULE);

            for (int i = 0; i < count; ++i) {
                ModuleInfo info{};

                char moduleName[MAX_PATH];
                if (GetModuleFileNameEx(process, moduleHandles[i], moduleName, MAX_PATH)) {
                    info.name = _strdup(PathFindFileName(moduleName));
                    info.path = _strdup(moduleName);
                }

                MODULEINFO moduleInfo;
                if (GetModuleInformation(process, moduleHandles[i], &moduleInfo, sizeof(moduleInfo))) {
                    info.baseAddress = reinterpret_cast<uint64_t>(moduleInfo.lpBaseOfDll);
                    info.size = moduleInfo.SizeOfImage;
                }

                // Get version info
                DWORD handle;
                DWORD size = GetFileVersionInfoSize(moduleName, &handle);
                if (size > 0) {
                    std::vector<char> buffer(size);
                    if (GetFileVersionInfo(moduleName, 0, size, buffer.data())) {
                        VS_FIXEDFILEINFO* verInfo;
                        UINT len;
                        if (VerQueryValue(buffer.data(), "\\", (LPVOID*)&verInfo, &len)) {
                            char version[64];
                            snprintf(version, sizeof(version), "%u.%u.%u.%u",
                                    HIWORD(verInfo->dwFileVersionMS),
                                    LOWORD(verInfo->dwFileVersionMS),
                                    HIWORD(verInfo->dwFileVersionLS),
                                    LOWORD(verInfo->dwFileVersionLS));
                            info.version = _strdup(version);
                        }
                    }
                }

                modules.push_back(info);
            }
        }
#endif

        return modules;
    }

    static const int MAX_STACK_FRAMES = 128;
    static const char* CRASH_LOGGER_VERSION = "1.0.0";
};
```

### Integration with Game Loop

```cpp
// GameLoop initialization
void GameLoop::Initialize() {
    // Initialize crash logger FIRST (before anything else)
    crashLogger = new CrashLogger();
    crashLogger->Initialize();

    // Initialize other systems...
    // If they crash during init, we'll get a log
}
```

### Crash Log Analysis Tools

```cpp
// CrashAnalyzer.h - Post-mortem analysis tool

class CrashAnalyzer {
public:
    // Parse crash log and identify likely causes
    struct Analysis {
        const char* likelyCause;        // "Null pointer dereference"
        const char* suspectedModule;    // "OnCue.dll"
        const char* recommendation;     // "Update or disable mod"
        float confidence;               // 0.0-1.0
    };

    Analysis AnalyzeCrashLog(const char* logPath) {
        // Read crash log
        CrashReport report = ParseCrashLog(logPath);

        // Pattern matching for common issues
        if (report.isAccessViolation && report.accessAddress == 0) {
            return Analysis{
                "Null pointer dereference",
                report.moduleName,
                "This is a bug in the code. Contact the mod author.",
                0.95f
            };
        }

        if (report.isAccessViolation && report.accessAddress == 0xFFFFFFFFFFFFFFFF) {
            return Analysis{
                "Use-after-free (accessing freed memory)",
                report.moduleName,
                "This is a memory management bug. Contact the mod author.",
                0.90f
            };
        }

        if (strstr(report.callStack[0].symbolName, "std::_Container_base")) {
            return Analysis{
                "Iterator invalidation (modifying container during iteration)",
                report.moduleName,
                "This is a threading or container bug. Contact the mod author.",
                0.85f
            };
        }

        if (report.exceptionType == "EXCEPTION_STACK_OVERFLOW") {
            return Analysis{
                "Stack overflow (infinite recursion or very deep call stack)",
                report.moduleName,
                "Reduce recursion depth or increase stack size.",
                0.90f
            };
        }

        // Check for mod conflicts in loaded modules
        if (HasKnownConflict(report.loadedModules)) {
            return Analysis{
                "Known mod conflict",
                "Multiple mods",
                "Disable conflicting mods.",
                0.80f
            };
        }

        return Analysis{
            "Unknown cause",
            report.moduleName,
            "Submit crash log to mod author for analysis.",
            0.5f
        };
    }
};
```

---

## Exception Handling

### Exception Strategy

```cpp
// ExceptionHandler.h

/**
 * Exception Handling Strategy:
 *
 * 1. Use exceptions for EXCEPTIONAL cases (not control flow)
 * 2. Catch exceptions at system boundaries
 * 3. Log all exceptions with context
 * 4. Attempt recovery when possible
 * 5. Auto-save before fatal errors
 */

// Base exception class
class GameException : public std::exception {
public:
    GameException(const char* message, const char* category)
        : message(message), category(category) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    const char* GetCategory() const { return category; }

private:
    std::string message;
    const char* category;
};

// Specific exception types
class ResourceLoadException : public GameException {
public:
    ResourceLoadException(const char* path)
        : GameException(
            ("Failed to load resource: " + std::string(path)).c_str(),
            "Resource"
          ),
          path(path) {}

    const char* GetPath() const { return path; }

private:
    const char* path;
};

class SaveFileCorruptException : public GameException {
public:
    SaveFileCorruptException(const char* path, const char* reason)
        : GameException(
            ("Save file corrupted: " + std::string(reason)).c_str(),
            "SaveLoad"
          ),
          path(path) {}

private:
    const char* path;
};

class PhysicsException : public GameException {
public:
    PhysicsException(const char* message)
        : GameException(message, "Physics") {}
};

// Exception handler
class ExceptionHandler {
public:
    // Set exception handlers
    void Initialize() {
        // C++ exception handler
        std::set_terminate([]() {
            OnUnhandledException();
        });

        // Platform-specific signal handlers
#ifdef _WIN32
        SetUnhandledExceptionFilter(WindowsExceptionFilter);
#else
        signal(SIGSEGV, UnixSignalHandler);
        signal(SIGABRT, UnixSignalHandler);
#endif
    }

    // Handle caught exception
    void HandleException(const std::exception& e, const char* context) {
        // Log exception
        GetLogger()->Error("Exception",
            "Exception in %s: %s", context, e.what());

        // Fire exception event
        DispatchEvent(ErrorAPI::ExceptionEvent{
            e.what(), context
        });

        // Attempt recovery based on exception type
        if (auto* ge = dynamic_cast<const GameException*>(&e)) {
            AttemptRecovery(ge);
        } else {
            // Unknown exception, safer to crash
            OnUnhandledException();
        }
    }

    // Safe execution wrapper
    template<typename Func>
    bool TryExecute(Func&& func, const char* context) {
        try {
            func();
            return true;
        } catch (const std::exception& e) {
            HandleException(e, context);
            return false;
        }
    }

private:
    void AttemptRecovery(const GameException* e) {
        const char* category = e->GetCategory();

        if (strcmp(category, "Resource") == 0) {
            // Resource load failed, use fallback
            GetLogger()->Warning("Recovery",
                "Using fallback resource for failed load");
            // ... load fallback resource ...

        } else if (strcmp(category, "SaveLoad") == 0) {
            // Save file corrupted, enter safe mode
            GetLogger()->Warning("Recovery",
                "Save file corrupted, entering safe mode");
            EnterSafeMode();

        } else if (strcmp(category, "Physics") == 0) {
            // Physics error, reset physics state
            GetLogger()->Warning("Recovery",
                "Physics error, resetting simulation");
            GetPhysicsSystem()->Reset();

        } else {
            // Unknown error, can't recover
            OnUnhandledException();
        }
    }

    static void OnUnhandledException() {
        // Last resort: auto-save and crash gracefully

        GetLogger()->Fatal("Exception", "Unhandled exception, triggering crash recovery");

        // Flush logs
        GetLogger()->Flush();

        // Auto-save (emergency)
        EmergencySave();

        // Generate crash report
        GenerateCrashReport();

        // Fire crash event
        DispatchEvent(ErrorAPI::CrashEvent{
            "Unhandled exception"
        });

        // Exit
        std::abort();
    }

    static void EmergencySave() {
        try {
            auto* saveSystem = GetSaveSystem();
            if (saveSystem) {
                GetLogger()->Info("Crash", "Attempting emergency save...");
                saveSystem->QuickSave("_emergency");
                GetLogger()->Info("Crash", "Emergency save completed");
            }
        } catch (...) {
            GetLogger()->Error("Crash", "Emergency save failed");
        }
    }

    static void GenerateCrashReport() {
        // Generate crash dump with stack trace
        // ... platform-specific implementation ...
    }
};
```

---

## Crash Recovery

### Auto-Save on Error

```cpp
// CrashRecovery.h

class CrashRecoveryManager {
public:
    void Initialize() {
        // Load recovery settings
        autoSaveOnError = configManager->Get("System", "AutoSaveOnError", true);
        emergencySaveInterval = configManager->Get("System", "EmergencySaveInterval", 5.0f);

        // Start monitoring
        StartMonitoring();
    }

    // Called when error detected
    void OnErrorDetected(LogLevel level, const char* message) {
        if (level < LogLevel::ERROR) return;

        errorCount++;
        lastErrorTime = GetCurrentTime();

        // Trigger auto-save after threshold
        if (errorCount >= ERROR_THRESHOLD) {
            GetLogger()->Warning("CrashRecovery",
                "Error threshold reached (%d errors), triggering auto-save",
                errorCount);

            TriggerEmergencySave();
            errorCount = 0;  // Reset counter
        }
    }

    // Called on crash
    void OnCrash(const char* reason) {
        GetLogger()->Fatal("CrashRecovery", "Crash detected: %s", reason);

        // Flush logs immediately
        GetLogger()->Flush();

        // Emergency save
        TriggerEmergencySave();

        // Write crash marker
        WriteCrashMarker(reason);

        // Fire crash event
        DispatchEvent(ErrorAPI::CrashEvent{reason});
    }

    // Check if last session crashed
    bool DidLastSessionCrash() const {
        return FileExists("_crashmarker.txt");
    }

    // Recover from crash
    void RecoverFromCrash() {
        if (!DidLastSessionCrash()) return;

        GetLogger()->Info("CrashRecovery", "Detected previous crash, attempting recovery");

        // Load crash info
        CrashInfo info = LoadCrashMarker();

        // Show recovery UI
        ShowRecoveryDialog(info);

        // Try to load emergency save
        if (FileExists("_emergency.sav")) {
            GetLogger()->Info("CrashRecovery", "Found emergency save, loading...");

            if (GetSaveSystem()->LoadGame("_emergency.sav")) {
                GetLogger()->Info("CrashRecovery", "Recovery successful");
            } else {
                GetLogger()->Error("CrashRecovery", "Failed to load emergency save");
                EnterSafeMode();
            }
        }

        // Delete crash marker
        DeleteFile("_crashmarker.txt");
    }

private:
    bool autoSaveOnError;
    float emergencySaveInterval;
    int errorCount = 0;
    double lastErrorTime = 0.0;
    double lastEmergencySave = 0.0;

    static const int ERROR_THRESHOLD = 10;

    void StartMonitoring() {
        // Monitor for errors in logging system
        GetHookManager()->RegisterPostHandler("Error.Log",
            [this](const ErrorAPI::LogEvent& e) {
                OnErrorDetected(e.level, e.message);
            }
        );
    }

    void TriggerEmergencySave() {
        double currentTime = GetCurrentTime();

        // Rate limit emergency saves
        if (currentTime - lastEmergencySave < emergencySaveInterval) {
            GetLogger()->Debug("CrashRecovery", "Emergency save rate limited");
            return;
        }

        lastEmergencySave = currentTime;

        // Perform emergency save on background thread
        std::thread([this]() {
            try {
                GetSaveSystem()->QuickSave("_emergency");
                GetLogger()->Info("CrashRecovery", "Emergency save completed");
            } catch (const std::exception& e) {
                GetLogger()->Error("CrashRecovery",
                    "Emergency save failed: %s", e.what());
            }
        }).detach();
    }

    void WriteCrashMarker(const char* reason) {
        FILE* f = fopen("_crashmarker.txt", "w");
        if (f) {
            fprintf(f, "Reason: %s\n", reason);
            fprintf(f, "Time: %.3f\n", GetCurrentTime());
            fprintf(f, "Build: %s\n", GetBuildVersion());
            fclose(f);
        }
    }

    struct CrashInfo {
        const char* reason;
        double time;
        const char* buildVersion;
    };

    CrashInfo LoadCrashMarker() {
        // Parse crash marker file
        // ... implementation ...
        return {};
    }

    void ShowRecoveryDialog(const CrashInfo& info) {
        // Show UI dialog with recovery options
        // ... implementation ...
    }
};
```

---

## Safe Mode

### Safe Mode Manager

```cpp
// SafeMode.h

class SafeModeManager {
public:
    // Enter safe mode
    void EnterSafeMode(const char* reason) {
        if (isInSafeMode) return;

        isInSafeMode = true;

        GetLogger()->Warning("SafeMode", "Entering safe mode: %s", reason);

        // Fire safe mode event
        DispatchEvent(ErrorAPI::SafeModeEvent{reason});

        // Disable non-essential systems
        DisableModdedContent();
        DisableGraphicsEffects();
        ResetGameSettings();

        // Show safe mode UI
        ShowSafeModeDialog(reason);
    }

    // Exit safe mode
    void ExitSafeMode() {
        if (!isInSafeMode) return;

        isInSafeMode = false;

        GetLogger()->Info("SafeMode", "Exiting safe mode");

        // Re-enable systems
        LoadGameSettings();
    }

    bool IsInSafeMode() const { return isInSafeMode; }

private:
    bool isInSafeMode = false;

    void DisableModdedContent() {
        // Disable all mods
        GetModManager()->DisableAllMods();

        GetLogger()->Info("SafeMode", "Disabled all mods");
    }

    void DisableGraphicsEffects() {
        // Set graphics to minimum
        GraphicsSettings safeSettings{};
        safeSettings.qualityPreset = 0;  // Low
        safeSettings.antiAliasing = false;
        safeSettings.motionBlur = false;
        safeSettings.depthOfField = false;

        GetGraphicsSettingsManager()->ApplySettings(safeSettings);

        GetLogger()->Info("SafeMode", "Set graphics to safe defaults");
    }

    void ResetGameSettings() {
        // Reset to default config
        GetConfigManager()->LoadDefaultConfig();
    }

    void ShowSafeModeDialog(const char* reason) {
        // Show UI with options:
        // - Continue in safe mode
        // - Try to load backup save
        // - Reset to new game
        // ... implementation ...
    }
};
```

---

# PART 2: SERIALIZATION

## Save File Format

### Save File Structure

```cpp
// SaveFileFormat.h

/**
 * Save File Format (.sav):
 *
 * [Header]
 * - Magic number (4 bytes): "SAVE"
 * - Version (4 bytes): Save format version
 * - Checksum (4 bytes): CRC32 of entire file
 * - Timestamp (8 bytes): When save was created
 * - Playtime (4 bytes): Total playtime in seconds
 * - Header size (4 bytes): Size of header + metadata
 *
 * [Metadata]
 * - Character name (256 bytes)
 * - Character level (4 bytes)
 * - Current location (256 bytes)
 * - Screenshot (compressed, variable size)
 *
 * [Player Data]
 * - Position, rotation
 * - Attributes (health, stamina, magic)
 * - Skills & perks
 * - Inventory (compressed)
 * - Quest states
 * - Faction standings
 *
 * [World State]
 * - Modified cells (delta from base game)
 * - NPC states
 * - Container contents (if changed)
 * - Dynamic events
 * - Mod data (per-mod save sections)
 *
 * [Footer]
 * - End marker (4 bytes): "ENDF"
 * - Final checksum (4 bytes)
 */

#pragma pack(push, 1)
struct SaveFileHeader {
    char magic[4];          // "SAVE"
    uint32_t version;       // Save format version
    uint32_t checksum;      // CRC32 of file
    uint64_t timestamp;     // Unix timestamp
    uint32_t playtime;      // Playtime in seconds
    uint32_t headerSize;    // Size of header + metadata

    bool IsValid() const {
        return memcmp(magic, "SAVE", 4) == 0;
    }
};

struct SaveFileMetadata {
    char characterName[256];
    uint32_t characterLevel;
    char currentLocation[256];
    uint32_t screenshotSize;
    // Screenshot data follows (screenshotSize bytes)
};
#pragma pack(pop)

// Current save version
const uint32_t SAVE_VERSION = 1;
```

---

## Serialization Framework

### Serializer Base Class

```cpp
// Serializer.h

// Binary writer
class BinaryWriter {
public:
    BinaryWriter(const char* path) {
        file = fopen(path, "wb");
        if (!file) {
            throw std::runtime_error("Failed to open file for writing");
        }
    }

    ~BinaryWriter() {
        if (file) fclose(file);
    }

    // Write primitive types
    void Write(uint8_t value) { fwrite(&value, sizeof(value), 1, file); }
    void Write(uint16_t value) { fwrite(&value, sizeof(value), 1, file); }
    void Write(uint32_t value) { fwrite(&value, sizeof(value), 1, file); }
    void Write(uint64_t value) { fwrite(&value, sizeof(value), 1, file); }
    void Write(float value) { fwrite(&value, sizeof(value), 1, file); }
    void Write(double value) { fwrite(&value, sizeof(value), 1, file); }

    // Write string
    void WriteString(const char* str) {
        uint32_t length = strlen(str);
        Write(length);
        fwrite(str, 1, length, file);
    }

    // Write vector
    void WriteVector(const FVector& v) {
        Write(v.x);
        Write(v.y);
        Write(v.z);
    }

    // Write quaternion
    void WriteQuat(const FQuat& q) {
        Write(q.x);
        Write(q.y);
        Write(q.z);
        Write(q.w);
    }

    // Write array
    template<typename T>
    void WriteArray(const std::vector<T>& array) {
        Write(static_cast<uint32_t>(array.size()));
        for (const auto& item : array) {
            Write(item);
        }
    }

    // Get current position
    size_t Tell() const {
        return ftell(file);
    }

    // Seek to position
    void Seek(size_t pos) {
        fseek(file, pos, SEEK_SET);
    }

private:
    FILE* file;
};

// Binary reader
class BinaryReader {
public:
    BinaryReader(const char* path) {
        file = fopen(path, "rb");
        if (!file) {
            throw std::runtime_error("Failed to open file for reading");
        }
    }

    ~BinaryReader() {
        if (file) fclose(file);
    }

    // Read primitive types
    uint8_t ReadUInt8() {
        uint8_t value;
        fread(&value, sizeof(value), 1, file);
        return value;
    }

    uint32_t ReadUInt32() {
        uint32_t value;
        fread(&value, sizeof(value), 1, file);
        return value;
    }

    float ReadFloat() {
        float value;
        fread(&value, sizeof(value), 1, file);
        return value;
    }

    // Read string
    std::string ReadString() {
        uint32_t length = ReadUInt32();
        std::vector<char> buffer(length + 1);
        fread(buffer.data(), 1, length, file);
        buffer[length] = '\0';
        return std::string(buffer.data());
    }

    // Read vector
    FVector ReadVector() {
        return FVector{ReadFloat(), ReadFloat(), ReadFloat()};
    }

    // Read array
    template<typename T>
    std::vector<T> ReadArray() {
        uint32_t count = ReadUInt32();
        std::vector<T> array;
        array.reserve(count);

        for (uint32_t i = 0; i < count; ++i) {
            array.push_back(Read<T>());
        }

        return array;
    }

    bool IsEOF() const {
        return feof(file) != 0;
    }

private:
    FILE* file;
};

// Serializable interface
class ISerializable {
public:
    virtual ~ISerializable() = default;

    virtual void Serialize(BinaryWriter& writer) const = 0;
    virtual void Deserialize(BinaryReader& reader) = 0;
};
```

---

## Save System

### Save/Load Manager

```cpp
// SaveSystem.h

class SaveSystem {
public:
    // ASYNC: Save game (runs on background worker)
    async Task<bool> SaveGame(const char* filename) {
        // BACKGROUND WORKER THREAD

        auto* inst = GetInstrumentation();
        inst->BeginSample("SaveGame");

        try {
            GetLogger()->Info("SaveSystem", "Saving game: %s", filename);

            // Fire pre-save event
            DispatchEvent(SaveAPI::PreSaveEvent{filename});

            // Collect save data from all subsystems
            SaveData data = CollectSaveData();

            // Write to file
            WriteSaveFile(filename, data);

            // Calculate checksum
            uint32_t checksum = CalculateChecksum(filename);

            // Update header with checksum
            UpdateChecksum(filename, checksum);

            inst->EndSample("SaveGame");

            // Fire post-save event (on main thread)
            PostToMainThread([filename]() {
                DispatchEvent(SaveAPI::PostSaveEvent{filename, true});
            });

            GetLogger()->Info("SaveSystem", "Save completed: %s", filename);

            return true;

        } catch (const std::exception& e) {
            inst->EndSample("SaveGame");

            GetLogger()->Error("SaveSystem", "Save failed: %s", e.what());

            // Fire save failed event
            PostToMainThread([filename, error = std::string(e.what())]() {
                DispatchEvent(SaveAPI::SaveFailedEvent{filename, error.c_str()});
            });

            return false;
        }
    }

    // ASYNC: Load game
    async Task<bool> LoadGame(const char* filename) {
        // BACKGROUND WORKER THREAD

        auto* inst = GetInstrumentation();
        inst->BeginSample("LoadGame");

        try {
            GetLogger()->Info("SaveSystem", "Loading game: %s", filename);

            // Fire pre-load event
            DispatchEvent(SaveAPI::PreLoadEvent{filename});

            // Validate file
            if (!ValidateSaveFile(filename)) {
                throw SaveFileCorruptException(filename, "Checksum mismatch");
            }

            // Read save data
            SaveData data = ReadSaveFile(filename);

            // Check version compatibility
            if (data.version > SAVE_VERSION) {
                throw SaveFileCorruptException(filename, "Save from newer version");
            }

            // Migrate if needed
            if (data.version < SAVE_VERSION) {
                GetLogger()->Info("SaveSystem",
                    "Migrating save from v%d to v%d", data.version, SAVE_VERSION);
                data = MigrateSaveData(data, SAVE_VERSION);
            }

            // Apply to game state (on main thread)
            PostToMainThread([this, data]() {
                ApplySaveData(data);
            });

            inst->EndSample("LoadGame");

            // Fire post-load event
            PostToMainThread([filename]() {
                DispatchEvent(SaveAPI::PostLoadEvent{filename, true});
            });

            GetLogger()->Info("SaveSystem", "Load completed: %s", filename);

            return true;

        } catch (const std::exception& e) {
            inst->EndSample("LoadGame");

            GetLogger()->Error("SaveSystem", "Load failed: %s", e.what());

            // Fire load failed event
            PostToMainThread([filename, error = std::string(e.what())]() {
                DispatchEvent(SaveAPI::LoadFailedEvent{filename, error.c_str()});
            });

            // Enter safe mode on corrupted save
            if (dynamic_cast<const SaveFileCorruptException*>(&e)) {
                PostToMainThread([error = std::string(e.what())]() {
                    GetSafeModeManager()->EnterSafeMode(error.c_str());
                });
            }

            return false;
        }
    }

    // Quick save
    void QuickSave(const char* suffix = "") {
        char filename[256];
        snprintf(filename, sizeof(filename), "quicksave%s.sav", suffix);

        // Run async
        SaveGame(filename);
    }

    // Auto-save
    void AutoSave() {
        // Rotate auto-saves (keep 3 most recent)
        RotateAutoSaves();

        QuickSave("_auto");
    }

private:
    struct SaveData {
        uint32_t version;
        SaveFileMetadata metadata;
        PlayerData player;
        WorldState world;
        std::unordered_map<std::string, ModData> mods;
    };

    SaveData CollectSaveData() {
        SaveData data;
        data.version = SAVE_VERSION;

        // Collect player data
        data.player = GetPlayerController()->SerializePlayerData();

        // Collect world state
        data.world = GetWorldManager()->SerializeWorldState();

        // Collect mod data
        for (auto* mod : GetModManager()->GetActiveMods()) {
            data.mods[mod->GetName()] = mod->SerializeModData();
        }

        return data;
    }

    void WriteSaveFile(const char* filename, const SaveData& data) {
        BinaryWriter writer(filename);

        // Write header
        SaveFileHeader header{};
        memcpy(header.magic, "SAVE", 4);
        header.version = data.version;
        header.timestamp = GetCurrentTimeUnix();
        header.playtime = GetTotalPlaytime();

        writer.Write(header);

        // Write metadata
        writer.Write(data.metadata);

        // Write player data
        data.player.Serialize(writer);

        // Write world state
        data.world.Serialize(writer);

        // Write mod data
        writer.Write(static_cast<uint32_t>(data.mods.size()));
        for (const auto& [modName, modData] : data.mods) {
            writer.WriteString(modName.c_str());
            modData.Serialize(writer);
        }

        // Write footer
        writer.WriteString("ENDF");
    }

    SaveData ReadSaveFile(const char* filename) {
        BinaryReader reader(filename);

        SaveData data;

        // Read header
        SaveFileHeader header;
        reader.Read(&header, sizeof(header));

        if (!header.IsValid()) {
            throw SaveFileCorruptException(filename, "Invalid magic number");
        }

        data.version = header.version;

        // Read metadata
        reader.Read(&data.metadata, sizeof(data.metadata));

        // Read player data
        data.player.Deserialize(reader);

        // Read world state
        data.world.Deserialize(reader);

        // Read mod data
        uint32_t modCount = reader.ReadUInt32();
        for (uint32_t i = 0; i < modCount; ++i) {
            std::string modName = reader.ReadString();
            ModData modData;
            modData.Deserialize(reader);
            data.mods[modName] = modData;
        }

        // Validate footer
        std::string footer = reader.ReadString();
        if (footer != "ENDF") {
            throw SaveFileCorruptException(filename, "Invalid footer");
        }

        return data;
    }

    bool ValidateSaveFile(const char* filename) {
        // Calculate checksum
        uint32_t calculated = CalculateChecksum(filename);

        // Read header checksum
        BinaryReader reader(filename);
        SaveFileHeader header;
        reader.Read(&header, sizeof(header));

        // Compare
        return header.checksum == calculated;
    }

    uint32_t CalculateChecksum(const char* filename) {
        // CRC32 of entire file
        // ... implementation ...
        return 0;
    }

    void UpdateChecksum(const char* filename, uint32_t checksum) {
        // Update checksum in header
        FILE* f = fopen(filename, "r+b");
        if (f) {
            fseek(f, offsetof(SaveFileHeader, checksum), SEEK_SET);
            fwrite(&checksum, sizeof(checksum), 1, f);
            fclose(f);
        }
    }

    SaveData MigrateSaveData(const SaveData& old, uint32_t targetVersion) {
        // Version migration logic
        SaveData migrated = old;

        // Apply migrations sequentially
        for (uint32_t v = old.version; v < targetVersion; ++v) {
            migrated = ApplyMigration(migrated, v, v + 1);
        }

        return migrated;
    }

    SaveData ApplyMigration(const SaveData& data, uint32_t from, uint32_t to) {
        GetLogger()->Info("SaveSystem", "Migrating from v%d to v%d", from, to);

        // Apply version-specific migration
        // ... implementation ...

        return data;
    }

    void ApplySaveData(const SaveData& data) {
        // MAIN THREAD

        // Apply player data
        GetPlayerController()->DeserializePlayerData(data.player);

        // Apply world state
        GetWorldManager()->DeserializeWorldState(data.world);

        // Apply mod data
        for (const auto& [modName, modData] : data.mods) {
            auto* mod = GetModManager()->FindMod(modName.c_str());
            if (mod) {
                mod->DeserializeModData(modData);
            }
        }
    }

    void RotateAutoSaves() {
        // Keep 3 auto-saves: auto0, auto1, auto2
        // Delete auto2, rename auto1 -> auto2, auto0 -> auto1
        // ... implementation ...
    }
};
```

---

## Hook Events

### Error Events

```cpp
// ErrorEvents.h

namespace ErrorAPI {

// Log event
struct LogEvent : IGameEvent {
    LogLevel level;
    const char* category;
    const char* message;

    const char* GetCategory() const override { return "Error"; }
};

// Exception caught
struct ExceptionEvent : IGameEvent {
    const char* message;
    const char* context;
};

// Crash detected
struct CrashEvent : IGameEvent {
    const char* reason;
};

// Safe mode entered
struct SafeModeEvent : IGameEvent {
    const char* reason;
};

} // namespace ErrorAPI

/*
Event names:
"Error.Log"
"Error.Exception"
"Error.Crash"
"Error.SafeMode.Enter"
"Error.SafeMode.Exit"
*/
```

### Save Events

```cpp
// SaveEvents.h

namespace SaveAPI {

// Pre-save
struct PreSaveEvent : IGameEvent {
    const char* filename;
    bool* shouldCancel;

    const char* GetCategory() const override { return "Save"; }
};

// Post-save
struct PostSaveEvent : IGameEvent {
    const char* filename;
    bool success;
};

// Save failed
struct SaveFailedEvent : IGameEvent {
    const char* filename;
    const char* error;
};

// Pre-load
struct PreLoadEvent : IGameEvent {
    const char* filename;
    bool* shouldCancel;
};

// Post-load
struct PostLoadEvent : IGameEvent {
    const char* filename;
    bool success;
};

// Load failed
struct LoadFailedEvent : IGameEvent {
    const char* filename;
    const char* error;
};

} // namespace SaveAPI

/*
Event names:
"Save.Pre"
"Save.Post"
"Save.Failed"
"Load.Pre"
"Load.Post"
"Load.Failed"
*/
```

---

## Console Commands

```cpp
// Error handling commands

REGISTER_CONSOLE_COMMAND(log_level, "Set minimum log level") {
    if (args.size() < 1) {
        Console->Print("Usage: log.level <trace|debug|info|warning|error|fatal>");
        return;
    }

    LogLevel level = ParseLogLevel(args[0]);
    GetLogger()->SetMinLevel(level);
    Console->Print("Log level set to: %s", args[0]);
}

REGISTER_CONSOLE_COMMAND(crash_test, "Test crash recovery") {
    Console->Print("Triggering test crash...");
    GetCrashRecoveryManager()->OnCrash("Test crash");
}

REGISTER_CONSOLE_COMMAND(safe_mode, "Enter safe mode") {
    GetSafeModeManager()->EnterSafeMode("Manual activation");
    Console->Print("Entered safe mode");
}

// Save/load commands

REGISTER_CONSOLE_COMMAND(save_game, "Save game") {
    if (args.size() < 1) {
        Console->Print("Usage: save.game <filename>");
        return;
    }

    GetSaveSystem()->SaveGame(args[0]);
    Console->Print("Saving to: %s", args[0]);
}

REGISTER_CONSOLE_COMMAND(load_game, "Load game") {
    if (args.size() < 1) {
        Console->Print("Usage: load.game <filename>");
        return;
    }

    GetSaveSystem()->LoadGame(args[0]);
    Console->Print("Loading from: %s", args[0]);
}

REGISTER_CONSOLE_COMMAND(quick_save, "Quick save") {
    GetSaveSystem()->QuickSave();
    Console->Print("Quick saving...");
}

REGISTER_CONSOLE_COMMAND(validate_save, "Validate save file") {
    if (args.size() < 1) {
        Console->Print("Usage: save.validate <filename>");
        return;
    }

    bool valid = GetSaveSystem()->ValidateSaveFile(args[0]);
    Console->Print("Save file %s: %s", args[0], valid ? "VALID" : "CORRUPTED");
}
```

---

**Document Status:** Design v1.0
**Last Updated:** 2026-01-25
**Next Review:** After prototype phase
