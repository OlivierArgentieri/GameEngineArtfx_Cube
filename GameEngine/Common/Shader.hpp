#pragma once

class Shader
{
public:
	static	GLuint LoadShaders(const char* _vertex_file_path, const char* _fragment_file_path);
};