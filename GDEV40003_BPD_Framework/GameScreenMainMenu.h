// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _GAMESCREENMAINMENU_H
#define GAMESCREENMAINMENU_H
#include "GameScreen.h"
#include "Commons.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "GameText.h"
#include "constants.h"
#include "GlobalGameStates.h"
#include <iostream>
#include "Audio.h"


class Texture2D; // Forward declaration.
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- GAMESCREENMAINMENU CLASS ----------------------------- //
class GameScreenMainMenu : GameScreen // Inherits from GameScreen.
{
public:
	/// <summary>
	/// Initialise the main menu game screen using a renderer.
	/// </summary>
	explicit GameScreenMainMenu(SDL_Renderer* renderer);

	/// <summary>
	/// Deletes all of the gameobjects and textures in the scene.
	/// </summary>
	~GameScreenMainMenu() override;

	/// <summary>
/// Renders all of the gameobjects and textures in the scene.
/// </summary>
	void Render() override;

	/// <summary>
/// Updates all of the gameobjects and textures in the scene.
/// </summary>
	void Update(float deltaTime, SDL_Event e) override;

	/// <summary>
	/// Sets the start state of the game.
	/// </summary>
	bool SetStartState(bool state) { return v_startState = state; }

	/// <summary>
	/// Gets the start state of the game.
	/// </summary>
	bool GetStartState() const { return v_startState; }

private:
	// Texture and renderer members.
	Texture2D* m_background_texture = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	// Gameobject members.
	GameObject* m_quitSelect_texture = nullptr;
	GameObject* m_startSelect_texture = nullptr;
	GameObject* m_quitNotSelect_texture = nullptr;
	GameObject* m_startNotSelect_texture = nullptr;
	GameObject* m_controlsSelect_texture = nullptr;
	GameObject* m_controlsNotSelect_texture = nullptr;

	// Audio member.
	Audio* m_audio = nullptr;

	GameText* m_gameText = nullptr;
	GameText* m_gameText2 = nullptr;
	GameText* m_gameText3 = nullptr;

	// Gamestate members.
	bool v_controlsSelected = false;
	bool v_startState = true;

	/// <summary>
/// Initialise all gameobjects, sounds and textures in the scene.
/// </summary>
	bool SetUpLevel();
};


#endif // _GAMESCREENLEVEL1_H
// ----------------------------- GAMESCREENMAINMENU CLASS ----------------------------- //
