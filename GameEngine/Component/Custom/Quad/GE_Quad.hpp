
#include "../../GE_Component.hpp"

class GE_Quad : public GE_Component
{
public:

	void LoadVertices();
	void LoadUVs();

public:
	GE_Quad(const glm::vec3& _position, const glm::vec3& _scale, const char* _texturePath, const char* _vertexShaderPath, const char* _fragmentShaderPath, const GE_Color& _color);
	GE_Quad(const GE_Component& _sceneObject);

	void OnStart() override;
};
