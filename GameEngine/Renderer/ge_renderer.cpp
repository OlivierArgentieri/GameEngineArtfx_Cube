#include <glew.h>
#include "ge_renderer.hpp"


#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "../Window/ge_window.hpp"
#include "../Component/GE_Component.hpp"


#define PI_APPROX 3.14

// camera on forward
float GE_Renderer::horizontalAngleCamera = 3.14f;
float GE_Renderer::verticalAngleCamera = 0;
float GE_Renderer::fovCamera = 45;

void GE_Renderer::InitGlew()
{
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
	}
}

void GE_Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GE_Renderer::SwapBuffer()
{
}


// todo
/// <summary>
/// Update user input
/// </summary>
void GE_Renderer::PollEvent()
{
	glfwPollEvents();
}

void GE_Renderer::ComputeCameraMatrix(GLFWwindow* _window)
{
	if (!_window) return;
	// fix the camera on forward


	glm::vec3 _rightVector = GetCameraRightVector(horizontalAngleCamera);
	glm::vec3 _directionVector = GetCameraDirection(verticalAngleCamera, horizontalAngleCamera);

	// Up vector
	glm::vec3 up = glm::cross(_rightVector, _directionVector);

	glm::vec3 _zPosition = _directionVector * -40.0f;

	projectionMatrix = glm::perspective(glm::radians(fovCamera), 4.0f / 3.0f, 0.1f, 1000.0f);
	
	// Camera matrix
	viewMatrix = glm::lookAt(
		_zPosition,           // Camera is here
		_zPosition + _directionVector, // and looks here : at the same position, plus "direction"
		up                  
	);
}

glm::mat4 GE_Renderer::ComputeMVP(glm::mat4 _objectModelMatrix) const
{
	return projectionMatrix * viewMatrix * _objectModelMatrix;
}

glm::vec3 GE_Renderer::GetCameraDirection(float _vertical, float _horizontal) const
{
	// see : https://stackoverflow.com/questions/23574320/opengl-camera-direction-vector

	glm::vec3 _direction(
		cos(_vertical) * sin(_horizontal),
		sin(_vertical),
		cos(_vertical) * cos(_horizontal)
	);

	return _direction;
}

glm::vec3 GE_Renderer::GetCameraRightVector(float _horizontalAngle) const
{
	// see : https://stackoverflow.com/questions/23574320/opengl-camera-direction-vector
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(_horizontalAngle - PI_APPROX / 2.0f),
		0,
		cos(_horizontalAngle - PI_APPROX / 2.0f)
	);

	return right;
}

void GE_Renderer::Close()
{
	glfwTerminate();
}

GE_Renderer::GE_Renderer()
{
	InitGlew();
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
}

GE_Renderer::~GE_Renderer()
{
	Close();
}

void GE_Renderer::AddVertices(std::vector<glm::vec3> _vertices)
{
	for (glm::vec3 _vertex : _vertices)
	{
		vertices.push_back(_vertex);
	}
}

void GE_Renderer::AddUVs(std::vector<glm::vec2> _uvs)
{
	for (glm::vec2 _uv : _uvs)
	{
		uvs.push_back(_uv);
	}
}


void GE_Renderer::ClearVerticesAndUV()
{
	vertices.clear();
	uvs.clear();
}