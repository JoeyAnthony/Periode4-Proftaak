#pragma once
#include "Component.h"

class CameraComponent : public Component
{
public:
	// Constructor
	// @param float width: width of the openGL window
	// @param float height: height of the openGL window
	// @param float nearPlane: the near clipping plane of the camera
	// @param float farPlane: the far clipping plane of the camera
	// @param float fov: the fov of the camera
	CameraComponent(float width, float height, float nearPlane, float farPlane, float fov, bool useKeys = true);
	
	// Destructor
	~CameraComponent();
	
	// Overriden Update function from component
	// changes the parents _position and rotation based
	// on keyboard an mouse input
	// @param float deltaTime: the time in milliseconds between this and the last frame
	void Update(float deltaTime) override;
	
	// Apply the camera _position and rotation to the view
	void ApplyCamera() const;

	// The with and height of the openGL window
	float _screenWidth;
	float _screenHeight;

	// the near and far clipping plane
	float _nearPlane;
	float _farPlane;

	// The camera's fov
	float _fov;

	bool _useKeys;
private:
	// Translate the camera horizontally
	// @param float angle: the angle at which the camera will be translated
	// @param float fac: the amount the camera will translated
	void Move(float angle, float fac);

	// Translate the camera vertically
	// @param float fac: the amound the camera will be translated
	void Up(float fac);
};
