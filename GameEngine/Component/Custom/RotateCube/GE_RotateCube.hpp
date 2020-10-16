#pragma once
#include "../../GE_Component.hpp"


struct GE_Color;

class GE_RotateCube : public GE_Component
{
private:
	const float friction = 2;

	void LoadVertices();
	void LoadUVs();

	static float currentSpeed;
	static float currentAngle;


	static glm::vec2 direction;
	static glm::vec2 normalRotation;

	static glm::vec2 startPos;
	static glm::vec2 endPos;

public:
	GE_RotateCube() = delete;
	GE_RotateCube(glm::vec3 _position, glm::vec3 _scale, const char* _texturePath = "", const char* _vertexShaderPath = "", const char* _fragmentShaderPath = "", GE_Color _color = GE_Color());
	GE_RotateCube(const GE_RotateCube& _component);

	void OnStart() override;

	void Update(float _deltaTime) override;
	
	static void OnMouseLeftPressed(double _x, double _y);
	static void OnMouseLeftRelease(double _x, double _y);
};


