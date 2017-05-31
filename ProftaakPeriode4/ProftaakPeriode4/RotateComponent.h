#pragma once
#include "Component.h"
#include "Vec.h"

class RotateComponent : public Component
{
public:
	RotateComponent(Vec3f rotationFactor);


	void Update(float deltaTime) override;
private:
	Vec3f _rotationFactor;
};
