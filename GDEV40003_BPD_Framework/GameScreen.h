// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _GAMESCREEN_H
#define GAMESCREEN_H
#include <SDL.h>
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- GAMESCREEN CLASS ----------------------------- //
class GameScreen
{
public:

	/// <summary>
	/// Initialise a game screen using a renderer.
	/// </summary>
	explicit GameScreen(SDL_Renderer* renderer);

	/// <summary>
	/// Set the renderer to nullptr.
	/// </summary>
	virtual ~GameScreen();

	/// <summary>
	/// Virtual render function to parse onto the renderer.
	/// </summary>
	virtual void Render();

	/// <summary>
	/// Virtual update function to parse onto the gamescreen thread.
	/// </summary>
	virtual void Update(float deltaTime, SDL_Event e);

private:

	// Gamescreen renderer
	SDL_Renderer* m_renderer = nullptr;
};
#endif // _GAMESCREEN_H
// ----------------------------- GAMESCREEN CLASS ----------------------------- //