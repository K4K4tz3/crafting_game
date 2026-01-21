#include "playerController.h"



using namespace godot;

//
// Con-/Destructor
//
PlayerController::PlayerController() {

}
PlayerController::~PlayerController() {

}

//
// Protected Methods
//

void PlayerController::_bind_methods() {
    ClassDB::bind_method(D_METHOD("setMouseDebugState", "m_showMouseMotion"), &PlayerController::setMouseDebugState);
    ClassDB::bind_method(D_METHOD("getMouseDebugState"), &PlayerController::getMouseDebugState);

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "showMouseMotion"), "setMouseDebugState", "getMouseDebugState");

    ClassDB::bind_method(D_METHOD("setVerticalMouseSpeed", "m_verticalMouseSpeed"), &PlayerController::setVerticalMouseSpeed);
    ClassDB::bind_method(D_METHOD("getVerticalMouseSpeed"), &PlayerController::getVerticalMouseSpeed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Vertical Mouse Speed"), "setVerticalMouseSpeed", "getVerticalMouseSpeed");

    ClassDB::bind_method(D_METHOD("setHorizontalMouseSpeed", "m_horizontalMouseSpeed"), &PlayerController::setHorizontalMouseSpeed);
    ClassDB::bind_method(D_METHOD("getHorizontalMouseSpeed"), &PlayerController::getHorizontalMouseSpeed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Horizontal Mouse Speed"), "setHorizontalMouseSpeed", "getHorizontalMouseSpeed");
}

//
// Override Methods
//

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

    set_process(true);
}

void PlayerController::_process(double delta) {
    if (m_mouseInput != Vector2{}) {
        handleCamera(delta);

        m_mouseInput = Vector2{};
    }
}

void PlayerController::_input(const Ref<InputEvent> &a_event) {
    Ref<InputEventMouseMotion> mouseMotion = a_event;
    if (mouseMotion.is_valid()) {
        m_mouseInput = mouseMotion->get_relative();


    }

    Ref<InputEventKey> keyEvent = a_event;
    if (keyEvent.is_valid() && keyEvent->is_pressed()) {
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

//
// Getter/Setter Methods
//
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

// 
// Movement control
//
void PlayerController::handleCamera(const double delta) {
    if (!m_enableMovement)
        return;

    if (m_showMouseMotion) // debug mouse motion
        UtilityFunctions::print("X: ", m_mouseInput.x, " Y: ", m_mouseInput.y);
    // Set horizontal rotation
    Vector3 rotation_main = get_rotation();
    rotation_main.y += Math::deg_to_rad(-m_mouseInput.x * m_horizontalMouseSpeed * delta);
    set_rotation(rotation_main);

    // Set vertical rotation
    Vector3 rotation_camera = m_camera->get_rotation();
    rotation_camera.x += Math::deg_to_rad(-m_mouseInput.y * m_verticalMouseSpeed * delta);
    m_camera->set_rotation(rotation_camera);
}