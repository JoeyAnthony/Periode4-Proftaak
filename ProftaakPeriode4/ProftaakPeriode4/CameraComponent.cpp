#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <cmath>
// #include "Component.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "Vec.h"
#include "Input.h"

CameraComponent::CameraComponent(float  width, float height, float nearPlane, float farPlane, float fov, bool useKeys)
: Component(CAMERA_COMPONENT)
{
	_screenWidth = width;
	_screenHeight = height;

	_nearPlane = nearPlane; 
	_farPlane = farPlane;

	_fov = fov;
	_useKeys = useKeys;
}

void CameraComponent::Move(float angle, float fac)
{
	_parent->_position.x -= (float)cos((_parent->_rotation.y + angle) / 180.0f * M_PI) * fac;
	_parent->_position.z -= (float)sin((_parent->_rotation.y + angle) / 180.0f * M_PI) * fac;
}

void CameraComponent::Up(float fac)
{
	_parent->_position.y += fac;
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update(float deltaTime)
{
	Vec2i mousePos(Mouse::GetMousePos());
	const bool * keys = Keyboard::GetKeyboard();

	const float speed = 10.0f;
	if (_useKeys) {
		if (keys['a']) Move(0, deltaTime*speed);
		if (keys['d']) Move(180, deltaTime*speed);
		if (keys['w']) Move(90, deltaTime*speed);
		if (keys['s']) Move(270, deltaTime*speed);
		if (keys['q']) Up(deltaTime*-speed);
		if (keys['e']) Up(deltaTime*speed);

		// Calculate mouse movement and reset mouse
		float dx = float(mousePos.x) - _screenWidth / 2;
		float dy = float(mousePos.y) - _screenHeight / 2;
		if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
		{
			_parent->_rotation.y += dx / 10.0f;
			_parent->_rotation.x += dy / 10.0f;
			glutWarpPointer(int(_screenWidth / 2), int(_screenHeight / 2));
		}
	}
	if (keys[KEYBOARD_KEY_ESC]) exit(0); 	
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
	glTranslatef(_parent->_position.x * -1, _parent->_position.y * -1, _parent->_position.z * -1); // Times -1 because camera axis are inverted

	float pos[4] = { 2.0f, 5.0f, 5.0f, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
}
