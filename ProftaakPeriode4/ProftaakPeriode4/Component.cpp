#include "Component.h"

Component::Component(ComponentID id)
{
	_id = id;
	_parent = nullptr;
}

Component::~Component()
{
	// TODO destructor stuff
}

void Component::Update(float deltaTime)
{
}

void Component::LateUpdate(float deltaTime)
{
}

void Component::Draw()
{
}

void Component::SetParent(GameObject* parent)
{
	_parent = parent;
}
