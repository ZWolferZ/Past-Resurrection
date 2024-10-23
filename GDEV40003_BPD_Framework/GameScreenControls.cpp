// ----------------------------- INCLUDE ----------------------------- //
#include "GameScreenControls.h"
// ----------------------------- INCLUDE ----------------------------- //


// Initialize the GameScreenControls Screen, by parsing the renderer and setting up the level
GameScreenControls::GameScreenControls(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	m_background_texture = nullptr;

	SetUpLevel();
}

// Delete all of the gameobjects in the scene
GameScreenControls::~GameScreenControls()
{
	if (m_background_texture != nullptr)
	{
		delete m_background_texture;
		m_background_texture = nullptr;
	}
}

// Render all of the gameobjects in the scene
void GameScreenControls::Render()
{
	if (m_background_texture != nullptr)
	{
		m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	}
}

// Update all of the gameobjects in the scene and parse the user input
void GameScreenControls::Update(float deltaTime, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RETURN:
			if (v_inControls)
			{
				// Go back to the main menu
				g_continue = true;
			}

			break;
		default: break;
		}
	}
	if (e.type == SDL_JOYBUTTONDOWN)
	{
		switch (e.jbutton.button)
		{
		case 9:
			if (v_inControls)
			{
				// Go back to the main menu
				g_continue = true;
			}
			break;
		default: break;
		}
	}
	// After one pass, you are in the controls
	v_inControls = true;
}

// Initialize the level by creating all of the gameobjects
bool GameScreenControls::SetUpLevel()
{
	// Not in the controls menu yet
	v_inControls = false;

	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/Controls.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	return true;
}
