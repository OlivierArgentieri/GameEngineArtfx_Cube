#pragma once
#include "../Component/GE_Component.hpp"
#include <vector>
#include <GL/glew.h>
#include <glm.hpp>

class GE_Window;


class GE_Renderer
{
private:
	static float horizontalAngleCamera; 
	static float verticalAngleCamera;
	static float fovCamera;
	
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;

	GLuint vertexArrayID;
	GLuint programID;
	GLuint matrixID;

	static void InitGlew();
	static void Close();


public:
	GE_Renderer();
	~GE_Renderer();
	void AddVertices(std::vector<glm::vec3> _vertices);
	void AddUVs(std::vector<glm::vec2> _uvs);

	void ClearVerticesAndUV();
	
	static void ClearScreen();
	static void SwapBuffer();
	static void PollEvent();

	glm::mat4 GetViewMatrix(){return viewMatrix;}
	glm::mat4 GetProjectionMatrix(){ return projectionMatrix;}

	glm::vec3 GE_Renderer::GetCameraDirection(float _vertical, float _horizontal) const;
	glm::vec3 GE_Renderer::GetCameraRightVector(float _horizontalAngle) const;
	
	void ComputeCameraMatrix(GLFWwindow* _window);
	glm::mat4 GE_Renderer::ComputeMVP(glm::mat4 _objectModelMatrix) const;
};
