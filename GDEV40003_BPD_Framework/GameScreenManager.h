// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _GAMESCREENMANAGER_H
#define GAMESCREENMANAGER_H
#include <SDL.h>
#include "Commons.h"
#include "Audio.h"
#include "GameScreenControls.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenMainMenu.h"
#include "GameScreenOver.h"
#include "GameScreenUpgrade.h"
#include "GameScreenLevel3.h"

class GameScreen; // Forward Declaration
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- GAMESCREENMANAGER CLASS ----------------------------- //
class GameScreenManager
{
public:
	/// <summary>
	/// Initialise the renderer and set the first screen to the main menu.
	/// </summary>
	GameScreenManager(SDL_Renderer* renderer, SCREENS start_screen);

	/// <summary>
	/// Delete all instances of screens and the current screen itself.
	/// </summary>
	~GameScreenManager();

	/// <summary>
	/// Renders all of the gameobjects and textures in the scene.
	/// </summary>
	void Render();

	/// <summary>
/// Updates the current screen
/// </summary>
	void Update(float deltaTime, SDL_Event e);

	/// <summary>
	/// Change off the current screen to a specified screen.
	/// </summary>
	void ChangeScreen(SCREENS new_screen);

	/// <summary>
	/// Return the current screen index.
	/// </summary>
	int GetCurrentScreenIndex() const;

private:
	// Screen index member.
	int v_screenIndex;

	// Texture and renderer members.
	SDL_Renderer* m_renderer = nullptr;
	GameScreen* m_current_screen = nullptr;

	// Instances of the game screens.
	GameScreenLevel1* tempLevel1Screen = nullptr;
	GameScreenLevel2* tempLevel2Screen = nullptr;
	GameScreenLevel3* tempLevel3Screen = nullptr;
	GameScreenMainMenu* tempMainMenuScreen = nullptr;
	GameScreenOver* tempGameOverScreen = nullptr;
	GameScreenControls* tempControlsScreen = nullptr;
	GameScreenUpgrade* tempUpgradeScreen = nullptr;
};

#endif // _GAMESCREENMANAGER_H
// ----------------------------- GAMESCREENMANAGER CLASS ----------------------------- //
