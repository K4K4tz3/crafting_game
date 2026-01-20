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

}

//
// Override Methods
//

void PlayerController::_ready() {
    try {
        m_camera = get_node<Camera3D>("Camera3D");
        m_camera->set_current(true);
        print_line("Set player camera as main");
    } catch (int errorCode) {
        print_error("Failed to set player camera as main");
    }
}

void PlayerController::_input(const Ref<InputEvent> &a_event) {
    Ref<InputEventMouseMotion> mouseMotion = a_event;
    if (mouseMotion.is_valid()) {
        Vector2 rel = mouseMotion->get_relative();
        UtilityFunctions::print("X: ", rel.x, " Y: ", rel.y);
    }
}

//
// Public Methods
//