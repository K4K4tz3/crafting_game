#include "voxel/voxelObject.h"

using namespace godot;

#pragma region Con-/Destructor

VoxelObject::VoxelObject () {

}
VoxelObject::~VoxelObject () {

}

#pragma endregion

#pragma region Public Methods

void VoxelObject::_ready() {
	UtilityFunctions::print(get_class(), ": is ready...");
	generateMesh();
	UtilityFunctions::print("has setGenerateNow? ", has_method(StringName("setGenerateNow")));
	UtilityFunctions::print("has generateMesh? ", has_method(StringName("generateMesh")));
	set("setGenerateNow", true);
}

#pragma endregion

#pragma region Protected Methods

void VoxelObject::_bind_methods() {
	UtilityFunctions::print("Voxel Object: Bind Methods...");

	// Add Methods

	UtilityFunctions::print("Voxel Object: All Methods Bound!");
}

#pragma endregion

#pragma region Private Methods

void VoxelObject::generateMesh() {
	setVertices();

	Ref<ArrayMesh> mesh;
	mesh.instantiate();

	m_objectMesh = memnew(MeshInstance3D);
	m_objectMesh->set_mesh(mesh);
	add_child(m_objectMesh);

	makeTriangles(mesh);
}

void VoxelObject::makeTriangles(Ref<ArrayMesh> a_mesh) {
	print_line("Voxel Object: Make Triangles...");
	const int vcount = m_triVerts.size();
	ERR_FAIL_COND(vcount % 3 != 0);
	UtilityFunctions::print("Voxel Object: VCount = ", vcount);	

	PackedVector3Array normals;
	normals.resize(vcount);

	PackedInt32Array indices;
	indices.resize(vcount);

	print_line("Voxel Object: Set Normals & Indices");
	for (int i = 0; i < vcount; i += 3) {
		const Vector3 &a = m_triVerts[i + 0];
		const Vector3 &b = m_triVerts[i + 1];
		const Vector3 &c = m_triVerts[i + 2];

		Vector3 n = (b - a).cross(c - a);
		real_t len = n.length();
		n = (len > (real_t)0.0) ? (n / len) : Vector3(0, 1, 0);

		normals.set(i + 0, n);
		normals.set(i + 1, n);
		normals.set(i + 2, n);

		indices.set(i + 0, i + 0);
		indices.set(i + 1, i + 1);
		indices.set(i + 2, i + 2);
	}

	print_line("Voxel Object: Set the Array");
	Array arrays;
	arrays.resize(Mesh::ARRAY_MAX);
	arrays[Mesh::ARRAY_VERTEX] = m_triVerts;
	arrays[Mesh::ARRAY_NORMAL] = normals;
	arrays[Mesh::ARRAY_INDEX] = indices;

	if (a_mesh->get_surface_count() > 0) {
		a_mesh->clear_surfaces();
	}
	a_mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);

	Ref<StandardMaterial3D> mat;
	mat.instantiate();
	mat->set_shading_mode(BaseMaterial3D::SHADING_MODE_UNSHADED);

	a_mesh->surface_set_material(0, mat);
}

void VoxelObject::setVertices() {
	// clear array
	if ( m_triVerts.size() > 0 )
		m_triVerts.clear();
	
	// create vertices
	m_triVerts.push_back(Vector3{0, 0, 0});
	m_triVerts.push_back(Vector3{0, 1, 0});
	m_triVerts.push_back(Vector3{1, 0, 0});

	m_triVerts.push_back(Vector3{0, 1, 0});
	m_triVerts.push_back(Vector3{1, 1, 0});
	m_triVerts.push_back(Vector3{1, 0, 0});
}

#pragma endregion
