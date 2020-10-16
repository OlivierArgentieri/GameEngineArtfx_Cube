#pragma once
#include <glm.hpp>

class GE_Renderer;
class GE_Transform
{
private:
	glm::mat4 modelMatrix;

public:
	glm::vec3 position;
	glm::vec3 scale;

	GE_Transform();
	GE_Transform(glm::vec3 _position, glm::vec3 _scale);
	GE_Transform(const GE_Transform& _transform);

	void SetPosition(glm::vec3 _position);
	void Translate(glm::vec3 _position);
	void SetScale(glm::vec3 _scale);
	void SetRotation(float _angle, glm::vec3 _normalRotation);

	glm::mat4 GetModelMatrix()const { return modelMatrix; }

};
