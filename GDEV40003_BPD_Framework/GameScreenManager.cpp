// ----------------------------- INCLUDE ----------------------------- //
#include "GameScreenManager.h"
// ----------------------------- INCLUDE ----------------------------- //


// Initialize the GameScreenManager by setting the renderer and the first screen to be loaded
GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS start_screen)
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	v_screenIndex = 0;

	//Load the first screen
	ChangeScreen(SCREEN_MENU);
}

// Make sure all the temp screens are deleted and the current screen is deleted
GameScreenManager::~GameScreenManager()
{
	delete tempLevel1Screen;
	delete tempLevel2Screen;
	delete tempLevel3Screen;
	delete tempMainMenuScreen;
	delete tempGameOverScreen;
	delete tempControlsScreen;
	delete tempUpgradeScreen;

	tempLevel1Screen = nullptr;
	tempLevel2Screen = nullptr;
	tempLevel3Screen = nullptr;
	tempMainMenuScreen = nullptr;
	tempGameOverScreen = nullptr;
	tempControlsScreen = nullptr;
	tempUpgradeScreen = nullptr;

	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}

// Render the current screen
void GameScreenManager::Render()
{
	if (m_current_screen != nullptr)
	{
		m_current_screen->Render();
	}
}

// Update the current screen
void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	if (m_current_screen != nullptr)
	{
		m_current_screen->Update(deltaTime, e);
	}
}

int GameScreenManager::GetCurrentScreenIndex() const
{
	return v_screenIndex;
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//Clear up the old screen.
	delete m_current_screen;
	m_current_screen = nullptr;

	// Clean up the temp screens
	delete tempLevel1Screen;
	delete tempLevel2Screen;
	delete tempLevel3Screen;
	delete tempMainMenuScreen;
	delete tempGameOverScreen;
	delete tempControlsScreen;
	delete tempUpgradeScreen;

	tempLevel1Screen = nullptr;
	tempLevel2Screen = nullptr;
	tempLevel3Screen = nullptr;
	tempMainMenuScreen = nullptr;
	tempGameOverScreen = nullptr;
	tempControlsScreen = nullptr;
	tempUpgradeScreen = nullptr;


	// Switch to the new screen
	switch (new_screen)
	{
	// Check which screen to load
	case SCREEN_MENU:

		// Create a new instance of the screen
		tempMainMenuScreen = new GameScreenMainMenu(m_renderer);

	// Set the current screen to the temp screen
		m_current_screen = reinterpret_cast<GameScreen*>(tempMainMenuScreen);

	// Set the screen index to the current screen
		v_screenIndex = SCREEN_MENU;

	// Set the temp screen to null
		tempMainMenuScreen = nullptr;

		break;

	case SCREEN_LEVEL1:
		tempLevel1Screen = new GameScreenLevel1(m_renderer);
		m_current_screen = reinterpret_cast<GameScreen*>(tempLevel1Screen);
		v_screenIndex = SCREEN_LEVEL1;

		tempLevel1Screen = nullptr;
		break;

	case SCREEN_LEVEL2:
		tempLevel2Screen = new GameScreenLevel2(m_renderer);
		m_current_screen = reinterpret_cast<GameScreen*>(tempLevel2Screen);
		v_screenIndex = SCREEN_LEVEL2;

		tempLevel2Screen = nullptr;

		break;

	case SCREEN_LEVEL3:


		tempLevel3Screen = new GameScreenLevel3(m_renderer);
		m_current_screen = reinterpret_cast<GameScreen*>(tempLevel3Screen);
		v_screenIndex = SCREEN_LEVEL3;

		tempLevel3Screen = nullptr;
		break;

	case SCREEN_GAMEOVER:
		tempGameOverScreen = new GameScreenOver(m_renderer);
		m_current_screen = reinterpret_cast<GameScreen*>(tempGameOverScreen);
		v_screenIndex = SCREEN_GAMEOVER;

		tempGameOverScreen = nullptr;
		break;

	case SCREEN_CONTROLS:
		tempControlsScreen = new GameScreenControls(m_renderer);
		m_current_screen = reinterpret_cast<GameScreen*>(tempControlsScreen);
		v_screenIndex = SCREEN_CONTROLS;

		tempControlsScreen = nullptr;

		break;

	case SCREEN_UPGRADE:
		tempUpgradeScreen = new GameScreenUpgrade(m_renderer);
		m_current_screen = reinterpret_cast<GameScreen*>(tempUpgradeScreen);
		v_screenIndex = SCREEN_UPGRADE;

		tempUpgradeScreen = nullptr;
		break;


	default: break;
	}
}
