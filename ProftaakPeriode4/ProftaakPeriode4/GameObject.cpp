#include "GameObject.h"
#include "DrawComponent.h"

GameObject::GameObject(std::vector<GameObject *> * gameObjects, Vec3f position, Vec3f rotation, Vec3f scale)
{
	_lighting = true;
	_position = position;
	_rotation = rotation;
    _parentList = gameObjects;
	_scale = scale;
}

void GameObject::Update(float deltaTime)
{
	for (Component * component : _components)
	{
		component->Update(deltaTime);
	}
}

void GameObject::LateUpdate(float deltaTime)
{
	for(Component * component : _components)
	{
		component->LateUpdate(deltaTime);
	}
}


void GameObject::SetPosition(Vec3f position)
{
	_position = Vec3f(position);
}

void GameObject::Rotate(Vec3f rotation)
{
	_rotation.x += rotation.x;
	_rotation.y += rotation.y;
	_rotation.z += rotation.z;
}

void GameObject::SetRotation(Vec3f rotation)
{
	_rotation = Vec3f(rotation);
}

void GameObject::Scale(Vec3f scale)
{
	_scale.x += scale.x;
	_scale.y += scale.y;
	_scale.z += scale.z;
}

void GameObject::SetScale(Vec3f scale)
{
	_scale = Vec3f(scale);
}

void GameObject::SetLighting(bool lighting)
{
	_lighting = lighting;
}

void GameObject::Draw() const
{
	for (Component * component : _components)
		component->Draw();
}

Component * GameObject::GetComponent(ComponentID id)
{
	for (Component * component : _components)
	{
		// Component is found so it's reference is returned
		if (component->_id == id)
		{
			return component;
		}
	}
	// The component was not found so a nullptr is returned
	return nullptr;
}

void GameObject::AddComponent(Component * component)
{
	component->SetParent(this);
	_components.push_back(component);
}

bool GameObject::RemoveComponent(Component* component)
{
	// TODO implement
	return false;
}
