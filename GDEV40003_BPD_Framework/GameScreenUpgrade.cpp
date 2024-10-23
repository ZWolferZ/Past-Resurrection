// ----------------------------- INCLUDE ----------------------------- //
#include "GameScreenUpgrade.h"
// ----------------------------- INCLUDE ----------------------------- //

bool v_moneytimer = false; // Cannot be placed in header file as it is used in timers (I don't know why)


// Initialize the GameScreenUpgrade screen by parsing the renderer and setting up the level
GameScreenUpgrade::GameScreenUpgrade(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	m_background_texture = nullptr;

	SetUpLevel();
}

// Delete the Gameobjects and Textures in the scene, if they exist
// I forgot to add a lot of cases in the evercade port, so uhhh: https://youtu.be/irxkZQTTdm4?si=ppFBa2o1rwYdFNVp
GameScreenUpgrade::~GameScreenUpgrade()
{
	if (m_background_texture != nullptr)
	{
		delete m_background_texture;
		m_background_texture = nullptr;
	}

	if (m_BackSelected_texture != nullptr)
	{
		delete m_BackSelected_texture;
		m_BackSelected_texture = nullptr;
	}

	if (m_ContinueSelected_texture != nullptr)
	{
		delete m_ContinueSelected_texture;
		m_ContinueSelected_texture = nullptr;
	}

	if (m_BackNotSelected_texture != nullptr)
	{
		delete m_BackNotSelected_texture;
		m_BackNotSelected_texture = nullptr;
	}

	if (m_ContinueNotSelected_texture != nullptr)
	{
		delete m_ContinueNotSelected_texture;
		m_ContinueNotSelected_texture = nullptr;
	}

	if (m_HealthUpgrade1Selected_texture != nullptr)
	{
		delete m_HealthUpgrade1Selected_texture;
		m_HealthUpgrade1Selected_texture = nullptr;
	}

	if (m_HealthUpgrade1NotSelected_texture != nullptr)
	{
		delete m_HealthUpgrade1NotSelected_texture;
		m_HealthUpgrade1NotSelected_texture = nullptr;
	}

	if (m_HealthUpgrade1Bought_texture != nullptr)
	{
		delete m_HealthUpgrade1Bought_texture;
		m_HealthUpgrade1Bought_texture = nullptr;
	}

	if (m_HealthUpgrade2Selected_texture != nullptr)
	{
		delete m_HealthUpgrade2Selected_texture;
		m_HealthUpgrade2Selected_texture = nullptr;
	}

	if (m_HealthUpgrade2NotSelected_texture != nullptr)
	{
		delete m_HealthUpgrade2NotSelected_texture;
		m_HealthUpgrade2NotSelected_texture = nullptr;
	}

	if (m_HealthUpgrade2Bought_texture != nullptr)
	{
		delete m_HealthUpgrade2Bought_texture;
		m_HealthUpgrade2Bought_texture = nullptr;
	}

	if (m_HealthUpgrade3Selected_texture != nullptr)
	{
		delete m_HealthUpgrade3Selected_texture;
		m_HealthUpgrade3Selected_texture = nullptr;
	}

	if (m_HealthUpgrade3NotSelected_texture != nullptr)
	{
		delete m_HealthUpgrade3NotSelected_texture;
		m_HealthUpgrade3NotSelected_texture = nullptr;
	}

	if (m_HealthUpgrade3Bought_texture != nullptr)
	{
		delete m_HealthUpgrade3Bought_texture;
		m_HealthUpgrade3Bought_texture = nullptr;
	}

	if (m_BaseHealthUpgrade1Selected_texture != nullptr)
	{
		delete m_BaseHealthUpgrade1Selected_texture;
		m_BaseHealthUpgrade1Selected_texture = nullptr;
	}

	if (m_BaseHealthUpgrade1NotSelected_texture != nullptr)
	{
		delete m_BaseHealthUpgrade1NotSelected_texture;
		m_BaseHealthUpgrade1NotSelected_texture = nullptr;
	}

	if (m_BaseHealthUpgrade1Bought_texture != nullptr)
	{
		delete m_BaseHealthUpgrade1Bought_texture;
		m_BaseHealthUpgrade1Bought_texture = nullptr;
	}

	if (m_BaseHealthUpgrade2Selected_texture != nullptr)
	{
		delete m_BaseHealthUpgrade2Selected_texture;
		m_BaseHealthUpgrade2Selected_texture = nullptr;
	}

	if (m_BaseHealthUpgrade2NotSelected_texture != nullptr)
	{
		delete m_BaseHealthUpgrade2NotSelected_texture;
		m_BaseHealthUpgrade2NotSelected_texture = nullptr;
	}

	if (m_BaseHealthUpgrade2Bought_texture != nullptr)
	{
		delete m_BaseHealthUpgrade2Bought_texture;
		m_BaseHealthUpgrade2Bought_texture = nullptr;
	}

	if (m_BaseHealthUpgrade3Selected_texture != nullptr)
	{
		delete m_BaseHealthUpgrade3Selected_texture;
		m_BaseHealthUpgrade3Selected_texture = nullptr;
	}

	if (m_BaseHealthUpgrade3NotSelected_texture != nullptr)
	{
		delete m_BaseHealthUpgrade3NotSelected_texture;
		m_BaseHealthUpgrade3NotSelected_texture = nullptr;
	}

	if (m_BaseHealthUpgrade3Bought_texture != nullptr)
	{
		delete m_BaseHealthUpgrade3Bought_texture;
		m_BaseHealthUpgrade3Bought_texture = nullptr;
	}

	if (m_scoreIcon != nullptr)
	{
		delete m_scoreIcon;
		m_scoreIcon = nullptr;
	}

	if (m_scoreText != nullptr)
	{
		delete m_scoreText;
		m_scoreText = nullptr;
	}
}

// Render objects in the scene
// There is so much boolean logic to determine what to render, it is a bit of a mess,
// but it works and is easy to understand
void GameScreenUpgrade::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);


	if (continueSelected && backSelected == false)
	{
		m_ContinueSelected_texture->Render();
		m_BackNotSelected_texture->Render();
	}
	else if (!continueSelected && backSelected == true)
	{
		m_ContinueNotSelected_texture->Render();
		m_BackSelected_texture->Render();
	}
	else if (!continueSelected && !backSelected)
	{
		m_ContinueNotSelected_texture->Render();
		m_BackNotSelected_texture->Render();
	}

	if (healthUpgrade1Selected && !healthUpgrade1Bought)
	{
		m_HealthUpgrade1Selected_texture->Render();
	}
	else if (!healthUpgrade1Selected && !healthUpgrade1Bought)
	{
		m_HealthUpgrade1NotSelected_texture->Render();
	}
	else if (healthUpgrade1Bought)
	{
		m_HealthUpgrade1Bought_texture->Render();
	}


	if (healthUpgrade2Selected && !healthUpgrade2Bought)
	{
		m_HealthUpgrade2Selected_texture->Render();
	}
	else if (!healthUpgrade2Selected && !healthUpgrade2Bought)
	{
		m_HealthUpgrade2NotSelected_texture->Render();
	}
	else if (healthUpgrade2Bought)
	{
		m_HealthUpgrade2Bought_texture->Render();
	}


	if (healthUpgrade3Selected && !healthUpgrade3Bought)
	{
		m_HealthUpgrade3Selected_texture->Render();
	}
	else if (!healthUpgrade3Selected && !healthUpgrade3Bought)
	{
		m_HealthUpgrade3NotSelected_texture->Render();
	}
	else if (healthUpgrade3Bought)
	{
		m_HealthUpgrade3Bought_texture->Render();
	}


	if (baseHealthUpgrade1Selected && !baseHealthUpgrade1Bought)
	{
		m_BaseHealthUpgrade1Selected_texture->Render();
	}
	else if (!baseHealthUpgrade1Selected && !baseHealthUpgrade1Bought)
	{
		m_BaseHealthUpgrade1NotSelected_texture->Render();
	}
	else if (baseHealthUpgrade1Bought)
	{
		m_BaseHealthUpgrade1Bought_texture->Render();
	}

	if (baseHealthUpgrade2Selected && !baseHealthUpgrade2Bought)
	{
		m_BaseHealthUpgrade2Selected_texture->Render();
	}
	else if (!baseHealthUpgrade2Selected && !baseHealthUpgrade2Bought)
	{
		m_BaseHealthUpgrade2NotSelected_texture->Render();
	}
	else if (baseHealthUpgrade2Bought)
	{
		m_BaseHealthUpgrade2Bought_texture->Render();
	}

	if (baseHealthUpgrade3Selected && !baseHealthUpgrade3Bought)
	{
		m_BaseHealthUpgrade3Selected_texture->Render();
	}
	else if (!baseHealthUpgrade3Selected && !baseHealthUpgrade3Bought)
	{
		m_BaseHealthUpgrade3NotSelected_texture->Render();
	}
	else if (baseHealthUpgrade3Bought)
	{
		m_BaseHealthUpgrade3Bought_texture->Render();
	}
}

// Update the gameobjects in the scene
void GameScreenUpgrade::Update(float deltaTime, SDL_Event e)
{
	// Quickly check if the player has bought any upgrades before
	if (g_playerHealthUpgrade1 == true)
	{
		healthUpgrade1Bought = true;
	}
	if (g_playerHealthUpgrade2 == true)
	{
		healthUpgrade2Bought = true;
	}
	if (g_playerHealthUpgrade3 == true)
	{
		healthUpgrade3Bought = true;
	}
	if (g_baseHealthUpgrade1 == true)
	{
		baseHealthUpgrade1Bought = true;
	}
	if (g_baseHealthUpgrade2 == true)
	{
		baseHealthUpgrade2Bought = true;
	}
	if (g_baseHealthUpgrade3 == true)
	{
		baseHealthUpgrade3Bought = true;
	}

	// Check for keyboard input
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RETURN:

			// Check if the player has selected the continue button
			if (continueSelected && g_levelThree == true && !healthUpgrade1Selected && !healthUpgrade2Selected && !
				healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				// Go to level 3
				g_playerconfirmation = true;
			}

			// Check if the player has selected the back button
			else if (!continueSelected && backSelected == true && g_levelThree == true && !healthUpgrade1Selected && !
				healthUpgrade2Selected &&
				!healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				// Go back to the main menu
				g_continue = true;
			}

		// Check if the player has selected the continue button
			if (continueSelected && g_levelTwo == true && !healthUpgrade1Selected && !healthUpgrade2Selected && !
				healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				// Go to level 3
				g_levelTwo = false;

				g_levelThree = true;

				g_playerconfirmation = true;
			}
			else if (!continueSelected && backSelected == true && g_levelTwo == true && !healthUpgrade1Selected && !
				healthUpgrade2Selected && !
				healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				// Go back to the main menu and set the level to 3
				g_continue = true;

				g_levelTwo = false;

				g_levelThree = true;
			}


			if (continueSelected && backSelected == false && !g_levelTwo && !g_levelThree && !healthUpgrade1Selected &&
				!healthUpgrade2Selected && !
				healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				// Go to level 2
				std::cout << "Continue Confirmed" << std::endl;
				g_levelOne = false;
				g_levelTwo = true;
				g_playerconfirmation = true;
			}
			else if (!continueSelected && backSelected == true && !g_levelTwo && !g_levelThree && !
				healthUpgrade1Selected && !
				healthUpgrade2Selected && !
				healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				// Go back to the main menu and set the level to level 2
				std::cout << "Back Confirmed" << std::endl;
				g_continue = true;
				g_levelOne = false;
				g_levelTwo = true;
			}

		// Check if the player has selected the health upgrade 1 button
			if (healthUpgrade1Selected && !healthUpgrade1Bought && g_score >= 200)
			{
				// Set the cooldown timer to true
				v_moneytimer = true;

				// Set the upgrade to bought
				healthUpgrade1Bought = true;
				g_playerHealthUpgrade1 = true;

				// Play the buy sound
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);

				// Deduct the score
				g_score -= 250;

				// Set the cooldown timer to false after 300ms
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			// If the player does not have enough score, play a error sound
			else if (g_score < 200 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}

			if (healthUpgrade2Selected && !healthUpgrade2Bought && g_score >= 250)
			{
				v_moneytimer = true;
				healthUpgrade2Bought = true;
				g_playerHealthUpgrade2 = true;
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);
				g_score -= 250;
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			else if (g_score < 250 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}

			if (healthUpgrade3Selected && !healthUpgrade3Bought && g_score >= 300)
			{
				v_moneytimer = true;
				healthUpgrade3Bought = true;
				g_playerHealthUpgrade3 = true;
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);
				g_score -= 300;
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			else if (g_score < 300 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}


			if (baseHealthUpgrade1Selected && !baseHealthUpgrade1Bought && g_score >= 200)
			{
				v_moneytimer = true;
				baseHealthUpgrade1Bought = true;
				g_baseHealthUpgrade1 = true;
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);
				g_score -= 200;
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			else if (g_score < 200 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}

			if (baseHealthUpgrade2Selected && !baseHealthUpgrade2Bought && g_score >= 250)
			{
				v_moneytimer = true;
				baseHealthUpgrade2Bought = true;
				g_baseHealthUpgrade2 = true;
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);
				g_score -= 250;
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			else if (g_score < 250 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}
			if (baseHealthUpgrade3Selected && !baseHealthUpgrade3Bought && g_score >= 300)
			{
				v_moneytimer = true;
				baseHealthUpgrade3Bought = true;
				g_baseHealthUpgrade3 = true;
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);
				g_score -= 300;
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			else if (g_score < 300 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}

			break;

		case SDLK_RIGHT: // Cases for the right key, change the selected button
			if (continueSelected && !backSelected)
			{
				// Play the menu selection sound
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);

				// Change the selected button
				continueSelected = false;
				backSelected = true;

				std::cout << "Back Selected" << std::endl;
			}

			if (healthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade1Selected = false;
				baseHealthUpgrade1Selected = true;
				std::cout << "Base Health Upgrade 1 Selected" << std::endl;
			}
			else if (healthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade2Selected = false;
				baseHealthUpgrade2Selected = true;
				std::cout << "Base Health Upgrade 2 Selected" << std::endl;
			}
			else if (healthUpgrade3Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade3Selected = false;
				baseHealthUpgrade3Selected = true;
				std::cout << "Base Health Upgrade 3 Selected" << std::endl;
			}

			break;

		case SDLK_LEFT: // Cases for the left key, change the selected button
			if (!continueSelected && backSelected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				continueSelected = true;
				backSelected = false;
				std::cout << "Continue Selected" << std::endl;
			}

			if (baseHealthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade1Selected = true;
				baseHealthUpgrade1Selected = false;
				std::cout << " Health Upgrade 1 Selected" << std::endl;
			}
			else if (baseHealthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade2Selected = true;
				baseHealthUpgrade2Selected = false;
				std::cout << "Base Health Upgrade 2 Selected" << std::endl;
			}
			else if (baseHealthUpgrade3Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade3Selected = true;
				baseHealthUpgrade3Selected = false;
				std::cout << "Base Health Upgrade 3 Selected" << std::endl;
			}
			break;

		case SDLK_UP: // Cases for the up key, change the selected button

			if (continueSelected && !backSelected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				continueSelected = false;
				healthUpgrade1Selected = true;
				std::cout << "Health Upgrade 1 Selected" << std::endl;
			}
			else if (healthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade1Selected = false;
				healthUpgrade2Selected = true;
				std::cout << "Health Upgrade 2 Selected" << std::endl;
			}
			else if (healthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade2Selected = false;
				healthUpgrade3Selected = true;
				std::cout << "Health Upgrade 3 Selected" << std::endl;
			}


			if (!continueSelected && backSelected == true)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				backSelected = false;
				baseHealthUpgrade1Selected = true;
				std::cout << "Base Health Upgrade 1 Selected" << std::endl;
			}
			else if (baseHealthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				baseHealthUpgrade1Selected = false;
				baseHealthUpgrade2Selected = true;
				std::cout << "Base Health Upgrade 2 Selected" << std::endl;
			}
			else if (baseHealthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				baseHealthUpgrade2Selected = false;
				baseHealthUpgrade3Selected = true;
				std::cout << "Base Health Upgrade 3 Selected" << std::endl;
			}


			break;

		case SDLK_DOWN: // Cases for the down key, change the selected button
			if (healthUpgrade3Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade2Selected = true;
				healthUpgrade3Selected = false;
				std::cout << "Health Upgrade 2 Selected" << std::endl;
			}
			else if (healthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade2Selected = false;
				healthUpgrade1Selected = true;
				std::cout << "Health Upgrade 1 Selected" << std::endl;
			}

			else if (healthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				continueSelected = true;
				backSelected = false;
				healthUpgrade1Selected = false;
				std::cout << "Continue Selected" << std::endl;
			}

			if (baseHealthUpgrade3Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				baseHealthUpgrade3Selected = false;
				baseHealthUpgrade2Selected = true;
				std::cout << " Base Health Upgrade 2 Selected" << std::endl;
			}
			else if (baseHealthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				baseHealthUpgrade2Selected = false;
				baseHealthUpgrade1Selected = true;
				std::cout << " Base Health Upgrade 1 Selected" << std::endl;
			}
			else if (baseHealthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				baseHealthUpgrade1Selected = false;
				continueSelected = false;
				backSelected = true;
				std::cout << "Back Selected" << std::endl;
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
		case 9:

			if (continueSelected && g_levelThree == true && !healthUpgrade1Selected && !healthUpgrade2Selected && !
				healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				g_playerconfirmation = true;
			}
			else if (!continueSelected && backSelected == true && g_levelThree == true && !healthUpgrade1Selected && !
				healthUpgrade2Selected &&
				!healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				g_continue = true;
			}

			if (continueSelected && g_levelTwo == true && !healthUpgrade1Selected && !healthUpgrade2Selected && !
				healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				g_levelTwo = false;

				g_levelThree = true;

				g_playerconfirmation = true;
			}
			else if (!continueSelected && backSelected == true && g_levelTwo == true && !healthUpgrade1Selected && !
				healthUpgrade2Selected && !
				healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				g_continue = true;

				g_levelTwo = false;

				g_levelThree = true;
			}


			if (continueSelected && backSelected == false && !g_levelTwo && !g_levelThree && !healthUpgrade1Selected &&
				!healthUpgrade2Selected && !
				healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				std::cout << "Continue Confirmed" << std::endl;
				g_levelOne = false;
				g_levelTwo = true;
				g_playerconfirmation = true;
			}
			else if (!continueSelected && backSelected == true && !g_levelTwo && !g_levelThree && !
				healthUpgrade1Selected && !
				healthUpgrade2Selected && !
				healthUpgrade3Selected && !baseHealthUpgrade1Selected && !baseHealthUpgrade2Selected && !
				baseHealthUpgrade3Selected)
			{
				std::cout << "Back Confirmed" << std::endl;
				g_continue = true;
				g_levelOne = false;
				g_levelTwo = true;
			}


			if (healthUpgrade1Selected && !healthUpgrade1Bought && g_score >= 200)
			{
				v_moneytimer = true;
				healthUpgrade1Bought = true;
				g_playerHealthUpgrade1 = true;
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);
				g_score -= 250;
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			else if (g_score < 200 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}

			if (healthUpgrade2Selected && !healthUpgrade2Bought && g_score >= 250)
			{
				v_moneytimer = true;
				healthUpgrade2Bought = true;
				g_playerHealthUpgrade2 = true;
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);
				g_score -= 250;
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			else if (g_score < 250 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}

			if (healthUpgrade3Selected && !healthUpgrade3Bought && g_score >= 300)
			{
				v_moneytimer = true;
				healthUpgrade3Bought = true;
				g_playerHealthUpgrade3 = true;
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);
				g_score -= 300;
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			else if (g_score < 300 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}


			if (baseHealthUpgrade1Selected && !baseHealthUpgrade1Bought && g_score >= 200)
			{
				v_moneytimer = true;
				baseHealthUpgrade1Bought = true;
				g_baseHealthUpgrade1 = true;
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);
				g_score -= 200;
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			else if (g_score < 200 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}

			if (baseHealthUpgrade2Selected && !baseHealthUpgrade2Bought && g_score >= 250)
			{
				v_moneytimer = true;
				baseHealthUpgrade2Bought = true;
				g_baseHealthUpgrade2 = true;
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);
				g_score -= 250;
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			else if (g_score < 250 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}
			if (baseHealthUpgrade3Selected && !baseHealthUpgrade3Bought && g_score >= 300)
			{
				v_moneytimer = true;
				baseHealthUpgrade3Bought = true;
				g_baseHealthUpgrade3 = true;
				m_buyaudio->Play(1, m_buyaudio->m_chunk, 0);
				g_score -= 300;
				SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
				{
					v_moneytimer = false;
					return 0;
				}, this);
			}
			else if (g_score < 300 && v_moneytimer == false)
			{
				m_erroraudio->Play(1, m_erroraudio->m_chunk, 0);
			}

			break;


		case 15:
			if (continueSelected && !backSelected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				continueSelected = false;
				backSelected = true;
				std::cout << "Back Selected" << std::endl;
			}

			if (healthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade1Selected = false;
				baseHealthUpgrade1Selected = true;
				std::cout << "Base Health Upgrade 1 Selected" << std::endl;
			}
			else if (healthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade2Selected = false;
				baseHealthUpgrade2Selected = true;
				std::cout << "Base Health Upgrade 2 Selected" << std::endl;
			}
			else if (healthUpgrade3Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade3Selected = false;
				baseHealthUpgrade3Selected = true;
				std::cout << "Base Health Upgrade 3 Selected" << std::endl;
			}

			break;

		case 14:
			if (!continueSelected && backSelected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				continueSelected = true;
				backSelected = false;
				std::cout << "Continue Selected" << std::endl;
			}

			if (baseHealthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade1Selected = true;
				baseHealthUpgrade1Selected = false;
				std::cout << " Health Upgrade 1 Selected" << std::endl;
			}
			else if (baseHealthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade2Selected = true;
				baseHealthUpgrade2Selected = false;
				std::cout << "Base Health Upgrade 2 Selected" << std::endl;
			}
			else if (baseHealthUpgrade3Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade3Selected = true;
				baseHealthUpgrade3Selected = false;
				std::cout << "Base Health Upgrade 3 Selected" << std::endl;
			}
			break;

		case 13:

			if (continueSelected && !backSelected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				continueSelected = false;
				healthUpgrade1Selected = true;
				std::cout << "Health Upgrade 1 Selected" << std::endl;
			}
			else if (healthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade1Selected = false;
				healthUpgrade2Selected = true;
				std::cout << "Health Upgrade 2 Selected" << std::endl;
			}
			else if (healthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade2Selected = false;
				healthUpgrade3Selected = true;
				std::cout << "Health Upgrade 3 Selected" << std::endl;
			}


			if (!continueSelected && backSelected == true)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				backSelected = false;
				baseHealthUpgrade1Selected = true;
				std::cout << "Base Health Upgrade 1 Selected" << std::endl;
			}
			else if (baseHealthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				baseHealthUpgrade1Selected = false;
				baseHealthUpgrade2Selected = true;
				std::cout << "Base Health Upgrade 2 Selected" << std::endl;
			}
			else if (baseHealthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				baseHealthUpgrade2Selected = false;
				baseHealthUpgrade3Selected = true;
				std::cout << "Base Health Upgrade 3 Selected" << std::endl;
			}


			break;

		case 16:
			if (healthUpgrade3Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade2Selected = true;
				healthUpgrade3Selected = false;
				std::cout << "Health Upgrade 2 Selected" << std::endl;
			}
			else if (healthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				healthUpgrade2Selected = false;
				healthUpgrade1Selected = true;
				std::cout << "Health Upgrade 1 Selected" << std::endl;
			}

			else if (healthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				continueSelected = true;
				backSelected = false;
				healthUpgrade1Selected = false;
				std::cout << "Continue Selected" << std::endl;
			}

			if (baseHealthUpgrade3Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				baseHealthUpgrade3Selected = false;
				baseHealthUpgrade2Selected = true;
				std::cout << " Base Health Upgrade 2 Selected" << std::endl;
			}
			else if (baseHealthUpgrade2Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				baseHealthUpgrade2Selected = false;
				baseHealthUpgrade1Selected = true;
				std::cout << " Base Health Upgrade 1 Selected" << std::endl;
			}
			else if (baseHealthUpgrade1Selected)
			{
				m_menuselectionaudio->Play(1, m_menuselectionaudio->m_chunk, 0);
				baseHealthUpgrade1Selected = false;
				continueSelected = false;
				backSelected = true;
				std::cout << "Back Selected" << std::endl;
			}

			break;
		default: break;
		}
	}
}

// Initialize the gameobjects in the scene
bool GameScreenUpgrade::SetUpLevel()
{
	// Reset the local bool
	v_moneytimer = false;

	// Initialize the background texture
	m_background_texture = new Texture2D(m_renderer);

	// Initialize the audio
	m_menuselectionaudio = new Audio();
	m_menuselectionaudio->LoadFromFile("Sound/MenuSelect.wav");
	m_buyaudio = new Audio();
	m_buyaudio->LoadFromFile("Sound/Buy.wav");
	m_erroraudio = new Audio();
	m_erroraudio->LoadFromFile("Sound/Error.wav");


	// Initialize the UI (This took so long)
	m_BackSelected_texture = new GameObject(m_renderer, "Images/BackSelected.png", Vector2D(500, 400));
	m_BackNotSelected_texture = new GameObject(m_renderer, "Images/BackNotSelected.png", Vector2D(500, 400));


	m_ContinueSelected_texture = new GameObject(m_renderer, "Images/continueselected.png", Vector2D(100, 400));
	m_ContinueNotSelected_texture = new GameObject(m_renderer, "Images/continuenotselected.png", Vector2D(100, 400));

	m_HealthUpgrade1Selected_texture = new GameObject(m_renderer, "Images/Health1Selected.png",
	                                                  Vector2D(100, 300));
	m_HealthUpgrade1NotSelected_texture = new GameObject(m_renderer, "Images/Health1NotSelected.png",
	                                                     Vector2D(100, 300));
	m_HealthUpgrade1Bought_texture = new GameObject(m_renderer, "Images/Health1Bought.png", Vector2D(100, 300));

	m_HealthUpgrade2Selected_texture = new GameObject(m_renderer, "Images/Health2Selected.png",
	                                                  Vector2D(100, 200));
	m_HealthUpgrade2NotSelected_texture = new GameObject(m_renderer, "Images/Health2NotSelected.png",
	                                                     Vector2D(100, 200));
	m_HealthUpgrade2Bought_texture = new GameObject(m_renderer, "Images/Health2Bought.png", Vector2D(100, 200));

	m_HealthUpgrade3Selected_texture = new
		GameObject(m_renderer, "Images/Health3Selected.png", Vector2D(100, 150));
	m_HealthUpgrade3NotSelected_texture = new GameObject(m_renderer, "Images/Health3NotSelected.png",
	                                                     Vector2D(100, 150));
	m_HealthUpgrade3Bought_texture = new GameObject(m_renderer, "Images/Health3Bought.png", Vector2D(100, 150));

	m_BaseHealthUpgrade1Selected_texture = new GameObject(m_renderer, "Images/Health1Selected.png",
	                                                      Vector2D(500, 300));
	m_BaseHealthUpgrade1NotSelected_texture = new GameObject(m_renderer, "Images/Health1NotSelected.png",
	                                                         Vector2D(500, 300));
	m_BaseHealthUpgrade1Bought_texture = new GameObject(m_renderer, "Images/Health1Bought.png",
	                                                    Vector2D(500, 300));

	m_BaseHealthUpgrade2Selected_texture = new GameObject(m_renderer, "Images/Health2Selected.png",
	                                                      Vector2D(500, 200));
	m_BaseHealthUpgrade2NotSelected_texture = new GameObject(m_renderer, "Images/Health2NotSelected.png",
	                                                         Vector2D(500, 200));
	m_BaseHealthUpgrade2Bought_texture = new GameObject(m_renderer, "Images/Health2Bought.png",
	                                                    Vector2D(500, 200));

	m_BaseHealthUpgrade3Selected_texture = new GameObject(m_renderer, "Images/Health3Selected.png",
	                                                      Vector2D(500, 150));
	m_BaseHealthUpgrade3NotSelected_texture = new GameObject(m_renderer, "Images/Health3NotSelected.png",
	                                                         Vector2D(500, 150));
	m_BaseHealthUpgrade3Bought_texture = new GameObject(m_renderer, "Images/Health3Bought.png",
	                                                    Vector2D(500, 150));


	m_scoreIcon = new GameObject(m_renderer, "Images/Score.png", Vector2D(300, 30));

	// Initialize the text (not used)
	m_scoreText = new GameText(m_renderer, "fonts/arial.ttf", 24);

	// Load the background texture
	if (!m_background_texture->LoadFromFile("Images/Upgrades.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	return true;
}
