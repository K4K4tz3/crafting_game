#ifndef EDITOR_H
#define EDITOR_H

#include <godot_cpp/classes/editor_plugin.hpp>

namespace godot {

class MyVoxelEditor : public EditorPlugin { 
	GDCLASS(MyVoxelEditor, EditorPlugin)


	Ref<EditorInspectorPlugin> inspector; 

protected:
	static void _bind_methods();

public:
	void _enter_tree() override;
	void _exit_tree() override;
	String _get_plugin_name() const override;
};

}

#endif
