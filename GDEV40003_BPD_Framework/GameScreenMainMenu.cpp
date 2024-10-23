// ----------------------------- INCLUDE ----------------------------- //
#include "GameScreenMainMenu.h"
// ----------------------------- INCLUDE ----------------------------- //


// Initialize the GameScreenMainMenu and sets up the renderer and start state.
GameScreenMainMenu::GameScreenMainMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;

	m_background_texture = nullptr;

	m_quitSelect_texture = nullptr;
	m_startSelect_texture = nullptr;
	m_quitNotSelect_texture = nullptr;
	m_startNotSelect_texture = nullptr;
	m_controlsNotSelect_texture = nullptr;
	m_controlsSelect_texture = nullptr;
	m_gameText = nullptr;
	v_startState = true;

	SetUpLevel();
}

// Delete all of the game objects in the scene, if they exist.
GameScreenMainMenu::~GameScreenMainMenu()
{
	if (m_background_texture != nullptr)
	{
		delete m_background_texture;
		m_background_texture = nullptr;
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
	if (m_startSelect_texture != nullptr)
	{
		delete m_startSelect_texture;
		m_startSelect_texture = nullptr;
	}
	if (m_startNotSelect_texture != nullptr)
	{
		delete m_startNotSelect_texture;
		m_startNotSelect_texture = nullptr;
	}

	if (m_controlsNotSelect_texture != nullptr)
	{
		delete m_controlsNotSelect_texture;
		m_controlsNotSelect_texture = nullptr;
	}
	if (m_controlsSelect_texture != nullptr)
	{
		delete m_controlsSelect_texture;
		m_controlsSelect_texture = nullptr;
	}

	if (m_gameText != nullptr)
	{
		delete m_gameText;
		m_gameText = nullptr;
	}

	if (m_gameText2 != nullptr)
	{
		delete m_gameText2;
		m_gameText2 = nullptr;
	}

	if (m_gameText3 != nullptr)
	{
		delete m_gameText3;
		m_gameText3 = nullptr;
	}
}

// Render the game objects to the screen.
void GameScreenMainMenu::Render()
{
	if (m_background_texture != nullptr)
	{
		m_background_texture->Render(Vector2D(), SDL_FLIP_NONE, 0.0);
	}

	if (m_quitSelect_texture != nullptr)
	{
		m_quitSelect_texture->Render();
	}

	if (m_quitNotSelect_texture != nullptr)
	{
		m_quitNotSelect_texture->Render();
	}

	if (m_startSelect_texture != nullptr)
	{
		m_startSelect_texture->Render();
	}

	if (m_startNotSelect_texture != nullptr)
	{
		m_startNotSelect_texture->Render();
	}

	// Determine which controls texture to render based on the selected state, and render it.
	// The controls button was implmented after the game was completed, so it uses a better logic method than the other buttons.
	if (m_controlsNotSelect_texture != nullptr && v_controlsSelected == false)
	{
		m_controlsNotSelect_texture->Render();
	}
	else if (m_controlsSelect_texture != nullptr && v_controlsSelected == true)
	{
		m_controlsSelect_texture->Render();
	}

	if (m_gameText != nullptr)
	{
		m_gameText->SetColor(SDL_Color{255, 255, 0, 255});
		m_gameText->RenderAt("NOW WITH SOUND!", 600, 453);
	}

	if (m_gameText2 != nullptr)
	{
		m_gameText2->SetColor(SDL_Color{255, 255, 0, 255});
		m_gameText2->RenderAt("HIGH-SCORE: ", 10, 453);
	}

	if (m_gameText3 != nullptr)
	{
		m_gameText3->SetColor(SDL_Color{255, 255, 0, 255});
		m_gameText3->RenderAt(std::to_string(g_highScore), 150, 453);
	}
}

// Update the game objects in the scene.
void GameScreenMainMenu::Update(float deltaTime, SDL_Event e)
{
	// Check for keyboard input 
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT: // Move the selection to the right.
			if (GetStartState() == true && !v_controlsSelected)
			{
				SetStartState(false);
				m_audio->Play(1, m_audio->m_chunk, 0);
			}
			break;
		case SDLK_LEFT: // Move the selection to the left.
			if (GetStartState() == false && !v_controlsSelected)
			{
				SetStartState(true);
				m_audio->Play(1, m_audio->m_chunk, 0);
			}
			break;
		case SDLK_UP: // Move the selection up.

			if (!v_controlsSelected)
			{
				SetStartState(false);
				m_audio->Play(1, m_audio->m_chunk, 0);
				v_controlsSelected = true;
			}

			break;

		case SDLK_DOWN: // Move the selection down.

			if (v_controlsSelected)
			{
				SetStartState(true);
				m_audio->Play(1, m_audio->m_chunk, 0);
				v_controlsSelected = false;
			}

			break;
		default: break;
		}
	}

	// Check for controller input
	if (e.type == SDL_JOYBUTTONDOWN)
	{
		switch (e.jbutton.button)
		{
		case 15: // Move the selection to the right.
			if (GetStartState() == true)
			{
				SetStartState(false);
				m_audio->Play(1, m_audio->m_chunk, 0);
			}
			break;
		case 14: // Move the selection to the left.
			if (GetStartState() == false)
			{
				SetStartState(true);
				m_audio->Play(1, m_audio->m_chunk, 0);
			}
			break;
		case 13: // Move the selection up.

			if (!v_controlsSelected)
			{
				SetStartState(false);
				m_audio->Play(1, m_audio->m_chunk, 0);
				v_controlsSelected = true;
			}

			break;

		case 16: // Move the selection down.

			if (v_controlsSelected)
			{
				SetStartState(true);
				m_audio->Play(1, m_audio->m_chunk, 0);
				v_controlsSelected = false;
			}

			break;
		default: break;
		}
	}

	// The UI logic here is really badly done as it was one of the first things I did in the project, so it's not very clean.
	// In this implementation, I send the buttons to the void if they are not selected.

	// Only later did I realise that I could have stopped rendering the buttons if they were not selected, but it works so... : https://www.youtube.com/watch?v=HPdURyombM0
	if (GetStartState() == true)
	{
		if (v_controlsSelected)
		{
			m_startNotSelect_texture->SetPosition(Vector2D(140, 300));
			m_quitNotSelect_texture->SetPosition(Vector2D(450, 300));
		}
		else
		{
			m_startSelect_texture->SetPosition(Vector2D(140, 300));
			m_startNotSelect_texture->SetPosition(Vector2D(theVoid, theVoid));
			m_quitNotSelect_texture->SetPosition(Vector2D(450, 300));
			m_quitSelect_texture->SetPosition(Vector2D(theVoid, theVoid));
		}
	}
	else if (GetStartState() == false)
	{
		if (v_controlsSelected)
		{
			m_startNotSelect_texture->SetPosition(Vector2D(140, 300));
			m_quitNotSelect_texture->SetPosition(Vector2D(450, 300));
		}
		else
		{
			m_startNotSelect_texture->SetPosition(Vector2D(140, 300));
			m_startSelect_texture->SetPosition(Vector2D(theVoid, theVoid));
			m_quitSelect_texture->SetPosition(Vector2D(450, 300));
			m_quitNotSelect_texture->SetPosition(Vector2D(theVoid, theVoid));
		}
	}
}

// Set up the main menu by initialising the game objects and load the textures.
bool GameScreenMainMenu::SetUpLevel()
{
	// Set the game states to their default values.
	v_startState = true;
	v_controlsSelected = false;
	g_score = 0;

	// Set up the background texture.
	m_background_texture = new Texture2D(m_renderer);

	// Initialise the UI as gameobjects.
	m_quitSelect_texture = new GameObject(m_renderer, "Images/quitselected.png", Vector2D(250, 300));
	m_startSelect_texture = new GameObject(m_renderer, "Images/playselected.png", Vector2D(140, 300));
	m_quitNotSelect_texture = new GameObject(m_renderer, "Images/quitnotselected.png", Vector2D(250, 300));
	m_startNotSelect_texture = new GameObject(m_renderer, "Images/playnotselected.png", Vector2D(140, 300));
	m_controlsNotSelect_texture = new GameObject(m_renderer, "Images/ControlsNotSelcted.png", Vector2D(290, 200));
	m_controlsSelect_texture = new GameObject(m_renderer, "Images/ControlsSelected.png", Vector2D(290, 200));

	// Load the audio file for the menu.
	m_audio = new Audio();
	m_audio->LoadFromFile("Sound/MenuSelect.wav");

	// Set up the game text.
	m_gameText = new GameText(m_renderer, "fonts/arial.ttf", 20);
	m_gameText2 = new GameText(m_renderer, "fonts/arial.ttf", 20);
	m_gameText3 = new GameText(m_renderer, "fonts/arial.ttf", 20);

	// Load the background texture.
	if (!m_background_texture->LoadFromFile("Images/mainmenubackground.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	return true;
}
