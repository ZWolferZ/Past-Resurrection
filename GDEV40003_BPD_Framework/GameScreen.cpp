// ----------------------------- INCLUDE ----------------------------- //
#include "GameScreen.h"
// ----------------------------- INCLUDE ----------------------------- //

// Parse the renderer to the screen
GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

// Set the renderer to null
GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

// Render the screen
void GameScreen::Render()
{
}

// Update the screen
void GameScreen::Update(float deltaTime, SDL_Event e)
{
}
