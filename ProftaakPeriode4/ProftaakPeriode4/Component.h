#pragma once

class GameObject;

// Enum which will indicate the functionality of a Component
enum ComponentID
{
	GUI_COMPONENT,
	SCORE_COMPONENT,
	CAMERA_COMPONENT,
	DRAW_COMPONENT,
	VISION_COMPONENT,
	COLLISION_COMPONENT,
    SCOREBOARD_COMPONENT,
	LANE_OBSTACLE_COMPONENT,
	PLAYER_COMPONENT,
	LANE_COMPONENT,
	LANE_OBSTACLE_GENERATOR,
	ASTEROID_COMPONENT,
	ROTATE_COMPONENT,
    LANE_GENERATOR_COMPONENT,
    POWER_UP_COMPONENT,
};

class Component
{
public:
	// Base Constructor for a component
	// if a class overrides this function it's important to
	// still call this function to make sure the id is set
	// @param Component id: the if of the Component
	// @param GameObject * parent: the paren GameObject of this Component
	explicit Component(ComponentID id);

	// Base Destructor for a component
	// TODO Add base Destructor functionality
	virtual ~Component();

	// Update is called as often as possible
	// @param float deltaTime: the time in milliseconds between the current and last frame
	virtual void Update(float deltaTime);

	// LateUpdate is also called as often as possible,
	// but always after the Update of EVERY GameObject
	// has been called
	// @param float deltaTime: the time in milliseconds between the current and last frame
	virtual void LateUpdate(float deltaTime);

	virtual void Draw();

	// Set the parent GameObject for this component
	// This is usefull, because this allows the component
	// to communicate with other components in it's parent GameObject
	// @param GameObject *: the pointer to the parent GameObject
	virtual void SetParent(GameObject * parent);

	// The identifier of the component
	ComponentID _id;
protected:
	// Pointer to the parent GameObject of this Component
	GameObject * _parent;
};

