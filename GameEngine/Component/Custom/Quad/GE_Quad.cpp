
#include "GE_Quad.hpp"

void GE_Quad::LoadVertices()
{
	#define WIDTH transform.scale.x
	#define HEIGHT transform.scale.y
	
	#define POSX transform.position.x
	#define POSY transform.position.y
	#define POSZ transform.position.z

	// front
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, HEIGHT / 2 + POSY, POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, POSZ));

	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, -HEIGHT / 2 + POSY, POSZ));
	vertices.push_back(glm::vec3(WIDTH / 2 + POSX, HEIGHT / 2 + POSY, POSZ));
	vertices.push_back(glm::vec3(-WIDTH / 2 + POSX, HEIGHT / 2 + POSY, POSZ));
	// end front
}


void GE_Quad::LoadUVs()
{
	uvs.push_back(glm::vec2(0, 0));
	uvs.push_back(glm::vec2(0, 1));
	uvs.push_back(glm::vec2(1, 1));

	uvs.push_back(glm::vec2(1, 1));
	uvs.push_back(glm::vec2(1, 0));
	uvs.push_back(glm::vec2(0, 0));
}


GE_Quad::GE_Quad(const glm::vec3& _position, const glm::vec3& _scale, const char* _texturePath, const char* _vertexShaderPath, const char* _fragmentShaderPath, const GE_Color& _color) : GE_Component(_position, _scale, _texturePath, _vertexShaderPath, _fragmentShaderPath, _color)
{
	LoadVertices();
	LoadUVs();
};


GE_Quad::GE_Quad(const GE_Component& _component) : GE_Component(_component)
{
	LoadVertices();
	LoadUVs();
}

void GE_Quad::OnStart()
{
}