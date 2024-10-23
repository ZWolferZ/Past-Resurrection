// ----------------------------- INCLUDE ----------------------------- //
#include "GameScreenOver.h"
// ----------------------------- INCLUDE ----------------------------- //

// Initialize the GameScreenOver screen by passing the renderer and setting up the level
GameScreenOver::GameScreenOver(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	m_background_texture = nullptr;

	SetUpLevel();
}

// Delete the textures and gameobjects in the scene
GameScreenOver::~GameScreenOver()
{
	if (m_background_texture != nullptr)
	{
		delete m_background_texture;
		m_background_texture = nullptr;
	}
	if (m_continueSelect_texture != nullptr)
	{
		delete m_continueSelect_texture;
		m_continueSelect_texture = nullptr;
	}
	if (m_continuetNotSelect_texture != nullptr)
	{
		delete m_continuetNotSelect_texture;
		m_continuetNotSelect_texture = nullptr;
	}
	if (m_quitSelect_texture != nullptr)
	{
		delete m_quitSelect_texture;
		m_quitSelect_texture = nullptr;
	}
	if (m_quitNotSelect_texture != nullptr)
	{
		delete m_quitNotSelect_texture;
		m_quitNotSelect_texture = nullptr;
	}
}

// Render the gameobjects in the scene
void GameScreenOver::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	// Render based on the selected option
	if (v_continueSelected)
	{
		m_continueSelect_texture->Render();
		m_quitNotSelect_texture->Render();
	}
	else
	{
		m_continuetNotSelect_texture->Render();
		m_quitSelect_texture->Render();
	}
}

// Update the scene based on the input
void GameScreenOver::Update(float deltaTime, SDL_Event e)
{
	// Check for keyboard input
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT: // Move selection right
			if (v_continueSelected)
			{
				v_continueSelected = false;
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
			}
			break;
		case SDLK_LEFT: // Move selection left
			if (!v_continueSelected)
			{
				v_continueSelected = true;
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
			}
			break;

		case SDLK_RETURN: // Select option
			if (v_continueSelected)
			{
				// Go to main menu

				// You might see this global variable used in other situations where the name does not make too much sense,
				// but it is used to control the flow of the game and always returns the player back to the main menu : https://www.youtube.com/watch?v=DzpmhfiBCO8

				g_continue = true;
			}
			else
			{
				g_quit = true;
				std::cout << "Quiting..." << std::endl;
			}
		default: break;
		}
	}

	// Check for controller input
	if (e.type == SDL_JOYBUTTONDOWN)
	{
		switch (e.jbutton.button)
		{
		case 15:
			if (v_continueSelected)
			{
				v_continueSelected = false;
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
			}
			break;
		case 14:
			if (!v_continueSelected)
			{
				v_continueSelected = true;
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
			}
			break;

		case 9:
			if (v_continueSelected)
			{
				g_continue = true;
			}
			else
			{
				g_quit = true;
				std::cout << "Quiting..." << std::endl;
			}
			break;
		default: break;
		}
	}
}

// Initialize the textures and gameobjects in the scene
bool GameScreenOver::SetUpLevel()
{
	v_continueSelected = true;

	m_background_texture = new Texture2D(m_renderer);

	m_continueSelect_texture = new GameObject(m_renderer, "Images/continueselected.png",
	                                          Vector2D(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2));

	m_continuetNotSelect_texture = new GameObject(m_renderer, "Images/continuenotselected.png",
	                                              Vector2D(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2));

	m_quitSelect_texture = new GameObject(m_renderer, "Images/quitselected.png",
	                                      Vector2D(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2));

	m_quitNotSelect_texture = new GameObject(m_renderer, "Images/quitnotselected.png",
	                                         Vector2D(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2));

	m_menuselectionaudio = new Audio();
	m_menuselectionaudio->LoadFromFile("Sound/MenuSelect.wav");

	if (!m_background_texture->LoadFromFile("Images/GameOver.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	return true;
}
