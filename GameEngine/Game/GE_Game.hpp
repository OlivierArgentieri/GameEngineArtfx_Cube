#pragma once
#include <memory>

#include "../Renderer/ge_renderer.hpp"

class GE_Window;
class GE_Renderer;
class GE_Game
{
private:
	GE_Window* window;
	GE_Renderer* renderer;
	
	static bool isRunning;

	std::vector<std::shared_ptr<GE_Component>> components;
	
	GE_Game() :window(nullptr) { } 

	void OnStart() const;
	
	void ProcessInput();
	void Update(float _deltaTime);
	void Render();
	
	void Clean();
	static void OnExitWindowAction(); // callback to close window 
public:
	static GE_Game& Instance()
	{
		static GE_Game _inst;
		return _inst;
	}

	GE_Game(const GE_Game&) = delete;
	GE_Game& operator=(const GE_Game&) = delete;
	GE_Game(GE_Game&&) = delete;
	GE_Game& operator=(GE_Game&&) = delete;

	void Initialize(GE_Window& _window);
	void Loop();
	void Close() const;
	
	void AddComponent(const std::shared_ptr<GE_Component>& _component);
};