// ----------------------------- INCLUDE ----------------------------- //
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Texture2D.h"
#include "constants.h"
#include "GameScreenManager.h"
#include "GlobalGameStates.h"
#include <iostream>


// ----------------------------- INCLUDE ----------------------------- //

// Initialising the starting variables
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager = nullptr;
Audio* m_audio1 = nullptr;
Audio* m_audiodeath = nullptr;
Uint32 g_old_time;

// Initialising the control variables
bool v_start = true;
bool v_controlsSelectedMain = false;
bool v_healthToggle1 = false;
bool v_healthToggle2 = false;
bool v_healthToggle3 = false;
bool v_baseHealthToggle1 = false;
bool v_baseHealthToggle2 = false;
bool v_baseHealthToggle3 = false;


// Function Prototypes
void Render();
bool InitSDL();
void CloseSDL();
bool Update();

// Main Function, where the program starts
int main(int argc, char* argv[])
{
	// Initialising SDL
	if (InitSDL())
	{
		// Create the Game Screen Manager
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);

		// Create the Audio systems
		m_audio1 = new Audio();
		m_audio1->LoadFromFile("Sound/Selected.wav");
		m_audiodeath = new Audio();
		m_audiodeath->LoadFromFile("Sound/Death.wav");

		// Get the time at the start of the game
		g_old_time = SDL_GetTicks();


		bool quit = false;

		// Initialising the game loop
		while (!quit)
		{
			// Sets the framerate to 60
			const Uint32 frameStart = SDL_GetTicks();

			Render();
			quit = Update();

			const Uint32 frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}
		}
	}

	// Close the game
	CloseSDL();

	return 0;
}

// Initialising SDL and all its subsystems / Initialising the window and renderer
bool InitSDL()
{
	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	// Setup passed, Create window
	g_window = SDL_CreateWindow("Past Resurrection", SDL_WINDOWPOS_UNDEFINED,
	                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);


	// Did the window get created?
	if (g_window == nullptr)
	{
		// Window Failed
		std::cout << "Window was not created. Error: " << SDL_GetError();
		return false;
	}
	// Create the renderer
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

	if (g_renderer == nullptr)
	{
		std::cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}


	// Init PNG Loading
	constexpr int imageFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imageFlags) & imageFlags))
	{
		std::cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
	}

	// Init SDL Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_Mixer could not initialise. Error: " << Mix_GetError();
	}

	// Init SDL Joystick
	SDL_JoystickOpen(1);

	return true;
}

// Free up the memory and close the game
void CloseSDL()
{
	delete game_screen_manager;
	game_screen_manager = nullptr;


	// Release the window
	g_window = nullptr;

	// Quit SDL subsystems
	SDL_Quit();

	// Clear the texture

	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
}

// Update the game every tick
bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	SDL_Event e;

	// Get Events
	SDL_PollEvent(&e);

	// Check if the player has beaten the highscore
	if (g_score > g_highScore)
	{
		g_highScore = g_score;
	}

	// Check to see if the player has bought the health upgrades
	if (g_playerHealthUpgrade1 == true && !v_healthToggle1)
	{
		g_maxplayerHealth += 25;
		v_healthToggle1 = true;
	}

	if (g_playerHealthUpgrade2 == true && !v_healthToggle2)
	{
		g_maxplayerHealth += 25;
		v_healthToggle2 = true;
	}

	if (g_playerHealthUpgrade3 == true && !v_healthToggle3)
	{
		g_maxplayerHealth += 50;
		v_healthToggle3 = true;
	}

	// Check to see if the player has bought the base health upgrades
	if (g_baseHealthUpgrade1 == true && !v_baseHealthToggle1)
	{
		g_maxbaseHealth += 25;
		v_baseHealthToggle1 = true;
	}
	if (g_baseHealthUpgrade2 == true)
	{
		g_maxbaseHealth += 25;
		v_baseHealthToggle2 = true;
	}
	if (g_baseHealthUpgrade3 == true && !v_baseHealthToggle3)
	{
		g_maxbaseHealth += 50;
		v_baseHealthToggle3 = true;
	}

	// If the player has completed the level, change the screen to the upgrade screen
	if (g_levelComplete == true && game_screen_manager->GetCurrentScreenIndex() != SCREEN_UPGRADE)
	{
		m_audio1->Play(1, m_audio1->m_chunk, 0);
		game_screen_manager->ChangeScreen(SCREEN_UPGRADE);
		g_levelComplete = false;
	}

	// If the player has died, change the screen to the game over screen
	if (g_gameOver == true && game_screen_manager->GetCurrentScreenIndex() != SCREEN_GAMEOVER || g_gameOver == true &&
		game_screen_manager->GetCurrentScreenIndex() != SCREEN_MENU)
	{
		m_audiodeath->Play(1, m_audiodeath->m_chunk, 0);
		game_screen_manager->ChangeScreen(SCREEN_GAMEOVER);
		g_gameOver = false;
	}

	// If the player has pressed the continue button, change the screen to the menu screen
	if (g_continue == true && game_screen_manager->GetCurrentScreenIndex() == SCREEN_GAMEOVER || g_continue == true &&
		game_screen_manager->GetCurrentScreenIndex() == SCREEN_CONTROLS)
	{
		m_audio1->Play(1, m_audio1->m_chunk, 0);
		game_screen_manager->ChangeScreen(SCREEN_MENU);
		v_start = true;
		g_mainMenu = true;
		g_continue = false;
	}

	// If the player has pressed the back button, change the screen to the menu screen
	if (g_continue && (g_levelTwo == true || g_levelThree == true) && game_screen_manager->GetCurrentScreenIndex() ==
		SCREEN_UPGRADE)
	{
		m_audio1->Play(1, m_audio1->m_chunk, 0);
		game_screen_manager->ChangeScreen(SCREEN_MENU);
		v_start = true;
		g_mainMenu = true;
		g_continue = false;
	}

	// If the player has pressed the continue button, change the screen to the level 2 screen
	if (!g_continue && g_playerconfirmation == true && g_levelTwo == true && game_screen_manager->
		GetCurrentScreenIndex() == SCREEN_UPGRADE)
	{
		m_audio1->Play(1, m_audio1->m_chunk, 0);
		std::cout << "Level 2" << std::endl;
		game_screen_manager->ChangeScreen(SCREEN_LEVEL2);
		g_playerconfirmation = false;
	}

	// If the player has pressed the continue button, change the screen to the level 3 screen
	if (!g_continue && g_playerconfirmation == true && g_levelThree == true && game_screen_manager->
		GetCurrentScreenIndex() == SCREEN_UPGRADE)
	{
		m_audio1->Play(1, m_audio1->m_chunk, 0);
		std::cout << "Level 3" << std::endl;
		game_screen_manager->ChangeScreen(SCREEN_LEVEL3);
		g_playerconfirmation = false;
	}

	// If the player has pressed the quit button, quit the game
	if (g_quit)
	{
		return true;
	}

	// Handle the events
	switch (e.type)
	{
	case SDL_KEYDOWN:

		switch (e.key.keysym.sym)
		{
		// Return to main menu or quit the game if at the main menu
		case SDLK_ESCAPE:
			if (game_screen_manager->GetCurrentScreenIndex() != SCREEN_MENU && game_screen_manager->
				GetCurrentScreenIndex() != SCREEN_UPGRADE)
			{
				// Play sound effect
				m_audio1->Play(1, m_audio1->m_chunk, 0);

				// Slight memory leak here as the previous screen is not deleted for some reason
				game_screen_manager->ChangeScreen(SCREEN_MENU);
				g_mainMenu = true;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_UPGRADE && g_levelOne)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				game_screen_manager->ChangeScreen(SCREEN_MENU);
				g_mainMenu = true;
				g_levelOne = false;
				g_levelTwo = true;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_UPGRADE && g_levelTwo)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				game_screen_manager->ChangeScreen(SCREEN_MENU);
				g_mainMenu = true;
				g_levelTwo = false;
				g_levelThree = true;
			}
			else
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				std::cout << "Quiting..." << std::endl;
				g_quit = true;
			}

			break;

		case SDLK_RETURN: // Load up the level/controls menu the player is currently on
			if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_start == true && v_controlsSelectedMain
				== false && g_levelOne == true)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
				g_mainMenu = false;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_start == true &&
				v_controlsSelectedMain == false && g_levelTwo == true)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				std::cout << "Level 2" << std::endl;
				game_screen_manager->ChangeScreen(SCREEN_LEVEL2);
				g_mainMenu = false;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_start == true &&
				v_controlsSelectedMain == false && g_levelThree == true)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				std::cout << "Level 3" << std::endl;
				game_screen_manager->ChangeScreen(SCREEN_LEVEL3);
				g_mainMenu = false;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_start == false &&
				v_controlsSelectedMain == false)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				std::cout << "Quiting..." << std::endl;
				g_quit = true;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_controlsSelectedMain == true)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				game_screen_manager->ChangeScreen(SCREEN_CONTROLS);
				v_controlsSelectedMain = false;
				g_mainMenu = false;
				g_controls = true;
			}
			break;

		case SDLK_RIGHT: // Change Selection to the right

			if (v_start == true && game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_controlsSelectedMain
				== false)
			{
				std::cout << "Quit" << std::endl;
				v_start = false;
			}
			break;
		case SDLK_LEFT: // Change Selection to the left
			if (v_start == false && game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU &&
				v_controlsSelectedMain == false)
			{
				std::cout << "Play" << std::endl;
				v_start = true;
			}
			break;

		case SDLK_UP: // Change Selection up
			if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_controlsSelectedMain == false)
			{
				std::cout << "Controls" << std::endl;
				v_controlsSelectedMain = true;
				v_start = false;
			}

			break;

		case SDLK_DOWN: // Change Selection down
			if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_controlsSelectedMain == true)
			{
				std::cout << "Play" << std::endl;
				v_controlsSelectedMain = false;
				v_start = true;
			}
			break;

		default: break;
		}


		break;

	// Handle the controller input
	case SDL_JOYBUTTONDOWN:
		switch (e.jbutton.button)
		{
		case 17: // Menu Button
			if (game_screen_manager->GetCurrentScreenIndex() != SCREEN_MENU && game_screen_manager->
				GetCurrentScreenIndex() != SCREEN_UPGRADE)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				game_screen_manager->ChangeScreen(SCREEN_MENU);
				g_mainMenu = true;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_UPGRADE && g_levelOne)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				game_screen_manager->ChangeScreen(SCREEN_MENU);
				g_mainMenu = true;
				g_levelOne = false;
				g_levelTwo = true;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_UPGRADE && g_levelTwo)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				game_screen_manager->ChangeScreen(SCREEN_MENU);
				g_mainMenu = true;
				g_levelTwo = false;
				g_levelThree = true;
			}
			else
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				std::cout << "Quiting..." << std::endl;
				g_quit = true;
			}
			break;

		case 9: // B Button
			if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_start == true && v_controlsSelectedMain
				== false && g_levelOne == true)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
				g_mainMenu = false;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_start == true &&
				v_controlsSelectedMain == false && g_levelTwo == true)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				game_screen_manager->ChangeScreen(SCREEN_LEVEL2);
				g_mainMenu = false;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_start == true &&
				v_controlsSelectedMain == false && g_levelThree == true)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				game_screen_manager->ChangeScreen(SCREEN_LEVEL3);
				g_mainMenu = false;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_start == false &&
				v_controlsSelectedMain == false)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				std::cout << "Quiting..." << std::endl;
				g_quit = true;
			}
			else if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_controlsSelectedMain == true)
			{
				m_audio1->Play(1, m_audio1->m_chunk, 0);
				game_screen_manager->ChangeScreen(SCREEN_CONTROLS);
				v_controlsSelectedMain = false;
				g_mainMenu = false;
				g_controls = true;
			}
			break;

		case 15: // Right Button
			if (v_start == true && game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU)
			{
				std::cout << "Quit" << std::endl;
				v_start = false;
			}
			break;
		case 14: // Left Button
			if (v_start == false && game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU)
			{
				std::cout << "Play" << std::endl;
				v_start = true;
			}
			break;
		case 13: // Up Button
			if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_controlsSelectedMain == false)
			{
				std::cout << "Controls" << std::endl;
				v_controlsSelectedMain = true;
				v_start = false;
			}

			break;

		case 16: // Down Button
			if (game_screen_manager->GetCurrentScreenIndex() == SCREEN_MENU && v_controlsSelectedMain == true)
			{
				std::cout << "Play" << std::endl;
				v_controlsSelectedMain = false;
				v_start = true;
			}
			break;

		default: ;
		}
		break;
	// Click the 'x' button to quit
	case SDL_QUIT:
		m_audio1->Play(1, m_audio1->m_chunk, 0);
		std::cout << "Quiting..." << std::endl;
		return true;


	default: break;
	}

	game_screen_manager->Update(static_cast<float>(new_time - g_old_time) / 1000.0f, e);
	// Update the game screen bases on the frame time
	g_old_time = new_time;

	return false;
}

// Render the current screen to the window
void Render()
{
	// Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	// Set where to render the texture
	game_screen_manager->Render();

	// Render to screen
	SDL_RenderPresent(g_renderer);
}
