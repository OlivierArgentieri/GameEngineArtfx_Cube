#include "GE_RotateCube.hpp"
#include <glm/gtc/matrix_transform.hpp >

#include "../../../Game/GE_Game.hpp"
#include "../../../Input/GE_InputManager.hpp"
#include "../../../Utils/Utils.hpp"
#include "../Quad/GE_Quad.hpp"

float GE_RotateCube::currentAngle = 0;
float GE_RotateCube::currentSpeed = 0;
glm::vec2 GE_RotateCube::direction = glm::vec2(0, 1);
glm::vec2 GE_RotateCube::normalRotation = glm::vec2(0, 1);

glm::vec2 GE_RotateCube::startPos = glm::vec2();
glm::vec2 GE_RotateCube::endPos = glm::vec2();

void GE_RotateCube::LoadVertices()
{
	#define DEPTH transform.scale.z
	#define WIDTH transform.scale.x
	#define HEIGHT transform.scale.y
	
	#define POSX transform.position.x
	#define POSY transform.position.y
	#define POSZ transform.position.z
	
	// front
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, HEIGHT/2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, -HEIGHT/ 2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, -HEIGHT/2 + POSY, DEPTH / 2 + POSZ));

	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	// end front


	// back
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, HEIGHT/2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));

	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, HEIGHT/2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, HEIGHT/2 + POSY, -DEPTH / 2 + POSZ));
	// end back


	// top
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	// end top

	// right
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));

	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	// end right

	// left
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
								 
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	// end left

	// bottom
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));

	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, -DEPTH / 2 + POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, DEPTH / 2 + POSZ));
	// end bottom
}

void GE_RotateCube::LoadUVs()
{
	uvs.push_back(glm::vec2(0, 0));
	uvs.push_back(glm::vec2(0, 1));
	uvs.push_back(glm::vec2(1, 1));

	uvs.push_back(glm::vec2(1, 1));
	uvs.push_back(glm::vec2(1, 0));
	uvs.push_back(glm::vec2(0, 0));
}

GE_RotateCube::GE_RotateCube(glm::vec3 _position, glm::vec3 _scale, const char* _texturePath, const char* _vertexShaderPath, const char* _fragmentShaderPath, GE_Color _color) : GE_Component(_position, _scale, _texturePath, _vertexShaderPath, _fragmentShaderPath, _color)
{
	LoadVertices();
	LoadUVs();
}

GE_RotateCube::GE_RotateCube(const GE_RotateCube& _component) : GE_Component(_component)
{
	LoadVertices();
	LoadUVs();
}

void GE_RotateCube::OnStart()
{
	GE_InputManager::RegisterLeftMouseActionButtonPressCentered(OnMouseLeftPressed);
	GE_InputManager::RegisterLeftMouseActionButtonReleaseCentered(OnMouseLeftRelease);
}

void GE_RotateCube::Update(float _deltaTime)
{
	glm::vec2 norm = glm::normalize(direction);
	SetRotation(currentAngle, glm::vec3(norm.y, -norm.x,0 ));

	currentAngle = fmod(currentAngle, 360); // because % doesn't work

	currentAngle += currentSpeed * _deltaTime;

	currentSpeed -= friction;

	currentSpeed = Utils::Clamp(0, 1000, currentSpeed);
}

void GE_RotateCube::OnMouseLeftPressed(double _x, double _y)
{
	startPos = glm::vec2();
	endPos = glm::vec2();
	startPos.x = _x;
	startPos.y = _y;
}


void GE_RotateCube::OnMouseLeftRelease(double _x, double _y)
{
	endPos.x = _x;
	endPos.y = _y;

	glm::vec2 _tempDirection = glm::vec2(-endPos.x, endPos.y) - glm::vec2(-startPos.x, startPos.y);
	if (glm::length(_tempDirection) == 0) return;
	
	direction = _tempDirection;
	currentSpeed = glm::length(direction);
}