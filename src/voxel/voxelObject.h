#ifndef VOXEL_OBJECT_HPP
#define VOXEL_OBJECT_HPP

#include <godot_cpp/classes/node3D.hpp>
#include <godot_cpp/variant/packed_vector3_array.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/variant/packed_int32_array.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

namespace godot {

class VoxelObject : public Node3D {
    GDCLASS(VoxelObject, Node3D);

private:
	PackedVector3Array m_triVerts;
	MeshInstance3D *m_objectMesh = nullptr;

	bool generateNow = false;

	void generateMesh();
	void makeTriangles(Ref<ArrayMesh> mesh);
	void setVertices();

protected:
    static void _bind_methods();

public:
    VoxelObject();
    ~VoxelObject();

    void _ready() override;

    void test() { UtilityFunctions::print("hello"); };
};

}

#endif
