#pragma once
#include <glew.h>
#include <vector>
#include <ext/matrix_float4x4.hpp>

#include "../Color/ge_color.hpp"
#include "../Transform/ge_transform.hpp"

class GE_Window;

class GE_Component
{
private:
	
	glm::mat4 mvp;

protected:
	const char* texturePath;
	const char* vertexShaderPath;
	const char* fragmentShaderPath;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;

	// shader
	GLuint programID;

	// buffers
	GLuint vertexBuffer;
	GLuint uvBuffer;

	GLuint vertexArrayID;
	GLuint matrixID;

	GLuint textureID;
	GLuint texture = 0;
	GE_Color color;

	GE_Transform transform;
	
	void LoadTexture();

	void LoadVBO();
	void LoadUVBuffer();
	void VerticesBuffer() const;
	void UVsBuffer() const;
	void InitBuffer();
	
	void LoadShader(const char* _vertexShaderPath, const char* _fragmentShaderPath);
	void CleanBuffer() const;

public:
	GE_Component() = delete;

	/// <summary>
	/// Construct an component
	/// </summary>
	/// <param name="_position">Center of object (pivot) </param>
	/// <param name="_scale">Scale</param>
	/// <param name="_texturePath"> Path of Texture File (WIP)</param>
	/// <param name="_vertexShaderPath">Path of vertex shader file</param>
	/// <param name="_fragmentShaderPath">Path of Fragment Shader File </param>
	/// <param name="_color"></param>
	GE_Component(glm::vec3 _position, glm::vec3 _scale, const char* _texturePath = "", const char* _vertexShaderPath = "", const char* _fragmentShaderPath = "", GE_Color _color = GE_Color());
	GE_Component(const GE_Component& _component);
	~GE_Component();

	std::vector<glm::vec3> GetVertices() const;
	std::vector<glm::vec2> GetUVs() const;
	std::vector<glm::vec3> GetNormals() const;
	
	virtual void Draw(GE_Window* _window);
	void BindTexture() const;
	void Clean() const;
	void SetColorShader(const GE_Color _color) const;
	void SetUseTexture(bool _res);
	void BindMvpToShader();
	void UseShader(GLint _shaderID);

	GLuint GetTexture() const;
	GLuint GetShader() const;
	GLuint GetTextureID() const;
	GE_Transform GetTransform() const;

	void SetPosition(glm::vec3 _pos);
	void SetScale(glm::vec3 _scale);
	void SetRotation(float _angle, glm::vec3 _normalRotation);

	void SetMVP(glm::mat4 _newMvp);

	// Main Game methods
	void virtual OnStart();
	void virtual Update(float _deltaTime);
};