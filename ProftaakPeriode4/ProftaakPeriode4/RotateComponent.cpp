#include "RotateComponent.h"
#include "GameObject.h"

RotateComponent::RotateComponent(Vec3f rotationFactor) : Component(ROTATE_COMPONENT)
{
	_rotationFactor = rotationFactor;
}

void RotateComponent::Update(float deltaTime)
{
	if (_parent != nullptr)
		_parent->_rotation += _rotationFactor * deltaTime;
}
