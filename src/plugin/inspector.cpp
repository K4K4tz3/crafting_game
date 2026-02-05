#include "plugin/inspector.h"
#include "voxel/voxelObject.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Inspector::_bind_methods() {
}

bool Inspector::_can_handle(Object *object) const {
	UtilityFunctions::print("Inspector handling object");
	return Object::cast_to<VoxelObject>(object) != nullptr;
}

void Inspector::_parse_begin(Object *object) {
	UtilityFunctions::print("Inspector parsing object");
	auto *lab = Object::cast_to<VoxelObject>(object);
	if (!lab) return;

	// Container for ui
	auto *box = memnew(VBoxContainer);
	auto *btn = memnew(Button);
	btn->set_text("Generate");

	btn->connect("pressed", callable_mp(this, &Inspector::_on_generate_pressed));
	box->add_child(btn);

	add_custom_control(box);
}

void Inspector::_on_generate_pressed(Object *object) {
	UtilityFunctions::print("Button Pressed"); }

