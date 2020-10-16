
#include <ext/matrix_transform.hpp>
#include "GE_Transform.hpp"
GE_Transform::GE_Transform() : GE_Transform(glm::vec3(),  glm::vec3())
{
}

GE_Transform::GE_Transform(glm::vec3 _position, glm::vec3 _scale)
{
	position = _position;
	scale = _scale;
}


GE_Transform::GE_Transform(const GE_Transform& _transform) : GE_Transform(_transform.position, _transform.scale)
{
	modelMatrix = _transform.modelMatrix;
}

void GE_Transform::SetPosition(glm::vec3 _position)
{
	position = _position;
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, _position);
}

void GE_Transform::Translate(glm::vec3 _position)
{
	position += _position;
	modelMatrix = glm::translate(modelMatrix, _position);
}

void GE_Transform::SetScale(glm::vec3 _scale)
{
	scale = _scale;
}

/// <summary>
/// Using GLM Rotation matrix
/// </summary>
/// <param name="_angle">deg</param>
/// <param name="_nomalRotation">normal of rotation </param>
void GE_Transform::SetRotation(float _angle, glm::vec3 _normalRotation)
{
	modelMatrix = glm::rotate<float>(glm::mat4(1.0f), glm::radians(_angle), _normalRotation);
}