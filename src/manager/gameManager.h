#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <godot_cpp/classes/node3d.hpp>

#include "player/playerController.h"

namespace godot {

class GameManager : public Node3D {
    GDCLASS(GameManager, Node3D)

private:
    PlayerController* player = nullptr;

protected:
    static void _bind_methods();

public:
    GameManager();
    ~GameManager();

    void _ready() override;

};

}

#endif