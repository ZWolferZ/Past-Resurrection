// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _GAMESCREENUPGRADE_H
#define GAMESCREENUPGRADE_H
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

// ----------------------------- GAMESCREENUPGRADE CLASS ----------------------------- //
class GameScreenUpgrade : GameScreen // Inherits from GameScreen.
{

	public:

	/// <summary>
	/// Initialise the upgrade menu game screen using a renderer.
	/// </summary>
	explicit GameScreenUpgrade(SDL_Renderer* renderer);

	/// <summary>
	/// Deletes all of the gameobjects and textures in the scene.
	/// </summary>
	~GameScreenUpgrade() override;

		/// <summary>
	/// Renders all of the gameobjects and textures in the scene.
	/// </summary>
	void Render() override;

		/// <summary>
	/// Updates all of the gameobjects and textures in the scene.
	/// </summary>
	void Update(float deltaTime, SDL_Event e) override;


private:

	// Texture and renderer members.
	Texture2D* m_background_texture = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	// A lot of gameobjects members.
	GameObject* m_BackSelected_texture = nullptr;
	GameObject* m_ContinueSelected_texture = nullptr;
	GameObject* m_BackNotSelected_texture = nullptr;
	GameObject* m_ContinueNotSelected_texture = nullptr;

	GameObject* m_HealthUpgrade1Selected_texture = nullptr;
	GameObject* m_HealthUpgrade1NotSelected_texture = nullptr;
	GameObject* m_HealthUpgrade1Bought_texture = nullptr;

	GameObject* m_HealthUpgrade2Selected_texture = nullptr;
	GameObject* m_HealthUpgrade2NotSelected_texture = nullptr;
	GameObject* m_HealthUpgrade2Bought_texture = nullptr;

	GameObject* m_HealthUpgrade3Selected_texture = nullptr;
	GameObject* m_HealthUpgrade3NotSelected_texture = nullptr;
	GameObject* m_HealthUpgrade3Bought_texture = nullptr;

	GameObject* m_BaseHealthUpgrade1Selected_texture = nullptr;
	GameObject* m_BaseHealthUpgrade1NotSelected_texture = nullptr;
	GameObject* m_BaseHealthUpgrade1Bought_texture = nullptr;

	GameObject* m_BaseHealthUpgrade2Selected_texture = nullptr;
	GameObject* m_BaseHealthUpgrade2NotSelected_texture = nullptr;
	GameObject* m_BaseHealthUpgrade2Bought_texture = nullptr;

	GameObject* m_BaseHealthUpgrade3Selected_texture = nullptr;
	GameObject* m_BaseHealthUpgrade3NotSelected_texture = nullptr;
	GameObject* m_BaseHealthUpgrade3Bought_texture = nullptr;

	GameObject* m_scoreIcon = nullptr;

	// Gametext member.
	GameText* m_scoreText = nullptr;

	// Gamestates member (for rendering).
	bool continueSelected = true;
	bool backSelected = false;
	bool healthUpgrade1Selected = false;
	bool healthUpgrade2Selected = false;
	bool healthUpgrade3Selected = false;

	bool healthUpgrade1Bought = false;
	bool healthUpgrade2Bought = false;
	bool healthUpgrade3Bought = false;

	bool baseHealthUpgrade1Selected = false;
	bool baseHealthUpgrade2Selected = false;
	bool baseHealthUpgrade3Selected = false;

	bool baseHealthUpgrade1Bought = false;
	bool baseHealthUpgrade2Bought = false;
	bool baseHealthUpgrade3Bought = false;


	// Audio members.
	Audio* m_menuselectionaudio = nullptr;
	Audio* m_buyaudio = nullptr;
	Audio* m_erroraudio = nullptr;

		/// <summary>
	/// Initialise all gameobjects, sounds and textures in the scene.
	/// </summary>
	bool SetUpLevel();
};

#endif // _GAMESCREENUPGRADE_H
// ----------------------------- GAMESCREENUPGRADE CLASS ----------------------------- //