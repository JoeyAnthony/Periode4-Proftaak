#include "LaneGeneratorComponent.h"
#include "LaneObstacleComponent.h"
#include "LaneComponent.h"
#include <iostream>
#include <queue>
#include "GameObject.h"
#include "MeshDrawComponent.h"
#include "PlayerComponent.h"
#include "CollisionComponent.h"
#include "Collision.h"
#include "MeshFactory.h"

Mesh * mesh;
float meshTime = 0.0f;

LaneGeneratorComponent::LaneGeneratorComponent(int laneAmount, int laneSize, std::vector<Mesh*> meshes)
{
	srand(unsigned int(time(nullptr))); // set fully random (on time)

						  // Testing
	mesh = LoadMeshFile("Assets//Models//TestCube//Cube.Cobj");

	_spaceBetween = 2.0f;

	for (int i = 0; i < laneAmount; i++)
	{
		GameObject * lane = new GameObject(&_lanes);
		lane->AddComponent(new LaneComponent(laneSize, meshes));
		lane->_position.x += i * (meshes[0]->_width + _spaceBetween);

		_lanes.push_back(lane);
	}

	// Create and add the player GameObject
	_player = new GameObject(&_obstacles);
	_player->AddComponent(new PlayerComponent(1, laneAmount, false));
	_player->AddComponent(new CollisionComponent(Hitbox({ 2,2,2 })));
	_player->AddComponent(new MeshDrawComponent(mesh));
	LaneObstacleComponent * lanePlayer = new LaneObstacleComponent(1);
	lanePlayer->_speed = 0.0f;
	_player->AddComponent(lanePlayer);
	_player->_position = { 0.0f,0.0f,-1.0f };

	_obstacles.push_back(_player);
}

LaneGeneratorComponent::~LaneGeneratorComponent()
{
}

void LaneGeneratorComponent::Draw()
{
	// Draw the lanes
	for (int i = 0; i < _lanes.size(); i++) {
		LaneComponent * lane = dynamic_cast<LaneComponent*>(
			_lanes.at(i)->GetComponent(LANE_COMPONENT));
		if(lane == nullptr) continue;

		lane->Draw();
	}
	// Draw the obstacles
	for(GameObject * obstacle : _obstacles)
	{
		obstacle->Draw();
	}
}

void LaneGeneratorComponent::Update(float deltaTime)
{
	meshTime += deltaTime;
	if(meshTime >= 1.0f)
	{
		meshTime = 0.0f;
		PlaceObstacleFullyRandom(mesh);
	}

	// Update and move the player
	_player->Update(deltaTime);
	PlayerComponent * player
		= dynamic_cast<PlayerComponent*>(_player->GetComponent(PLAYER_COMPONENT));
	if(player != nullptr && player->_lastLane != player->_laneIndex)
	{
		_player->_position.x = _lanes[player->_laneIndex]->_position.x;
		player->_lastLane = player->_laneIndex;
	}

	for(int i = 0; i < _obstacles.size(); i++)
	{
		_obstacles[i]->Update(deltaTime);
		// Remove out of bounds object
		if(_obstacles[i]->_position.z >= 0)
		{
			_obstacles.erase(_obstacles.begin() + i);
		}
	}

	// Update the lanes
	for (int i = 0; i < _lanes.size(); i++) {
		_lanes.at(i)->Update(deltaTime);
	}

	// Check collisions
	Collision::CheckCollision(_obstacles);
	CollisionComponent * collider
		= dynamic_cast<CollisionComponent*>(_player->GetComponent(COLLISION_COMPONENT));
	if(collider->_collided.size() > 0)
	{
		// Player collided with an obstacle
		// TODO reduce health
		std::cout << "player collision" << std::endl;
	}
}

void LaneGeneratorComponent::PlaceObstacleFullyRandom(Mesh* mesh)
{
	if (_lanes.size() == 0) // do nothing when no lanes visible
		return;

	int laneIndex = rand() % _lanes.size();
	
	LaneComponent * lane = dynamic_cast<LaneComponent*>(_lanes[laneIndex]->GetComponent(LANE_COMPONENT));
	float lenght; 
	if (lane != nullptr)
		lenght = lane->getLength() * -1;
	else
		lenght = -200.0f;

	// Create the obstacle
	GameObject * obstacle = new GameObject(&_obstacles);
	obstacle->AddComponent(new MeshDrawComponent(mesh));
	obstacle->AddComponent(new LaneObstacleComponent(laneIndex));
	obstacle->AddComponent(new CollisionComponent(Hitbox({ 1.0f,1.0f,1.0f }), false));
	obstacle->_position = { 
		_lanes[laneIndex]->_position.x,
		_lanes[laneIndex]->_position.y + mesh->_height/2,
		-100.0f};
	_obstacles.push_back(obstacle);
}


