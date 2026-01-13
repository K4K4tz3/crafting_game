#ifndef BTN_LOAD_SCENE_H
#define BTN_LOAD_SCENE_H

#include <godot_cpp/classes/texture_button.hpp>

namespace godot {

class Btn_LoadScene : public TextureButton {
    GDCLASS(Btn_LoadScene, TextureButton)

private:
    String state = "";
    String scene = "";

protected:
    static void _bind_methods();

public:
    Btn_LoadScene();
    ~Btn_LoadScene();

    void _ready() override;

    void on_pressed();

    void setState(String a_state);
    String getState() const;
    void setScene(String a_scene);
    String getScene() const;
};

}

#endif