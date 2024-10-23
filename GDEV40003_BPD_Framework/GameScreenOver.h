#pragma once
#ifndef _GAMESCREENOVER_H
#define GAMESCREENOVER_H
#include "GlobalGameStates.h"
#include "constants.h"
#include <iostream>
#include "GameScreen.h"
// ----------------------------- INCLUDES ----------------------------- //
#include "Commons.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "GlobalGameStates.h"
#include "GameText.h"
#include "Audio.h"

class Texture2D; // Forward Declaration
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- GAMESCREENOVER CLASS ----------------------------- //
class GameScreenOver : GameScreen // Inherits from GameScreen.
{
public:
	/// <summary>
	/// Initialise the gameover game screen using a renderer.
	/// </summary>
	explicit GameScreenOver(SDL_Renderer* renderer);

	/// <summary>
	/// Deletes all of the gameobjects and textures in the scene.
	/// </summary>
	~GameScreenOver() override;

	/// <summary>
/// Renders all of the gameobjects and textures in the scene.
/// </summary>
	void Render() override;

	/// <summary>
/// Updates all of the gameobjects and textures in the scene.
/// </summary>
	void Update(float deltaTime, SDL_Event e) override;

private:
	// Game state member.
	bool v_continueSelected = true;

	// Texture and renderer members.
	Texture2D* m_background_texture = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	// Gameobjects members.
	GameObject* m_quitSelect_texture = nullptr;
	GameObject* m_continueSelect_texture = nullptr;
	GameObject* m_quitNotSelect_texture = nullptr;
	GameObject* m_continuetNotSelect_texture = nullptr;

	// Audio member.
	Audio* m_menuselectionaudio = nullptr;


	/// <summary>
/// Initialise all gameobjects, sounds and textures in the scene.
/// </summary>
	bool SetUpLevel();
};

#endif // _GAMESCREENOVER_H
// ----------------------------- GAMESCREENOVER CLASS ----------------------------- //
