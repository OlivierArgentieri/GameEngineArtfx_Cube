#include <iostream>
#include "GE_Game.hpp"


#include "../Input/GE_InputManager.hpp"
#include "../Time/GE_Time.hpp"
#include "../Window/GE_Window.hpp"

bool GE_Game::isRunning = true;

void GE_Game::ProcessInput()
{
	GE_InputManager::InputLoop();
}

void GE_Game::Update(float _deltaTime)
{
	for (std::shared_ptr<GE_Component> _sceneObject : components)
		_sceneObject->Update(_deltaTime);
}

void GE_Game::Render()
{
	if (!window) return;
	GE_Time::BeginFrame();
	
	GE_Renderer::ClearScreen();
	
	renderer->ComputeCameraMatrix(window->GetWindow());

	// draw component
	for (std::shared_ptr<GE_Component> _sceneObject : components)
	{
		// set mvp for each object
		_sceneObject->SetMVP(renderer->ComputeMVP(_sceneObject->GetTransform().GetModelMatrix()));
		_sceneObject->Draw(window);
	}
	window->SwapBuffer();
	
	GE_Time::EndFrame();
}

void GE_Game::Clean()
{
	for (auto  _sceneObject : components)
	{
		_sceneObject->Clean();
	}
}

void GE_Game::Initialize(GE_Window& _window)
{
	window = &_window; // ref to pointer, to avoid default constructor implementation in GE_Window
	_window.InitWindow();

	// init input manager
	GE_InputManager::Initialize(_window);
	
	renderer = new GE_Renderer();
	
	isRunning = true;
}

void GE_Game::Loop()
{
	OnStart();
	while (isRunning)
	{
		ProcessInput();
		Update(GE_Time::GetDeltaTime());
		Render();
	}
}

void GE_Game::Close() const
{
	if (!window) return;
	
	window->Destroy();
	delete renderer;
}

void GE_Game::AddComponent(const std::shared_ptr<GE_Component>& _component)
{
	components.push_back(_component);
}

void GE_Game::OnStart() const
{
	// register close event
	GE_InputManager::RegisterOnExitGame(OnExitWindowAction);
	for (auto _component : components)
	{
		_component->OnStart();
	}
}

void GE_Game::OnExitWindowAction()
{
	isRunning = false;
}