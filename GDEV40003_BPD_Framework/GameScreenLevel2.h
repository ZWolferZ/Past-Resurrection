// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _GAMESCREENLEVEL2_H
#define GAMESCREENLEVEL2_H
#include "GameScreen.h"
#include "constants.h"
#include <iostream>
#include "Texture2D.h"
#include "GlobalGameStates.h"
#include "Character.h"

#include "GameText.h"

#include "EnemyGround.h"
#include "EnemyFlyers.h"
#include "Bullet.h"
#include "Audio.h"
#include "Crosshair.h"
#include "Collisions.h"

#include <functional>

#include <ctime>
#include <thread>


class Texture2D; // Forward Declaration

class Character; // Forward Declaration
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- GAMESCREENLEVEL2 CLASS ----------------------------- //
class GameScreenLevel2 : GameScreen // Inherits from GameScreen.
{
public:
	/// <summary>
	/// Initialise the second level game screen using a renderer.
	/// </summary>
	explicit GameScreenLevel2(SDL_Renderer* renderer);

	/// <summary>
	/// Deletes all of the gameobjects and textures in the scene.
	/// </summary>
	~GameScreenLevel2() override;

	/// <summary>
	/// Renders all of the gameobjects and textures in the scene.
	/// </summary>
	void Render() override;

	/// <summary>
/// Updates all of the gameobjects and textures in the scene.
/// </summary>
	void Update(float deltaTime, SDL_Event e) override;

	/// <summary>
	/// Move the character from the right tower to the left tower.
	/// </summary>
	void MoveTowerLeft();

	/// <summary>
	/// Move the character from the left tower to the right tower.
	/// </summary>
	void MoveTowerRight();

	/// <summary>
	/// Reload the bullet counter.
	/// </summary>
	void Reload();

private:
	// Texture and renderer members.
	Texture2D* m_background_texture = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	// GameState members.
	int m_timer = 5000;
	const float v_range = 5.0f;

	// Gametext members.
	GameText* m_scoreText = nullptr;
	GameText* m_timerText = nullptr;
	GameText* m_playerHealthText = nullptr;
	GameText* m_baseHealthText = nullptr;

	// Gameobject members.
	Bullet* m_bullet[7];
	GameObject* m_skybox = nullptr;
	GameObject* m_shotgun_get = nullptr;
	GameObject* m_playerHealthIcon = nullptr;
	GameObject* m_baseHealthIcon = nullptr;
	GameObject* m_normalGunIcon = nullptr;
	GameObject* m_shotgunIcon = nullptr;
	GameObject* m_scoreIcon = nullptr;
	GameObject* m_timeIcon = nullptr;
	GameObject* m_bulletCounter[7];

	// Audio members.
	Audio* m_bulletaudio = nullptr;
	Audio* m_reloadaudio = nullptr;
	Audio* m_swapaudio = nullptr;
	Audio* m_gunswapaudio = nullptr;
	Audio* m_shotgunaudio = nullptr;
	Audio* m_enemyhurt = nullptr;
	Audio* m_playerHurt = nullptr;

	/// <summary>
/// Initialise all gameobjects, sounds and textures in the scene.
/// </summary>
	bool SetUpLevel();
};


#endif // _GAMESCREENLEVEL2_H
// ----------------------------- GAMESCREENLEVEL2 CLASS ----------------------------- //
