#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/input_event_key.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/transform3d.hpp>


namespace godot {

class PlayerController : public Node3D {
    GDCLASS(PlayerController, Node3D);

private:
    Camera3D* m_camera = nullptr;

    // debug
    bool m_showMouseMotion = false;

    
    float m_verticalMouseSpeed = 10.0f;
    float m_horizontalMouseSpeed = 10.0f;


    bool m_enableMovement = true;
    Vector2 m_mouseInput = {0, 0};

    void handleCamera(const double delta);

protected:
    static void _bind_methods();

public:
    PlayerController();
    ~PlayerController();

    void _ready() override;
    void _process(double delta) override;
    void _input(const Ref<InputEvent> &a_event);

    void setMouseDebugState(const bool a_debugState);
    bool getMouseDebugState() const;

    void setVerticalMouseSpeed(const float a_mouseSpeed);
    float getVerticalMouseSpeed() const;
    void setHorizontalMouseSpeed(const float a_mouseSpeed);
    float getHorizontalMouseSpeed() const;
};

}

#endif