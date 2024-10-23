// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _GAMESCREENCONTROLS_H
#define GAMESCREENCONTROLS_H
#include "GlobalGameStates.h"
#include "constants.h"
#include <iostream>
#include "GameScreen.h"
#include "Commons.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "GameText.h"
#include "Audio.h"

class Texture2D; // Forward Declaration
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- GAMESCREENCONTROLS CLASS ----------------------------- //
class GameScreenControls : GameScreen // Inherit from GameScreen

{
public:
	/// <summary>
	/// Initialise the controls menu game screen using a renderer.
	/// </summary>
	explicit GameScreenControls(SDL_Renderer* renderer);

	/// <summary>
	/// Deletes all of the gameobjects and textures in the scene.
	/// </summary>
	~GameScreenControls() override;

	/// <summary>
	/// Renders all of the gameobjects and textures in the scene.
	/// </summary>
	void Render() override;

	/// <summary>
	/// Updates all of the gameobjects and textures in the scene.
	/// </summary>
	void Update(float deltaTime, SDL_Event e) override;

private:
	// Texture and renderer members	
	Texture2D* m_background_texture = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	// Gamestate member.
	bool v_inControls = false;

	/// <summary>
	/// Initialise all gameobjects, sounds and textures in the scene.
	/// </summary>
	bool SetUpLevel();
};

#endif // _GAMESCREENCONTROLS_H
// ----------------------------- GAMESCREENCONTROLS CLASS ----------------------------- //
