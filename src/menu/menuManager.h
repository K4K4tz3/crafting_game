#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <godot_cpp/classes/node.hpp>

namespace godot {

class MenuManager : public Node {
    GDCLASS(MenuManager, Node)

protected:
    static void _bind_methods();
public:
    MenuManager();
    ~MenuManager();

};

}

#endif