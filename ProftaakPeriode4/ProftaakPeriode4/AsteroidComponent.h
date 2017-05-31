#pragma once
#include "Component.h"
#include "Vec.h"

class AsteroidComponent : public Component
{
public:
	AsteroidComponent();
	
	void Update(float deltaTime) override;
private:
	Vec3f _rotationFactor;
};
