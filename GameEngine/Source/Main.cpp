#include "../Component/Custom/RotateCube/GE_RotateCube.hpp"
#include "../Game/GE_Game.hpp"
#include "../Renderer/ge_renderer.hpp"
#include "../Window/GE_Window.hpp"


int main()
{
	GE_Color  _windowColor = GE_Color(0, 0, .1f, 0);
	GE_Window _geWindow = GE_Window(1024, 760, "Roll a Cube", _windowColor);

	
	GE_Game::Instance().Initialize(_geWindow);
	
	std::shared_ptr<GE_Component> _rotateCube = std::make_unique<GE_RotateCube>(glm::vec3(0, 0, 0), glm::vec3(10, 10, 10), "", "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader", GE_Color(0.5, 1, 1));

	GE_Game::Instance().AddComponent(_rotateCube);

	GE_Game::Instance().Loop();
	
	GE_Game::Instance().Close();

	return 0;
}