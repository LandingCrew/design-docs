# Input & Configuration Systems

**Subsystem:** Core Engine - User Input & Settings Management
**Owner:** Engine Team
**Dependencies:** Game Loop, ECS
**Status:** Design Phase

---

## Overview

The Input Management System provides device abstraction and input mapping, while the Configuration System handles game settings and runtime options. Both systems support modding, hot-reload, and accessibility features.

**Core Principles:**
- **Device Agnostic**: Abstract keyboard/mouse/gamepad behind unified API
- **Remappable Everything**: All inputs can be rebound by user
- **Context-Aware**: Different input schemes for combat/menu/dialogue
- **Accessible**: Support alternative input methods and assistance features
- **Mod-Friendly**: Expose configuration and input events to mods

---

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                   Input System                               │
│  - Device abstraction (KB/M, gamepad, touch)                 │
│  - Input mapping & binding                                   │
│  - Context switching                                         │
│  - Input buffering for combos                                │
└─────────────────────────────────────────────────────────────┘
                              ↕
┌──────────────┬──────────────┬──────────────┬────────────────┐
│  Raw Input   │  Action Map  │  Context     │  Buffer        │
│  Handlers    │  System      │  Manager     │  System        │
└──────────────┴──────────────┴──────────────┴────────────────┘
                              ↕
┌─────────────────────────────────────────────────────────────┐
│                Configuration System                          │
│  - Settings categories (graphics, audio, gameplay)           │
│  - Config file management (.ini, .json)                      │
│  - Hot-reload support                                        │
│  - Platform-specific overrides                               │
└─────────────────────────────────────────────────────────────┘
```

---

# PART 1: INPUT MANAGEMENT

## Input Device Abstraction

### Raw Input Handling

```cpp
// InputDevice.h

// Abstract input device interface
class IInputDevice {
public:
    virtual ~IInputDevice() = default;

    // Poll device state (called each frame)
    virtual void Poll() = 0;

    // Check if device is connected
    virtual bool IsConnected() const = 0;

    // Get device type
    virtual DeviceType GetType() const = 0;

    // Get device name
    virtual const char* GetName() const = 0;
};

enum class DeviceType {
    KEYBOARD,
    MOUSE,
    GAMEPAD,
    TOUCH,
    VR_CONTROLLER
};

// Keyboard device
class KeyboardDevice : public IInputDevice {
public:
    void Poll() override {
        // MAIN THREAD ONLY

        // Poll OS for keyboard state
        for (int key = 0; key < KEY_COUNT; ++key) {
            bool wasDown = keyState[key];
            bool isDown = PollKeyState(key);

            keyState[key] = isDown;

            // Fire events on state change
            if (!wasDown && isDown) {
                // Key pressed
                DispatchEvent(InputAPI::KeyPressEvent{
                    static_cast<KeyCode>(key)
                });
            } else if (wasDown && !isDown) {
                // Key released
                DispatchEvent(InputAPI::KeyReleaseEvent{
                    static_cast<KeyCode>(key)
                });
            }
        }
    }

    bool IsKeyDown(KeyCode key) const {
        return keyState[static_cast<int>(key)];
    }

    bool IsKeyPressed(KeyCode key) const {
        return keyState[static_cast<int>(key)] &&
               !prevKeyState[static_cast<int>(key)];
    }

    bool IsKeyReleased(KeyCode key) const {
        return !keyState[static_cast<int>(key)] &&
               prevKeyState[static_cast<int>(key)];
    }

    DeviceType GetType() const override { return DeviceType::KEYBOARD; }
    const char* GetName() const override { return "Keyboard"; }

private:
    static const int KEY_COUNT = 256;
    bool keyState[KEY_COUNT] = {};
    bool prevKeyState[KEY_COUNT] = {};
};

// Mouse device
class MouseDevice : public IInputDevice {
public:
    void Poll() override {
        // MAIN THREAD ONLY

        // Poll mouse position
        prevPosition = position;
        position = GetMousePosition();

        // Poll mouse buttons
        for (int btn = 0; btn < BUTTON_COUNT; ++btn) {
            bool wasDown = buttonState[btn];
            bool isDown = PollButtonState(btn);

            buttonState[btn] = isDown;

            if (!wasDown && isDown) {
                DispatchEvent(InputAPI::MouseButtonPressEvent{
                    static_cast<MouseButton>(btn), position
                });
            } else if (wasDown && !isDown) {
                DispatchEvent(InputAPI::MouseButtonReleaseEvent{
                    static_cast<MouseButton>(btn), position
                });
            }
        }

        // Poll mouse wheel
        float wheelDelta = GetWheelDelta();
        if (wheelDelta != 0.0f) {
            DispatchEvent(InputAPI::MouseWheelEvent{wheelDelta});
        }

        // Fire mouse move event if moved
        if (position != prevPosition) {
            FVector2D delta = position - prevPosition;
            DispatchEvent(InputAPI::MouseMoveEvent{position, delta});
        }
    }

    FVector2D GetPosition() const { return position; }
    FVector2D GetDelta() const { return position - prevPosition; }

    bool IsButtonDown(MouseButton button) const {
        return buttonState[static_cast<int>(button)];
    }

    DeviceType GetType() const override { return DeviceType::MOUSE; }
    const char* GetName() const override { return "Mouse"; }

private:
    static const int BUTTON_COUNT = 8;
    FVector2D position;
    FVector2D prevPosition;
    bool buttonState[BUTTON_COUNT] = {};
};

// Gamepad device
class GamepadDevice : public IInputDevice {
public:
    void Poll() override {
        // MAIN THREAD ONLY

        if (!IsConnected()) return;

        // Poll button state
        for (int btn = 0; btn < BUTTON_COUNT; ++btn) {
            bool wasDown = buttonState[btn];
            bool isDown = PollButtonState(btn);

            buttonState[btn] = isDown;

            if (!wasDown && isDown) {
                DispatchEvent(InputAPI::GamepadButtonPressEvent{
                    playerIndex,
                    static_cast<GamepadButton>(btn)
                });
            } else if (wasDown && !isDown) {
                DispatchEvent(InputAPI::GamepadButtonReleaseEvent{
                    playerIndex,
                    static_cast<GamepadButton>(btn)
                });
            }
        }

        // Poll analog sticks (with deadzone)
        leftStick = ApplyDeadzone(PollLeftStick(), deadzone);
        rightStick = ApplyDeadzone(PollRightStick(), deadzone);

        // Poll triggers
        leftTrigger = PollLeftTrigger();
        rightTrigger = PollRightTrigger();

        // Fire analog events if changed
        if (leftStick != prevLeftStick) {
            DispatchEvent(InputAPI::GamepadStickEvent{
                playerIndex, StickType::LEFT, leftStick
            });
        }
        if (rightStick != prevRightStick) {
            DispatchEvent(InputAPI::GamepadStickEvent{
                playerIndex, StickType::RIGHT, rightStick
            });
        }

        prevLeftStick = leftStick;
        prevRightStick = rightStick;
    }

    FVector2D GetLeftStick() const { return leftStick; }
    FVector2D GetRightStick() const { return rightStick; }
    float GetLeftTrigger() const { return leftTrigger; }
    float GetRightTrigger() const { return rightTrigger; }

    // Apply radial deadzone
    FVector2D ApplyDeadzone(FVector2D stick, float deadzone) {
        float magnitude = stick.Length();
        if (magnitude < deadzone) {
            return FVector2D::Zero();
        }

        // Scale to remove deadzone
        float scaled = (magnitude - deadzone) / (1.0f - deadzone);
        return stick.Normalized() * scaled;
    }

    // Configure deadzone (default 0.15)
    void SetDeadzone(float value) { deadzone = std::clamp(value, 0.0f, 0.9f); }

    DeviceType GetType() const override { return DeviceType::GAMEPAD; }
    const char* GetName() const override { return "Gamepad"; }

private:
    static const int BUTTON_COUNT = 16;
    int playerIndex = 0;
    bool buttonState[BUTTON_COUNT] = {};
    FVector2D leftStick;
    FVector2D rightStick;
    FVector2D prevLeftStick;
    FVector2D prevRightStick;
    float leftTrigger = 0.0f;
    float rightTrigger = 0.0f;
    float deadzone = 0.15f;
};
```

---

## Action Mapping System

### Action Definitions

```cpp
// InputAction.h

// High-level game action (device-agnostic)
enum class InputAction {
    // Movement
    MOVE_FORWARD,
    MOVE_BACKWARD,
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP,
    SPRINT,
    CROUCH,

    // Combat
    ATTACK_LIGHT,
    ATTACK_HEAVY,
    BLOCK,
    DODGE,
    SHEATHE_WEAPON,

    // Interaction
    INTERACT,
    USE_ITEM,
    PICKUP,

    // Magic
    CAST_SPELL,
    SWITCH_SPELL,

    // UI
    OPEN_INVENTORY,
    OPEN_MAP,
    OPEN_JOURNAL,
    PAUSE,

    // Camera
    LOOK_HORIZONTAL,
    LOOK_VERTICAL,
    ZOOM_IN,
    ZOOM_OUT,

    COUNT
};

// Input binding (maps device input to action)
struct InputBinding {
    InputAction action;
    DeviceType device;
    int keyOrButton;           // Key code, button index, etc.
    float scale = 1.0f;        // For analog inputs (invert axis, etc.)
    ModifierKeys modifiers;    // Shift, Ctrl, Alt

    bool Matches(DeviceType dev, int input, ModifierKeys mods) const {
        return device == dev &&
               keyOrButton == input &&
               modifiers == mods;
    }
};

struct ModifierKeys {
    bool shift = false;
    bool ctrl = false;
    bool alt = false;

    bool operator==(const ModifierKeys& other) const {
        return shift == other.shift &&
               ctrl == other.ctrl &&
               alt == other.alt;
    }
};
```

### Action Map Manager

```cpp
// ActionMapManager.h

class ActionMapManager {
public:
    // Register default bindings
    void RegisterDefaultBindings() {
        // Keyboard + Mouse bindings
        Bind(InputAction::MOVE_FORWARD, DeviceType::KEYBOARD, KEY_W);
        Bind(InputAction::MOVE_BACKWARD, DeviceType::KEYBOARD, KEY_S);
        Bind(InputAction::MOVE_LEFT, DeviceType::KEYBOARD, KEY_A);
        Bind(InputAction::MOVE_RIGHT, DeviceType::KEYBOARD, KEY_D);
        Bind(InputAction::JUMP, DeviceType::KEYBOARD, KEY_SPACE);
        Bind(InputAction::SPRINT, DeviceType::KEYBOARD, KEY_SHIFT);
        Bind(InputAction::ATTACK_LIGHT, DeviceType::MOUSE, MOUSE_LEFT);
        Bind(InputAction::ATTACK_HEAVY, DeviceType::MOUSE, MOUSE_RIGHT);
        Bind(InputAction::INTERACT, DeviceType::KEYBOARD, KEY_E);

        // Gamepad bindings
        Bind(InputAction::JUMP, DeviceType::GAMEPAD, GAMEPAD_A);
        Bind(InputAction::SPRINT, DeviceType::GAMEPAD, GAMEPAD_LEFT_STICK_CLICK);
        Bind(InputAction::ATTACK_LIGHT, DeviceType::GAMEPAD, GAMEPAD_RIGHT_TRIGGER);
        Bind(InputAction::ATTACK_HEAVY, DeviceType::GAMEPAD, GAMEPAD_LEFT_TRIGGER);
        Bind(InputAction::INTERACT, DeviceType::GAMEPAD, GAMEPAD_X);
    }

    // Bind action to input
    void Bind(InputAction action, DeviceType device, int input,
              ModifierKeys modifiers = {}) {
        InputBinding binding{action, device, input, 1.0f, modifiers};
        bindings[action].push_back(binding);
    }

    // Rebind action (for user customization)
    void Rebind(InputAction action, int bindingIndex,
                DeviceType newDevice, int newInput,
                ModifierKeys modifiers = {}) {
        auto& actionBindings = bindings[action];

        if (bindingIndex < actionBindings.size()) {
            // Fire pre-rebind event (mods can react)
            DispatchEvent(InputAPI::RebindEvent{
                action, actionBindings[bindingIndex]
            });

            // Update binding
            actionBindings[bindingIndex].device = newDevice;
            actionBindings[bindingIndex].keyOrButton = newInput;
            actionBindings[bindingIndex].modifiers = modifiers;

            // Save to config
            SaveBindings();
        }
    }

    // Check if action is currently pressed
    bool IsActionPressed(InputAction action) const {
        for (const auto& binding : bindings.at(action)) {
            if (IsBindingActive(binding)) {
                return true;
            }
        }
        return false;
    }

    // Get analog value for action (-1.0 to 1.0)
    float GetActionValue(InputAction action) const {
        for (const auto& binding : bindings.at(action)) {
            if (IsBindingActive(binding)) {
                return GetBindingValue(binding) * binding.scale;
            }
        }
        return 0.0f;
    }

    // Get all bindings for action
    const std::vector<InputBinding>& GetBindings(InputAction action) const {
        return bindings.at(action);
    }

    // Save bindings to config file
    void SaveBindings() {
        JsonWriter writer("Config/InputBindings.json");

        for (int i = 0; i < static_cast<int>(InputAction::COUNT); ++i) {
            InputAction action = static_cast<InputAction>(i);
            writer.BeginArray(GetActionName(action));

            for (const auto& binding : bindings[action]) {
                writer.BeginObject();
                writer.Write("device", GetDeviceName(binding.device));
                writer.Write("input", binding.keyOrButton);
                writer.Write("scale", binding.scale);
                writer.Write("modifiers", SerializeModifiers(binding.modifiers));
                writer.EndObject();
            }

            writer.EndArray();
        }

        writer.Close();
    }

    // Load bindings from config file
    void LoadBindings() {
        JsonReader reader("Config/InputBindings.json");

        if (!reader.IsValid()) {
            RegisterDefaultBindings();
            SaveBindings();
            return;
        }

        // Parse bindings...
        // ... implementation ...
    }

private:
    std::unordered_map<InputAction, std::vector<InputBinding>> bindings;

    // Check if binding is currently active
    bool IsBindingActive(const InputBinding& binding) const {
        switch (binding.device) {
            case DeviceType::KEYBOARD:
                return keyboard->IsKeyDown(static_cast<KeyCode>(binding.keyOrButton));
            case DeviceType::MOUSE:
                return mouse->IsButtonDown(static_cast<MouseButton>(binding.keyOrButton));
            case DeviceType::GAMEPAD:
                return gamepad->IsButtonDown(static_cast<GamepadButton>(binding.keyOrButton));
            default:
                return false;
        }
    }

    // Get analog value for binding
    float GetBindingValue(const InputBinding& binding) const {
        // For digital inputs, return 1.0 if pressed
        if (IsBindingActive(binding)) {
            return 1.0f;
        }

        // For analog inputs (sticks, triggers)
        // ... implementation ...

        return 0.0f;
    }
};
```

---

## Input Context System

### Context Switching

```cpp
// InputContext.h

// Input context (different input schemes for different modes)
enum class InputContext {
    GAMEPLAY,       // Normal gameplay
    COMBAT,         // Active combat
    MENU,           // Pause menu, inventory
    DIALOGUE,       // Conversation
    MAP,            // World map
    CRAFTING,       // Crafting interface
    LOCKPICKING,    // Lockpicking minigame
    CINEMATIC       // Non-interactive cutscene
};

class InputContextManager {
public:
    // Push new context (stacks)
    void PushContext(InputContext context) {
        contextStack.push_back(context);

        // Fire context change event
        DispatchEvent(InputAPI::ContextChangeEvent{
            GetActiveContext(), context
        });

        GetInstrumentation()->LogDebug("Input",
            "Pushed context: %s", GetContextName(context));
    }

    // Pop current context
    void PopContext() {
        if (contextStack.empty()) return;

        InputContext oldContext = GetActiveContext();
        contextStack.pop_back();

        // Fire context change event
        DispatchEvent(InputAPI::ContextChangeEvent{
            oldContext, GetActiveContext()
        });
    }

    // Get active context
    InputContext GetActiveContext() const {
        return contextStack.empty() ?
            InputContext::GAMEPLAY : contextStack.back();
    }

    // Check if action is allowed in current context
    bool IsActionAllowed(InputAction action) const {
        InputContext context = GetActiveContext();

        switch (context) {
            case InputContext::GAMEPLAY:
                return true;  // All actions allowed

            case InputContext::MENU:
                // Only UI actions
                return IsUIAction(action);

            case InputContext::DIALOGUE:
                // Only dialogue and UI actions
                return IsDialogueAction(action) || IsUIAction(action);

            case InputContext::COMBAT:
                // Combat + movement, no UI
                return IsCombatAction(action) || IsMovementAction(action);

            case InputContext::CINEMATIC:
                // Only skip/pause
                return action == InputAction::PAUSE;

            default:
                return false;
        }
    }

private:
    std::vector<InputContext> contextStack;

    bool IsUIAction(InputAction action) const {
        return action >= InputAction::OPEN_INVENTORY &&
               action <= InputAction::PAUSE;
    }

    bool IsCombatAction(InputAction action) const {
        return action >= InputAction::ATTACK_LIGHT &&
               action <= InputAction::SHEATHE_WEAPON;
    }

    bool IsMovementAction(InputAction action) const {
        return action >= InputAction::MOVE_FORWARD &&
               action <= InputAction::CROUCH;
    }

    bool IsDialogueAction(InputAction action) const {
        return action == InputAction::INTERACT;
    }
};
```

---

## Input Buffering (Combo System)

### Buffered Input Queue

```cpp
// InputBuffer.h

// For fighting game-style input buffering
class InputBuffer {
public:
    struct BufferedInput {
        InputAction action;
        float timestamp;
        bool consumed = false;
    };

    InputBuffer(float bufferWindow = 0.2f) : bufferWindow(bufferWindow) {}

    // Add input to buffer
    void BufferInput(InputAction action) {
        BufferedInput input{action, GetCurrentTime(), false};
        buffer.push_back(input);

        // Trim old inputs
        CleanBuffer();
    }

    // Check if action is in buffer
    bool HasBufferedInput(InputAction action) const {
        for (const auto& input : buffer) {
            if (input.action == action && !input.consumed) {
                return true;
            }
        }
        return false;
    }

    // Consume buffered input (prevents reuse)
    void ConsumeInput(InputAction action) {
        for (auto& input : buffer) {
            if (input.action == action && !input.consumed) {
                input.consumed = true;
                return;
            }
        }
    }

    // Check for input sequence (combo)
    bool CheckSequence(const std::vector<InputAction>& sequence) const {
        if (sequence.size() > buffer.size()) return false;

        // Check if sequence matches recent inputs
        size_t bufferIdx = buffer.size() - sequence.size();
        for (size_t i = 0; i < sequence.size(); ++i) {
            if (buffer[bufferIdx + i].action != sequence[i]) {
                return false;
            }
        }

        return true;
    }

    // Clear buffer
    void Clear() {
        buffer.clear();
    }

private:
    std::vector<BufferedInput> buffer;
    float bufferWindow;  // How long inputs stay in buffer

    void CleanBuffer() {
        float currentTime = GetCurrentTime();

        buffer.erase(
            std::remove_if(buffer.begin(), buffer.end(),
                [currentTime, this](const BufferedInput& input) {
                    return currentTime - input.timestamp > bufferWindow;
                }),
            buffer.end()
        );
    }
};

// Usage example: Combo attack
void CombatSystem::Update(float deltaTime) {
    // Check for light attack combo: Light -> Light -> Heavy
    if (inputBuffer->CheckSequence({
        InputAction::ATTACK_LIGHT,
        InputAction::ATTACK_LIGHT,
        InputAction::ATTACK_HEAVY
    })) {
        ExecuteComboAttack("TripleCombo");
        inputBuffer->Clear();
    }

    // Check for buffered dodge (during attack animation)
    if (player->IsAttacking() &&
        inputBuffer->HasBufferedInput(InputAction::DODGE)) {
        // Execute dodge immediately after attack finishes
        QueueDodge();
        inputBuffer->ConsumeInput(InputAction::DODGE);
    }
}
```

---

## Accessibility Features

### Accessibility Options

```cpp
// AccessibilitySettings.h

struct AccessibilitySettings {
    // Input assistance
    bool toggleCrouch = false;         // Toggle instead of hold
    bool toggleSprint = false;
    bool toggleADS = false;            // Aim down sights
    bool autoRun = false;

    // Button remapping
    bool swapTriggers = false;         // L2/R2 <-> L1/R1
    bool swapSticks = false;           // Left <-> right stick

    // Input timing
    float buttonHoldDuration = 0.5f;   // Longer hold time for confirmations
    float doubleClickWindow = 0.3f;    // Time window for double-tap

    // Haptics
    bool enableVibration = true;
    float vibrationStrength = 1.0f;

    // Visual indicators
    bool showButtonPrompts = true;
    bool showInputHistory = false;    // Display recent inputs on screen
};

class AccessibilityManager {
public:
    void ApplySettings(const AccessibilitySettings& settings) {
        this->settings = settings;

        // Modify input bindings based on accessibility settings
        if (settings.toggleCrouch) {
            // Convert crouch to toggle instead of hold
            ConvertToToggle(InputAction::CROUCH);
        }

        if (settings.swapTriggers) {
            // Swap L2/R2 with L1/R1
            SwapBindings(InputAction::ATTACK_LIGHT, InputAction::ATTACK_HEAVY);
        }

        // Fire settings changed event
        DispatchEvent(InputAPI::AccessibilityChangeEvent{settings});
    }

    // Check if action should toggle (vs hold)
    bool IsToggleAction(InputAction action) const {
        switch (action) {
            case InputAction::CROUCH:
                return settings.toggleCrouch;
            case InputAction::SPRINT:
                return settings.toggleSprint;
            default:
                return false;
        }
    }

private:
    AccessibilitySettings settings;

    void ConvertToToggle(InputAction action) {
        // Modify action behavior to toggle on/off
        // ... implementation ...
    }

    void SwapBindings(InputAction a, InputAction b) {
        // Swap bindings between two actions
        // ... implementation ...
    }
};
```

---

# PART 2: CONFIGURATION SYSTEM

## Configuration Architecture

### Config File Management

```cpp
// ConfigManager.h

class ConfigManager {
public:
    // Initialize with config file
    void Initialize(const char* configPath) {
        this->configPath = configPath;

        // Load config
        LoadConfig();

        // Watch for file changes (hot-reload)
        fileWatcher->WatchFile(configPath, [this]() {
            OnConfigFileChanged();
        });
    }

    // Get config value
    template<typename T>
    T Get(const char* category, const char* key, T defaultValue) const {
        std::string fullKey = std::string(category) + "." + key;

        if (!values.contains(fullKey)) {
            return defaultValue;
        }

        return ParseValue<T>(values.at(fullKey));
    }

    // Set config value
    template<typename T>
    void Set(const char* category, const char* key, T value) {
        std::string fullKey = std::string(category) + "." + key;

        // Fire pre-change event (mods can cancel)
        bool canceled = false;
        DispatchEvent(ConfigAPI::ValueChangeEvent{
            category, key, SerializeValue(value), &canceled
        });

        if (canceled) return;

        // Update value
        values[fullKey] = SerializeValue(value);

        // Mark dirty for save
        isDirty = true;

        // Apply immediately
        ApplyConfigChange(category, key, value);

        // Fire post-change event
        DispatchEvent(ConfigAPI::ValueChangedEvent{
            category, key, SerializeValue(value)
        });
    }

    // Save config to file
    void SaveConfig() {
        if (!isDirty) return;

        // Write to file
        ConfigWriter writer(configPath);

        // Write by category
        std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> byCategory;

        for (const auto& [fullKey, value] : values) {
            size_t dotPos = fullKey.find('.');
            std::string category = fullKey.substr(0, dotPos);
            std::string key = fullKey.substr(dotPos + 1);

            byCategory[category].push_back({key, value});
        }

        for (const auto& [category, entries] : byCategory) {
            writer.BeginSection(category);

            for (const auto& [key, value] : entries) {
                writer.Write(key, value);
            }

            writer.EndSection();
        }

        writer.Close();
        isDirty = false;

        GetInstrumentation()->LogInfo("Config", "Saved config to: %s", configPath);
    }

    // Load config from file
    void LoadConfig() {
        ConfigReader reader(configPath);

        if (!reader.IsValid()) {
            GetInstrumentation()->LogWarn("Config",
                "Config file not found: %s (using defaults)", configPath);
            CreateDefaultConfig();
            SaveConfig();
            return;
        }

        // Parse config file
        while (reader.HasMore()) {
            std::string category = reader.ReadSection();

            while (reader.HasMoreInSection()) {
                auto [key, value] = reader.ReadKeyValue();
                std::string fullKey = category + "." + key;
                values[fullKey] = value;
            }
        }

        reader.Close();

        // Apply all config values
        ApplyAllConfig();
    }

private:
    const char* configPath;
    std::unordered_map<std::string, std::string> values;
    bool isDirty = false;

    void OnConfigFileChanged() {
        GetInstrumentation()->LogInfo("Config", "Config file changed, reloading...");

        // Reload config
        LoadConfig();

        // Fire reload event
        DispatchEvent(ConfigAPI::ReloadEvent{configPath});
    }

    void ApplyConfigChange(const char* category, const char* key, const std::string& value) {
        // Apply specific config change to engine
        // ... implementation per category ...
    }

    void ApplyAllConfig() {
        // Apply all config values on load
        for (const auto& [fullKey, value] : values) {
            size_t dotPos = fullKey.find('.');
            std::string category = fullKey.substr(0, dotPos);
            std::string key = fullKey.substr(dotPos + 1);

            ApplyConfigChange(category.c_str(), key.c_str(), value);
        }
    }
};
```

---

## Settings Categories

### Graphics Settings

```cpp
// GraphicsSettings.h

struct GraphicsSettings {
    // Resolution
    int resolutionWidth = 1920;
    int resolutionHeight = 1080;
    bool fullscreen = true;
    bool vsync = true;

    // Quality presets
    int qualityPreset = 2;  // 0=Low, 1=Medium, 2=High, 3=Ultra

    // Individual settings
    int textureQuality = 2;      // 0-3
    int shadowQuality = 2;
    int effectsQuality = 2;
    int foliageDistance = 2;
    int viewDistance = 2;

    // Advanced
    bool antiAliasing = true;
    bool ambientOcclusion = true;
    bool motionBlur = true;
    bool depthOfField = true;
    float fov = 90.0f;

    // Performance
    int maxFPS = 60;
    bool showFPSCounter = false;
};

class GraphicsSettingsManager {
public:
    void ApplySettings(const GraphicsSettings& settings) {
        this->settings = settings;

        // Apply to renderer
        renderer->SetResolution(settings.resolutionWidth, settings.resolutionHeight);
        renderer->SetFullscreen(settings.fullscreen);
        renderer->SetVSync(settings.vsync);
        renderer->SetTextureQuality(settings.textureQuality);
        renderer->SetShadowQuality(settings.shadowQuality);
        renderer->SetMaxFPS(settings.maxFPS);

        // Fire settings changed event
        DispatchEvent(ConfigAPI::GraphicsChangeEvent{settings});

        // Save to config
        SaveToConfig();
    }

    void LoadFromConfig() {
        auto* cfg = GetConfigManager();

        settings.resolutionWidth = cfg->Get("Graphics", "ResolutionWidth", 1920);
        settings.resolutionHeight = cfg->Get("Graphics", "ResolutionHeight", 1080);
        settings.fullscreen = cfg->Get("Graphics", "Fullscreen", true);
        settings.vsync = cfg->Get("Graphics", "VSync", true);
        settings.qualityPreset = cfg->Get("Graphics", "QualityPreset", 2);
        // ... load other settings ...

        ApplySettings(settings);
    }

private:
    GraphicsSettings settings;

    void SaveToConfig() {
        auto* cfg = GetConfigManager();

        cfg->Set("Graphics", "ResolutionWidth", settings.resolutionWidth);
        cfg->Set("Graphics", "ResolutionHeight", settings.resolutionHeight);
        cfg->Set("Graphics", "Fullscreen", settings.fullscreen);
        // ... save other settings ...

        cfg->SaveConfig();
    }
};
```

### Audio Settings

```cpp
// AudioSettings.h

struct AudioSettings {
    // Volume levels (0.0 - 1.0)
    float masterVolume = 1.0f;
    float musicVolume = 0.8f;
    float sfxVolume = 1.0f;
    float voiceVolume = 1.0f;
    float ambientVolume = 0.7f;

    // Audio quality
    int sampleRate = 44100;
    bool enableReverb = true;
    bool enable3DAudio = true;

    // Advanced
    bool enableSubtitles = true;
    bool muteWhenUnfocused = true;
};

class AudioSettingsManager {
public:
    void ApplySettings(const AudioSettings& settings) {
        this->settings = settings;

        // Apply to audio system
        audioSystem->SetMasterVolume(settings.masterVolume);
        audioSystem->SetMusicVolume(settings.musicVolume);
        audioSystem->SetSFXVolume(settings.sfxVolume);
        audioSystem->SetVoiceVolume(settings.voiceVolume);
        audioSystem->Enable3DAudio(settings.enable3DAudio);

        // Fire settings changed event
        DispatchEvent(ConfigAPI::AudioChangeEvent{settings});

        SaveToConfig();
    }

    // ... similar to GraphicsSettingsManager ...

private:
    AudioSettings settings;
};
```

### Gameplay Settings

```cpp
// GameplaySettings.h

struct GameplaySettings {
    // Difficulty
    int difficulty = 1;  // 0=Easy, 1=Normal, 2=Hard, 3=Legendary

    // HUD
    bool showHealthBar = true;
    bool showStaminaBar = true;
    bool showmagicBar = true;
    bool showCompass = true;
    bool showQuestMarkers = true;
    float hudOpacity = 1.0f;

    // Gameplay
    bool autoSave = true;
    int autoSaveInterval = 10;  // minutes
    bool fastTravel = true;
    bool showDamageNumbers = true;

    // Controls
    float mouseSensitivity = 1.0f;
    bool invertYAxis = false;
    float gamepadSensitivity = 1.0f;
};
```

---

## Console Variables (CVars)

### CVar System

```cpp
// CVar.h

// Console variable for runtime tweaking
class CVar {
public:
    enum Type {
        INT,
        FLOAT,
        BOOL,
        STRING
    };

    CVar(const char* name, int defaultValue)
        : name(name), type(INT), intValue(defaultValue) {}

    CVar(const char* name, float defaultValue)
        : name(name), type(FLOAT), floatValue(defaultValue) {}

    CVar(const char* name, bool defaultValue)
        : name(name), type(BOOL), boolValue(defaultValue) {}

    // Get value
    int GetInt() const { return type == INT ? intValue : 0; }
    float GetFloat() const { return type == FLOAT ? floatValue : 0.0f; }
    bool GetBool() const { return type == BOOL ? boolValue : false; }

    // Set value
    void SetInt(int value) {
        if (type == INT) {
            intValue = value;
            OnChanged();
        }
    }

    void SetFloat(float value) {
        if (type == FLOAT) {
            floatValue = value;
            OnChanged();
        }
    }

    void SetBool(bool value) {
        if (type == BOOL) {
            boolValue = value;
            OnChanged();
        }
    }

    const char* GetName() const { return name; }
    Type GetType() const { return type; }

private:
    const char* name;
    Type type;

    union {
        int intValue;
        float floatValue;
        bool boolValue;
    };

    void OnChanged() {
        // Fire CVar changed event
        DispatchEvent(ConfigAPI::CVarChangeEvent{name});
    }
};

class CVarManager {
public:
    // Register CVar
    void Register(CVar* cvar) {
        cvars[cvar->GetName()] = cvar;
    }

    // Get CVar
    CVar* Get(const char* name) {
        return cvars.contains(name) ? cvars[name] : nullptr;
    }

    // Set CVar from string (for console)
    void SetFromString(const char* name, const char* value) {
        CVar* cvar = Get(name);
        if (!cvar) return;

        switch (cvar->GetType()) {
            case CVar::INT:
                cvar->SetInt(std::stoi(value));
                break;
            case CVar::FLOAT:
                cvar->SetFloat(std::stof(value));
                break;
            case CVar::BOOL:
                cvar->SetBool(strcmp(value, "true") == 0 || strcmp(value, "1") == 0);
                break;
        }
    }

private:
    std::unordered_map<std::string, CVar*> cvars;
};

// Define CVars globally
CVar g_ShowFPS("r_showFPS", false);
CVar g_MaxFPS("r_maxFPS", 60);
CVar g_FOV("r_fov", 90.0f);
CVar g_GodMode("g_godMode", false);
```

---

## Hook Events

### Input Events

```cpp
// InputEvents.h

namespace InputAPI {

// Key press
struct KeyPressEvent : IGameEvent {
    KeyCode key;
    const char* GetCategory() const override { return "Input"; }
};

// Action triggered
struct ActionTriggeredEvent : IGameEvent {
    InputAction action;
    float value;  // For analog inputs
};

// Context changed
struct ContextChangeEvent : IGameEvent {
    InputContext oldContext;
    InputContext newContext;
};

// Binding changed
struct RebindEvent : IGameEvent {
    InputAction action;
    InputBinding oldBinding;
    InputBinding newBinding;
};

} // namespace InputAPI

/*
Event names:
"Input.Key.Press"
"Input.Key.Release"
"Input.Mouse.Move"
"Input.Action.Triggered"
"Input.Context.Changed"
"Input.Rebind"
*/
```

### Config Events

```cpp
// ConfigEvents.h

namespace ConfigAPI {

// Config value changed
struct ValueChangeEvent : IGameEvent {
    const char* category;
    const char* key;
    const char* newValue;
    bool* shouldCancel;
};

// Config reloaded
struct ReloadEvent : IGameEvent {
    const char* configPath;
};

// Settings categories
struct GraphicsChangeEvent : IGameEvent {
    GraphicsSettings settings;
};

struct AudioChangeEvent : IGameEvent {
    AudioSettings settings;
};

} // namespace ConfigAPI

/*
Event names:
"Config.Value.Change.Pre"
"Config.Value.Changed"
"Config.Reload"
"Config.Graphics.Changed"
"Config.Audio.Changed"
*/
```

---

## Console Commands

```cpp
// Input commands

REGISTER_CONSOLE_COMMAND(input_rebind, "Rebind input action") {
    if (args.size() < 3) {
        Console->Print("Usage: input.rebind <action> <device> <key>");
        return;
    }

    InputAction action = ParseAction(args[0]);
    DeviceType device = ParseDevice(args[1]);
    int key = std::stoi(args[2]);

    actionMapManager->Rebind(action, 0, device, key);
    Console->Print("Rebound %s to %s:%d", args[0], args[1], key);
}

REGISTER_CONSOLE_COMMAND(input_context, "Set input context") {
    if (args.size() < 1) {
        Console->Print("Usage: input.context <context>");
        return;
    }

    InputContext context = ParseContext(args[0]);
    contextManager->PushContext(context);
    Console->Print("Pushed context: %s", args[0]);
}

// Config commands

REGISTER_CONSOLE_COMMAND(config_get, "Get config value") {
    if (args.size() < 2) {
        Console->Print("Usage: config.get <category> <key>");
        return;
    }

    std::string value = configManager->Get<std::string>(args[0], args[1], "");
    Console->Print("%s.%s = %s", args[0], args[1], value.c_str());
}

REGISTER_CONSOLE_COMMAND(config_set, "Set config value") {
    if (args.size() < 3) {
        Console->Print("Usage: config.set <category> <key> <value>");
        return;
    }

    configManager->Set(args[0], args[1], args[2]);
    Console->Print("Set %s.%s = %s", args[0], args[1], args[2]);
}

REGISTER_CONSOLE_COMMAND(config_reload, "Reload config file") {
    configManager->LoadConfig();
    Console->Print("Config reloaded");
}
```

---

**Document Status:** Design v1.0
**Last Updated:** 2026-01-25
**Next Review:** After prototype phase
