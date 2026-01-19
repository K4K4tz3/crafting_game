#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <godot_cpp/classes/node3d.hpp>

namespace godot {

class PlayerController : public Node3D {
    GDCLASS(PlayerController, Node3D);

private:

protected:
    static void _bind_methods();

public:
    PlayerController();
    ~PlayerController();
};

}

#endif