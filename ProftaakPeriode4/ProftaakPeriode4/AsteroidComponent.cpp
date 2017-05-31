#include "AsteroidComponent.h"
#include <cstdlib>
#include <ctime>
#include "GameObject.h"

AsteroidComponent::AsteroidComponent() : Component(ASTEROID_COMPONENT)
{
	srand(time(nullptr));
	int factor = 100;

	_rotationFactor = {
		float(rand() % factor - factor/2),
		float(rand() % factor - factor/2),
		float(rand() % factor - factor/2),
	};
}

void AsteroidComponent::Update(float deltaTime)
{
	_parent->_rotation += _rotationFactor * deltaTime;
}
