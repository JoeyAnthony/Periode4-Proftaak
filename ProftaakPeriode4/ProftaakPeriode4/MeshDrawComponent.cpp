#include "MeshDrawComponent.h"
#include "GameObject.h"

MeshDrawComponent::MeshDrawComponent(Mesh* mesh) : DrawComponent()
{
	_mesh = mesh;
}

MeshDrawComponent::~MeshDrawComponent()
{
	// todo implement destructor
}

void MeshDrawComponent::Draw()
{
	if (_parent != nullptr) 
		_mesh->Draw(_parent->_position, _parent->_rotation, _parent->_scale, _parent->_lighting);
}
