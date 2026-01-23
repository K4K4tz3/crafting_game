#include "playerController.h"



using namespace godot;

#pragma region Con-/Destructor

PlayerController::PlayerController() {
    setupDefaultInputs();
}
PlayerController::~PlayerController() {

}

#pragma endregion

#pragma region Protected Methods

void PlayerController::_bind_methods() {
    ClassDB::bind_method(D_METHOD("setMouseDebugState", "m_showMouseMotion"), &PlayerController::setMouseDebugState);
    ClassDB::bind_method(D_METHOD("getMouseDebugState"), &PlayerController::getMouseDebugState);

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "showMouseMotion"), "setMouseDebugState", "getMouseDebugState");

    // Mouse Speed
    ClassDB::bind_method(D_METHOD("setVerticalMouseSpeed", "m_verticalMouseSpeed"), &PlayerController::setVerticalMouseSpeed);
    ClassDB::bind_method(D_METHOD("getVerticalMouseSpeed"), &PlayerController::getVerticalMouseSpeed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Vertical Mouse Speed"), "setVerticalMouseSpeed", "getVerticalMouseSpeed");

    ClassDB::bind_method(D_METHOD("setHorizontalMouseSpeed", "m_horizontalMouseSpeed"), &PlayerController::setHorizontalMouseSpeed);
    ClassDB::bind_method(D_METHOD("getHorizontalMouseSpeed"), &PlayerController::getHorizontalMouseSpeed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Horizontal Mouse Speed"), "setHorizontalMouseSpeed", "getHorizontalMouseSpeed");

    // Vertical Camera Clamp
    ClassDB::bind_method(D_METHOD("setVerticalRotationMin", "m_verticalRotationMin"), &PlayerController::setVerticalRotationMin);
    ClassDB::bind_method(D_METHOD("getVerticalRotationMin"), &PlayerController::getVerticalRotationMin);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Vertical Rotation Clamp Min"), "setVerticalRotationMin", "getVerticalRotationMin");

    ClassDB::bind_method(D_METHOD("setVerticalRotationMax", "m_verticalRotationMax"), &PlayerController::setVerticalRotationMax);
    ClassDB::bind_method(D_METHOD("getVerticalRotationMax"), &PlayerController::getVerticalRotationMax);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Vertical Rotation Clamp Max"), "setVerticalRotationMax", "getVerticalRotationMax");

    // Move Speed
    ClassDB::bind_method(D_METHOD("setFowardSpeed", "m_forwardSpeed"), &PlayerController::setFowardSpeed);
    ClassDB::bind_method(D_METHOD("getForwardSpeed"), &PlayerController::getForwardSpeed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Forward Speed"), "setFowardSpeed", "getForwardSpeed");

    ClassDB::bind_method(D_METHOD("setSideSpeed", "m_sideSpeed"), &PlayerController::setSideSpeed);
    ClassDB::bind_method(D_METHOD("getSideSpeed"), &PlayerController::getSideSpeed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Side Speed"), "setSideSpeed", "getSideSpeed");
}

#pragma endregion

#pragma region Override Methods

void PlayerController::_ready() {
    set_position({0, 1, 0});
    try {
        m_camera = get_node<Camera3D>("Camera3D");
        m_camera->set_current(true);
        print_line("Set player camera as main");
    } catch (int errorCode) {
        print_error("Failed to set player camera as main");
    }

    Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);

    set_physics_process(true);
}

void PlayerController::_physics_process(double delta) {
    if (m_mouseInput != Vector2{}) {
        handleCamera(delta);

        m_mouseInput = Vector2{};
    }

    handleMove(delta);
}

void PlayerController::_input(const Ref<InputEvent> &a_event) {
    Ref<InputEventMouseMotion> mouseMotion = a_event;
    if (mouseMotion.is_valid()) {
        m_mouseInput = mouseMotion->get_relative();


    }

    Ref<InputEventKey> keyEvent = a_event;
    if (keyEvent.is_valid() && keyEvent->is_pressed()) {
        // Get Escape button -> enable disable movment
        if (keyEvent->get_keycode() == Key::KEY_ESCAPE) {
            Input::MouseMode mode = Input::get_singleton()->get_mouse_mode();
            if (mode == Input::MOUSE_MODE_CAPTURED) {
                Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
            }
            else {
                Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
            }
            m_enableMovement = !m_enableMovement;
        }
    }
}

#pragma endregion

#pragma region Getter/Setter

void PlayerController::setMouseDebugState(const bool a_debugState) {
    m_showMouseMotion = a_debugState;
}
bool PlayerController::getMouseDebugState() const {
    return m_showMouseMotion;
}

void PlayerController::setVerticalMouseSpeed(const float a_mouseSpeed) {
    m_verticalMouseSpeed = a_mouseSpeed;
}
float PlayerController::getVerticalMouseSpeed() const {
    return m_verticalMouseSpeed;
}

void PlayerController::setHorizontalMouseSpeed(const float a_mouseSpeed) {
    m_horizontalMouseSpeed = a_mouseSpeed;
}
float PlayerController::getHorizontalMouseSpeed() const {
    return m_horizontalMouseSpeed;
}

void PlayerController::setVerticalRotationMin(const float a_float) {
    m_verticalRotationMin = a_float;
}
float PlayerController::getVerticalRotationMin() const {
    return m_verticalRotationMin;
}

void PlayerController::setVerticalRotationMax(const float a_float) {
    m_verticalRotationMax = a_float;
}
float PlayerController::getVerticalRotationMax() const {
    return m_verticalRotationMax;
}

void PlayerController::setFowardSpeed(const float a_speed) {
    m_forwardSpeed = a_speed;
}
float PlayerController::getForwardSpeed() const {
    return m_forwardSpeed;
}

void PlayerController::setSideSpeed(const float a_speed) {
    m_sideSpeed = a_speed;
}
float PlayerController::getSideSpeed() const {
    return m_sideSpeed;
}

#pragma endregion

#pragma region Movement Control

void PlayerController::handleCamera(const double delta) {
    if (!m_enableMovement)
        return;

    // Set horizontal rotation
    Vector3 rotation_main = get_rotation();
    rotation_main.y += Math::deg_to_rad(-m_mouseInput.x * m_horizontalMouseSpeed * delta);
    set_rotation(rotation_main);

    // Set vertical rotation
    Vector3 rotation_camera = m_camera->get_rotation();
    rotation_camera.x += Math::deg_to_rad(-m_mouseInput.y * m_verticalMouseSpeed * delta);
    rotation_camera.x = Math::deg_to_rad(Math::clamp(Math::rad_to_deg(rotation_camera.x), m_verticalRotationMin, m_verticalRotationMax));
    m_camera->set_rotation(rotation_camera);
}

void PlayerController::handleMove(const double delta) {
    m_wasdInput.x = Input::get_singleton()->get_action_strength("move_forward") - Input::get_singleton()->get_action_strength("move_backward");
    m_wasdInput.y = Input::get_singleton()->get_action_strength("move_left") - Input::get_singleton()->get_action_strength("move_right");
    UtilityFunctions::print("Movement Input: X ( ", m_wasdInput.x, " )", " Y ( ", m_wasdInput.y, " )");
    // calculate & set velocity
    Vector3 forward = -get_global_transform().basis.get_column(2);
    Vector3 right = -get_global_transform().basis.get_column(0);
    Vector3 velocity = get_velocity();

    velocity = ((forward * m_wasdInput.x * m_forwardSpeed) + (right * m_wasdInput.y * m_sideSpeed)) * delta;
    UtilityFunctions::print("Velocity: ", velocity);
    set_velocity(velocity);
    move_and_slide();
}

Ref<InputEventKey> PlayerController::makeKey(const Key a_keycode) {
    Ref<InputEventKey> event;
    event.instantiate();
    event->set_keycode(a_keycode);
    return event;
}

void PlayerController::setupDefaultInputs() {
    InputMap* inputMap = InputMap::get_singleton();

    // create missing functions
    if (!inputMap->has_action("move_forward")) 
        inputMap->add_action("move_forward");
    if (!inputMap->has_action("move_backward")) 
        inputMap->add_action("move_backward");
    if (!inputMap->has_action("move_left")) 
        inputMap->add_action("move_left");
    if (!inputMap->has_action("move_right")) 
        inputMap->add_action("move_right");

    // Add keys to actions
    inputMap->action_add_event("move_forward", makeKey(Key::KEY_E));
    inputMap->action_add_event("move_backward", makeKey(Key::KEY_D));
    inputMap->action_add_event("move_left", makeKey(Key::KEY_S));
    inputMap->action_add_event("move_right", makeKey(Key::KEY_F));
}

#pragma endregion