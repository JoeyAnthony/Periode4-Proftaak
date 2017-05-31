#include "CollisionComponent.h"
#include <GL/freeglut.h>

Hitbox::Hitbox(Vec3f dimensions, Vec3f offset)
{
	_dimensions = dimensions;
	_offset = offset;
}

Hitbox::Hitbox(const Hitbox& other)
{
	_dimensions = other._dimensions;
	_offset = other._offset;
}

Hitbox::Hitbox()
{
	_dimensions = Vec3f();
	_offset = Vec3f();
}

CollisionComponent::CollisionComponent(Hitbox hitbox, bool isCollder) : Component(COLLISION_COMPONENT)
{
	_isCollider = isCollder;
	_hitboxes.push_back(hitbox);
}

CollisionComponent::CollisionComponent(std::vector<Hitbox> hitboxes, bool isCollider) : Component(COLLISION_COMPONENT)
{
	_isCollider = isCollider;
	_hitboxes = hitboxes;
}

bool CollisionComponent::CollidesWith(GameObject* other) const
{
	CollisionComponent * collider = dynamic_cast<CollisionComponent*>(other->GetComponent(COLLISION_COMPONENT));
	if (collider == nullptr) return false;

	// In order to check wether two 3dimensional boxes are colliding every axis has to 
	// be checked acording to this schematic:
	// (this.minX <= other.maxX && this.maxX >= other.minX) &&
	// (this.minY <= other.maxY && this.maxY >= other.minY) &&
	// (this.minZ <= other.maxZ && this.maxZ >= other.minZ);
	// In this implementation it is a bit more complex since the parameters originate from
	// multiple sources
	// See: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
	// This calculation has to be made for each hitbox in this gameObject and each collider hitbox
	// The function will however return true if a single hitbox is colliding.
	for (Hitbox hitbox : _hitboxes)
	{
		for (Hitbox otherHitBox : collider->_hitboxes) {

			if(
				// X-axis
				(_parent->_position.x + hitbox._offset.x - (hitbox._dimensions.x / 2) <= other->_position.x + otherHitBox._offset.x + (otherHitBox._dimensions.x / 2) &&
				_parent->_position.x + hitbox._offset.x + (hitbox._dimensions.x / 2) >= other->_position.x + otherHitBox._offset.x - (otherHitBox._dimensions.x / 2)) &&
				// Y-axis
				(_parent->_position.y + hitbox._offset.y - (hitbox._dimensions.y / 2) <= other->_position.y + otherHitBox._offset.y + (otherHitBox._dimensions.y / 2) &&
				_parent->_position.y + hitbox._offset.y + (hitbox._dimensions.y / 2) >= other->_position.y + otherHitBox._offset.y - (otherHitBox._dimensions.y / 2)) &&
				// Z-axis
				(_parent->_position.z + hitbox._offset.z - (hitbox._dimensions.z / 2) <= other->_position.z + otherHitBox._offset.z + (otherHitBox._dimensions.z / 2) &&
				_parent->_position.z + hitbox._offset.z + (hitbox._dimensions.z / 2) >= other->_position.z + otherHitBox._offset.z - (otherHitBox._dimensions.z / 2)))
			{
				return true;
			}
		}
	}

	return false;
}
