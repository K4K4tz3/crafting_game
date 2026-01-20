#include "gameManager.h"

#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

//
// Con-/Destructor
//
GameManager::GameManager() {

}
GameManager::~GameManager() {

}

//
// Protected Functions
//
void GameManager::_bind_methods() {

}


//
// Public Functions
//
void GameManager::_ready() {
    print_line("GameManager is ready");
    print_line("Attempting to spawn player...");

    // Load Player Resource
    Ref<PackedScene> player_prefab = ResourceLoader::get_singleton()->load("res://prefab/player.tscn");
    if (player_prefab.is_null())
        print_error("Failed to load Player Prefab");
    else
        print_line("Loaded Player Prefab");
    
    // Instantiate under gameManager
    if (player_prefab->can_instantiate()) {
        print_line("Instantiate Player");
        Node *instance = player_prefab->instantiate();

        add_child(instance);
    }
    else
        print_error("Failed to Instantiate Player");
}