#pragma once
#include "DrawComponent.h"
#include "LifeBar.h"
#include "Mesh.h"
#include <queue>
#include <ctime>
#include "PlayerComponent.h"

/**
* \brief Class for generating and showing lanes
*/
class LaneGeneratorComponent :
    public DrawComponent
{
public:
    /*
    * The speed of the moving objects
    */
    float _speed = 9.0f;
	/**
	 * \brief Constructor for creating a LaneGaneratorComponent
	 * \param laneSize The amount of lanes to show
	 * \param laneSize the amount of blocks inside the lane (the length)
	 * \param meshes The meshes that are chosen randomly over all the lanes
	 * \param playerComponent pointer to the playerComponent which is used on the lanes
	 */

	LaneGeneratorComponent(int laneCount, int laneSize, float spaceBetweem, std::vector<Mesh*> meshes, GameObject * playerObject);
	/**
	 * \brief Destructor
	 * todo implement
	 */
	~LaneGeneratorComponent();
	/**
	 * \brief Draw the lanes
	 */
	void Draw() override;
	/**
	 * \brief Update the laneLogics (move the lanes)
	 * \param deltaTime The difference between the updates
	 */
	void Update(float deltaTime) override;

	/*
	* The lanes that are shown in the component
	* Are filled in constructor (given amount)
	*/
	vector<GameObject*> _lanes;

	vector<GameObject*> _obstacles;
	GameObject * _player;

private:
	
	/*
	 * The space between the lanes
	 */
	float _spaceBetween = 2.0f;
};
