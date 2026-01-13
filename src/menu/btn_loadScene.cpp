#include "btn_loadScene.h"
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

//
// Con-/Destructor
//

Btn_LoadScene::Btn_LoadScene() {

}

Btn_LoadScene::~Btn_LoadScene() {

}

void Btn_LoadScene::_ready() {
    connect("pressed", Callable(this, "on_pressed"));
}

//
// Protected Functions
//

void Btn_LoadScene::_bind_methods() {
    ClassDB::bind_method(D_METHOD("on_pressed"), &Btn_LoadScene::on_pressed);

    ClassDB::bind_method(D_METHOD("setState", "state"), &Btn_LoadScene::setState);
    ClassDB::bind_method(D_METHOD("getState"), &Btn_LoadScene::getState);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "state"), "setState", "getState");

    ClassDB::bind_method(D_METHOD("setScene", "scene"), &Btn_LoadScene::setScene);
    ClassDB::bind_method(D_METHOD("getScene"), &Btn_LoadScene::getScene);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "scene"), "setScene", "getScene");
}

//
// Public Functions
//

void Btn_LoadScene::on_pressed() {
    print_line("Close Game");
    get_tree()->quit();
}

void Btn_LoadScene::setState(String a_state) {
    state = a_state;
}
String Btn_LoadScene::getState() const {
    return state;
}
void Btn_LoadScene::setScene(String a_scene) {
    scene = a_scene;
}
String Btn_LoadScene::getScene() const {
    return scene;
}