#include "Model.h"
#include <GL\freeglut.h>
#include "DrawComponent.h"
#include "CameraComponent.h"
#include "VisionComponent.h"
#include <iostream>
#include "MeshDrawComponent.h"
#include "MeshFactory.h"
#include "LaneGeneratorComponent.h"
#include "CollisionComponent.h"
#include "Collision.h"
#include "GUIComponent.h"
#include "bass.h"
#include "Sound.h"

//for testing purposes only, comment/delete when finished
#include "Text.h"
#include "LifeBar.h"
#include "LaneObstacleGenerator.h"
#include "LaneObstacleComponent.h"
#include "RotateComponent.h"

Model::Model()
{
	_gameOverTime = 0.0f;
	_lastTime = 0;
	_gameOver = false;
	
}

void Model::update()
{
	// Calculate the deltaTime
	float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = currentTime - _lastTime;
	_lastTime = currentTime;

	// deltaTime should never be allowed to be 0 or negative...
	if (deltaTime <= 0) deltaTime = 0.000001f;

	// Calculate and display fps
	// For performance profiling only
	// should normally be commented
    //	int fps = int(1.0 / deltaTime);
    //	std::cout << "Fps: " << fps << "DT: " << deltaTime << std::endl;

	// Call the Update of every GameObject
	for (GameObject * gameObject : _gameObjects)
	{
		gameObject->Update(deltaTime);
		if(!_gameOver) continue;
		if(GameOverState(deltaTime)) return;
	}

	Collision::CheckCollision(_gameObjects);

	// Call the LateUpdate of every Gameobject afterwards
	for(GameObject * gameObject : _gameObjects)
	{
		gameObject->LateUpdate(deltaTime);
	}

	// Update the GUI
	for (GameObject * gameObject : _guiObjects)
	{
		gameObject->Update(deltaTime);
	}

	for(GameObject * gameObject : _guiObjects)
	{
		gameObject->LateUpdate(deltaTime);
	}
	glutPostRedisplay();
}

void Model::InitSound()
{
	//Initialize audio
	int device = -1; // Default Sounddevice (default playback device from windows settings)
	int freq = 44100; // Sample rate (Hz)
	BASS_Init(device, freq, 0, nullptr, nullptr);

	//example on how to start sound(s)
	Sound * backgroundMusic = new Sound("Assets/background.wav", true);
	backgroundMusic->Play();

	//place this where the program closes
	//BASS_Free();
}

void Model::Init()
{
	_lastTime = 0;

	Reset();

	// Create GUI object
	GameObject * guiOb = new GameObject(&_gameObjects);
	GUIComponent * GUI = new GUIComponent();


	Text * distanceCounter = new Text(Vec3f(30, 25, 0), Vec3f(255, 255, 255), "Distance: 0000 m");
	GUI->AddElement(distanceCounter);

	Text * speedCounter = new Text(Vec3f(30, 40, 0), Vec3f(255, 255, 255), "Speed: 0000 m/s");
	GUI->AddElement(speedCounter);

	Image * powerUpImage = new Image(Vec3f(1280.0f / 4.0 + 60.0f, 45, 0), 20.0f, 20.0f, "Assets/LifeBar.psd"); // Todo replace LifeBar Image
	powerUpImage->Hide();
	GUI->AddElement(powerUpImage);


	Text * powerTimeLeft = new Text(Vec3f(1280.0f / 4.0 + 100.0f, 60, 0), Vec3f(255, 255, 255), "00:00");
	powerTimeLeft->Hide();
	GUI->AddElement(powerTimeLeft);

	Text * scoreText = new Text(Vec3f(670.0f, 40, 0), Vec3f(255, 255, 255), "Score: 0000 0x");
	GUI->AddElement(scoreText);

	Text * highscore = new Text(Vec3f(670.0f, 25, 0), Vec3f(255, 255, 255), "HighScore: 0000");
	GUI->AddElement(highscore);

	Image * diededImage = new Image(Vec3f(0.0f, 0.0f, 0), 1280.0f, 720.0f, "Assets/LifeBar.psd"); // todo replace LifeBar Image
	diededImage->Hide();
	GUI->AddElement(diededImage);

	LifeBar * lifebar = new LifeBar(
		Vec3f(1280.0f / 4.0 - 100.0f, 20, 0),
		400.0f, 20.0f, 3,
		"Assets/LifeFrameBackground.psd",
		"Assets/LifeFrame.psd",
		"Assets/LifeBar.psd",
		"Assets/LifeFrameSegment.psd");

	GUI->AddElement(lifebar);

	guiOb->AddComponent(GUI);

	_guiObjects.push_back(guiOb);

	// Create every other GameObject

	// Create and add the camera GameObject
	GameObject * camera = new GameObject(&_gameObjects);
	CameraComponent * cameraComponent = new CameraComponent(1280.0f, 720.0f, 0.1f, 300.0f, 90.0f, false);
	camera->_position = { 3.65f, 3.3f, -8.0f};
	camera->_rotation.x = 30.0f;
	camera->AddComponent(cameraComponent);

	_gameObjects.push_back(camera);

	// Create and add the skybox GameObject
	GameObject * skybox = new GameObject(&_gameObjects);
	DrawComponent * skyboxDrawComponent = new MeshDrawComponent(LoadMeshFile("Assets//Models//Skybox//skybox.Cobj"));
	skybox->_scale = { 25.0f, 25.0f, 25.0f };
	skybox->_lighting = false;
	skybox->AddComponent(skyboxDrawComponent);
	_gameObjects.push_back(skybox);
	
	// Create and add the Mars GameObject
	GameObject * mars = new GameObject(&_gameObjects);
	mars->AddComponent(new MeshDrawComponent(LoadMeshFile("Assets//Models//Mars//planet.Cobj")));
	mars->AddComponent(new RotateComponent({ 0.0f,1.0f,0.0f }));
	mars->_position = { -25.0f,5.0F,-75.0F};

	_gameObjects.push_back(mars);

	// Create and add the player GameObject
	int laneAmount = 3;
	GameObject * player = new GameObject(nullptr, { 0.0f,0.0f,-1.0f });
	PlayerComponent * playerComponent = new PlayerComponent(laneAmount / 2, laneAmount, lifebar, diededImage, this, false);
	player->AddComponent(playerComponent);
	player->AddComponent(new CollisionComponent(Hitbox({ 1,1,1 }))); // Hitbox
	player->AddComponent(new MeshDrawComponent(LoadMeshFile("Assets//Models//silver-hawk-next//shawk13.Cobj"))); // todo move out of scope
	LaneObstacleComponent * lanePlayer = new LaneObstacleComponent(laneAmount/2);
	lanePlayer->_speed = nullptr;
	player->_position.y = 2.0f;
	player->_position.z = -10.0f;
	player->AddComponent(lanePlayer);

	// Create and add the LaneGenerator GameObject
	float speed = 10.0f;
	std::vector<Mesh*> meshes;
	meshes.push_back(LoadMeshFile("Assets//Models//Lane//lanePart.Cobj"));
	std::vector<Mesh*> obstacles;
	obstacles.push_back(LoadMeshFile("Assets//Models//Asteroid//Asteroid_LemoineM.Cobj"));


	GameObject * laneGenerator = new GameObject(&_gameObjects);
	LaneGeneratorComponent * laneDrawComponent = new LaneGeneratorComponent(3, 20, 2.0f, meshes, player);
	LaneObstacleGenerator * lane_obstacle_generator = new LaneObstacleGenerator(obstacles, &laneDrawComponent->_speed);

	laneGenerator->AddComponent(laneDrawComponent);
	laneGenerator->AddComponent(lane_obstacle_generator);
	_gameObjects.push_back(laneGenerator);

	GameObject * scoreObject = new GameObject(&_gameObjects);
	//Scoreboard that keeps track of the scores
	ScoreBoardComponent * scoreBoard = new ScoreBoardComponent();
	ScoreComponent * tempScore;

    scoreBoard->LoadScore();

    if (!scoreBoard->_scores.empty())
        tempScore = new ScoreComponent(&laneDrawComponent->_speed, scoreBoard->_scores[0]->score);
    else
        tempScore = new ScoreComponent(&laneDrawComponent->_speed, 0);

    tempScore->_scoreText = scoreText;
    tempScore->_highscoreText = highscore;

    scoreObject->AddComponent(tempScore);
    scoreObject->AddComponent(scoreBoard);
    scoreBoard->AddScore(tempScore->ReturnScoreStruct());

    _gameObjects.push_back(scoreObject);

}

void Model::Reset()
{
	_gameOver = false;
	_gameOverTime = 0.0f;
	_gameObjects.clear();
	_guiObjects.clear();
}

bool Model::GameOverState(float deltaTime)
{
	_gameOverTime += deltaTime;
	if(_gameOverTime >= 5.0f)
	{
		Init();
		return true;
	}
	return false;
}
