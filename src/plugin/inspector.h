#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <godot_cpp/classes/editor_inspector_plugin.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

namespace godot {

class Inspector : public EditorInspectorPlugin {
	GDCLASS(Inspector, EditorInspectorPlugin)

protected:
	static void _bind_methods();

public:
	bool _can_handle(Object *object) const override;
	void _parse_begin(Object *object) override;

private:
	void _on_generate_pressed(Object *object);

};

}

#endif
