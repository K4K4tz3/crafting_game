#include "plugin/editor.h"
#include "plugin/inspector.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void MyVoxelEditor::_bind_methods() {
}

void MyVoxelEditor::_enter_tree() {
	UtilityFunctions::print("Plugin entered tree");
	inspector.instantiate();
	add_inspector_plugin(inspector);
}

void MyVoxelEditor::_exit_tree() {
	UtilityFunctions::print("Plugin exiting tree");
	if (inspector.is_valid()) {
		remove_inspector_plugin(inspector);
	}
}

String MyVoxelEditor::_get_plugin_name() const {
	return "MyVoxelEditor";
}
