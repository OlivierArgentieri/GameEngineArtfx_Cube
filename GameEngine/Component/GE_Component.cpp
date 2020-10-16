#include "GE_Component.hpp"

#include <iostream>
#include <ostream>
#include <ext/matrix_transform.hpp>

#include "../Common/Shader.hpp"
#include "../Window/GE_Window.hpp"


void GE_Component::LoadTexture()
{
	printf("NEED TO IMPLEMENT LIBRARY");
}

void GE_Component::LoadVBO()
{
	if (vertices.empty()) return;
	// Load it into a VBO
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
}

void GE_Component::LoadUVBuffer()
{
	if (uvs.empty()) return;
	
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}

void GE_Component::VerticesBuffer() const
{
	if (vertices.empty()) return;
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0, // attribute
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
	);
}

void GE_Component::UVsBuffer() const
{
	if (uvs.empty()) return;
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(
		1, // attribute
		2, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
	);
}

void GE_Component::InitBuffer()
{
	LoadVBO();
	LoadUVBuffer();

	VerticesBuffer();
	UVsBuffer();
}

void GE_Component::LoadShader(const char* _vertexShaderPath, const char* _fragmentShaderPath)
{
	if (_vertexShaderPath[0] == '\0' || _fragmentShaderPath == '\0') return;
	programID = Shader::LoadShaders(_vertexShaderPath, _fragmentShaderPath);
}

void GE_Component::CleanBuffer() const
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
}


GE_Component::GE_Component(glm::vec3 _position, glm::vec3 _scale, const char* _texturePath,
	const char* _vertexShaderPath, const char* _fragmentShaderPath, GE_Color _color)
{
	transform = GE_Transform(_position, _scale);
	texturePath = _texturePath;
	
	vertexShaderPath = _vertexShaderPath;
	fragmentShaderPath = _fragmentShaderPath;
	color = _color;
	
	LoadTexture();
	LoadShader(_vertexShaderPath, _fragmentShaderPath);
	color = _color;
	transform.SetPosition(_position);
	GE_Component::SetScale(_scale);
}

GE_Component::GE_Component(const GE_Component& _component)
{
	transform = GE_Transform(_component.transform);
	texturePath = _component.texturePath;
	LoadTexture();

	color = _component.color;

	transform.SetPosition(_component.transform.position);
	SetScale(_component.transform.scale);

}

GE_Component::~GE_Component()
{
	glDeleteTextures(1, &texture);
}

std::vector<glm::vec3> GE_Component::GetVertices() const
{
	return vertices;
}

std::vector<glm::vec2> GE_Component::GetUVs() const
{
	return uvs;
}

std::vector<glm::vec3> GE_Component::GetNormals() const
{
	return std::vector<glm::vec3>();

}

void GE_Component::Draw(GE_Window* _window)
{
	// isValid ? 
	if (!_window) return;
	
	UseShader(programID);
	BindTexture();
	SetUseTexture(texture != 0);
	SetColorShader(color);

	BindMvpToShader();
	InitBuffer();

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	CleanBuffer();
}

void GE_Component::BindTexture() const
{
	if (texturePath[0] == '\0') return;

	// enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind our texture in texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	// sampler to use texture
	glUniform1i(textureID, 0);
}

void GE_Component::Clean() const
{
	// remove shader
	glDeleteProgram(programID);

	glDeleteVertexArrays(1, &vertexArrayID);
}

void GE_Component::SetColorShader(const GE_Color _color) const
{
	GLint _newColor = glGetUniformLocation(programID, "color"); // bind parameter
	float _editedColor[3] = { _color.r, _color.g, _color.b };
	glUniform3fv(_newColor, 1, _editedColor);
}

void GE_Component::SetUseTexture(bool _res)
{
	GLboolean _color = glGetUniformLocation(programID, "isTextureLoaded");
	glUniform1i(_color, _res);
}

void GE_Component::BindMvpToShader()
{
	// send transformation to currently bound shader (mvp uniform)
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
}

void GE_Component::UseShader(GLint _shaderID)
{
	// use shader
	glUseProgram(_shaderID);
	matrixID = glGetUniformLocation(_shaderID, "MVP");
}

GLuint GE_Component::GetTexture() const
{
	return texture;
}

GLuint GE_Component::GetShader() const
{
	return programID;
}

GLuint GE_Component::GetTextureID() const
{
	return textureID;
}

GE_Transform GE_Component::GetTransform() const
{
	return transform;
}

void GE_Component::SetPosition(glm::vec3 _pos)
{
	transform.SetPosition(_pos);
}

void GE_Component::SetScale(glm::vec3 _scale)
{
	transform.SetScale(_scale);
}

void GE_Component::SetRotation(float _angle, glm::vec3 _normalRotation)
{
	transform.SetRotation(_angle, _normalRotation);
}

void GE_Component::SetMVP(glm::mat4 _newMvp)
{
	mvp = _newMvp;
}

void GE_Component::OnStart()
{
}


void GE_Component::Update(float _deltaTime)
{
}

