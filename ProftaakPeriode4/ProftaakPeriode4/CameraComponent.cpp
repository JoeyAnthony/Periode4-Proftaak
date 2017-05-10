#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <cmath>
// #include "Component.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "Vec.h"
#include "Input.h"

CameraComponent::CameraComponent(float  width, float height, float nearPlane, float farPlane, float fov)
: Component(CAMERA_COMPONENT)
{
	_screenWidth = width;
	_screenHeight = height;

	_nearPlane = nearPlane; 
	_farPlane = farPlane;

	_fov = fov;
}

void CameraComponent::Move(float angle, float fac)
{
	_parent->_position.x += (float)cos((_parent->_rotation.y + angle) / 180.0f * M_PI) * fac;
	_parent->_position.y += (float)sin((_parent->_rotation.y + angle) / 180.0f * M_PI) * fac;
}

void CameraComponent::Up(float fac)
{
	_parent->_position.z -= fac;
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update(float deltaTime)
{
	Vec2i mousePos(Mouse::GetMousePos());
	const bool * keys = Keyboard::GetKeyboard();

	const float speed = 10.0f;
	if (keys['a']) Move(0, deltaTime*speed);
	if (keys['d']) Move(180, deltaTime*speed);
	if (keys['w']) Move(90, deltaTime*speed);
	if (keys['s']) Move(270, deltaTime*speed);
	if (keys['q']) Up(deltaTime*-speed);
	if (keys['e']) Up(deltaTime*speed);


	// Calculate mouse movement and reset mouse
	float dx = float(mousePos.x) - _screenWidth/ 2;
	float dy = float(mousePos.y) - _screenHeight/ 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		_parent->_rotation.y += dx / 10.0f;
		_parent->_rotation.x += dy / 10.0f;
		glutWarpPointer(int(_screenWidth / 2), int(_screenHeight / 2));
	}
}

void CameraComponent::ApplyCamera() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Apply camera settings
	gluPerspective(_fov, _screenWidth / float(_screenHeight), _nearPlane, _farPlane);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Rotate and translate the camera
	glRotatef(_parent->_rotation.x, 1, 0, 0);
	glRotatef(_parent->_rotation.y, 0, 1, 0);
	glTranslatef(_parent->_position.x, _parent->_position.z, _parent->_position.y);
}