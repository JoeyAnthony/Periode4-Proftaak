#pragma once

#include <vector>
// #include "Component.h"
#include "GameObject.h"
#include "ScoreBoard.h"

class Model {
public:
    // Constructor for Model
    // Initialises _lastTime as 0
    Model();

    // Update the model by calling Update and LateUpdate
    // of every GameObject present in the model
    void update();

	/*
	 * Initialise audio for game
	 * Is static for not needing other data
	 */
	static void InitSound();

    // Initialise the gameLogic
    // NOTE: should ONLY be called AFTER an OpenGL context has been created
    // and ONLY ONCE
    void Init();

    // Vector of every GameObject present in the model
    std::vector<GameObject*> _gameObjects;
	std::vector<GameObject*> _guiObjects;

	bool _gameOver;
private:

	/**
	 * \brief Reset the Model by clearing all the list and resetting the variables
	 */
	void Reset();
	/**
	 * \brief Update the gameOverState. Here everything should be done when the game is over but still running
	 * TODO: Currently it will just reset after 5 seconds, but in the future we may want to do more.
	 * \param deltaTime The deltaTime since the last frame
	 * \return wether the gameLoop should continue updating the gameObjects
	 */
	bool GameOverState(float deltaTime);
    // The last time a frame was rendered in milliseconds
    float _lastTime;

	/**
	 * \brief the time spent in the gameOverstate
	 */
	float _gameOverTime = 0.0f;
};
