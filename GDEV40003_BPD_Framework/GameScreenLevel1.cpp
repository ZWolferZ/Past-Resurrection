// ----------------------------- INCLUDE ----------------------------- //
#include "GameScreenLevel1.h"
// ----------------------------- INCLUDE ----------------------------- //


//  Gameobject initlisations (Not in header file to get timers to work)
GameObject* m_swap0 = nullptr;
GameObject* m_swap1 = nullptr;
GameObject* m_swap2 = nullptr;
GameObject* m_swap3 = nullptr;
GameObject* m_swap4 = nullptr;
Character* my_character = nullptr;
Crosshair* m_crosshair = nullptr;
EnemyFlyers* m_enemy[4];
EnemyGround* m_enemyGround[6];

//  Gamestate initalisations (Not in header file to get timers to work)
bool v_leftScreen = true;
int v_bullets = 6;
bool v_reload = false;
bool v_inlevel = false;
bool v_bulletCooldown = false;
bool v_towerCooldown = false;
bool v_gunSwapCooldown = false;
bool v_normalGun = true;
bool v_shotgun = false;
bool v_shotgunGet = false;
bool v_screenMovingLeft = false;
bool v_screenMovingRight = false;
bool v_dontRender = false;
bool v_skyboxRender = false;
bool v_shotgunGetToggle = false;
float v_backgroundX = 0.0f;
float v_backgroundY = 0.0f;
int v_playerHealth = 100;
int v_baseHealth = 100;


// Level 1 initlisation by parsing the renderer
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	m_background_texture = nullptr;

	// I am terrified of the segmentation fault, so I set all pointers to nullptr
	for (auto& i : m_bullet)
	{
		i = nullptr;
	}

	for (auto& i : m_bulletCounter)
	{
		i = nullptr;
	}

	for (auto& i : m_enemy)
	{
		i = nullptr;
	}

	for (auto& i : m_enemyGround)
	{
		i = nullptr;
	}

	SetUpLevel();
}

// Reload the bullets after 2 seconds
void GameScreenLevel1::Reload()
{
	// Reload the bullets, so the player can shoot again
	std::cout << "Reloading" << '\n';
	v_reload = true;

	// First time I used a timer so the syntax is weird as I was learning how to use it
	SDL_TimerCallback reloadCooldown = [](Uint32 interval, void* param) -> Uint32
	{
		v_bullets = 6;
		v_reload = false;
		return 0;
	};


	SDL_AddTimer(2000, reloadCooldown, this);
}

// Delete all of the game objects in the scene
GameScreenLevel1::~GameScreenLevel1()
{
	if (m_background_texture != nullptr)
	{
		delete m_background_texture;
		m_background_texture = nullptr;
	}

	if (m_shotgun_get != nullptr)
	{
		delete m_shotgun_get;
		m_shotgun_get = nullptr;
	}

	if (m_skybox != nullptr)
	{
		delete m_skybox;
		m_skybox = nullptr;
	}
	if (my_character != nullptr)
	{
		delete my_character;
		my_character = nullptr;
	}
	if (m_crosshair != nullptr)
	{
		delete m_crosshair;
		m_crosshair = nullptr;
	}

	for (auto bullet : m_bullet)
	{
		if (bullet != nullptr)
		{
			delete bullet;
			bullet = nullptr;
		}
	}

	for (auto enemyground : m_enemyGround)
	{
		if (enemyground != nullptr)
		{
			delete enemyground;
			enemyground = nullptr;
		}
	}

	for (auto bulletcount : m_bulletCounter)
	{
		if (bulletcount != nullptr)
		{
			delete bulletcount;
			bulletcount = nullptr;
		}
	}
	if (m_swap0 != nullptr)
	{
		delete m_swap0;
		m_swap0 = nullptr;
	}
	if (m_swap1 != nullptr)
	{
		delete m_swap1;
		m_swap1 = nullptr;
	}
	if (m_swap2 != nullptr)
	{
		delete m_swap2;
		m_swap2 = nullptr;
	}
	if (m_swap3 != nullptr)
	{
		delete m_swap3;
		m_swap3 = nullptr;
	}
	if (m_swap4 != nullptr)
	{
		delete m_swap4;
		m_swap4 = nullptr;
	}
	if (m_normalGunIcon)
	{
		delete m_normalGunIcon;
		m_normalGunIcon = nullptr;
	}
	if (m_shotgunIcon)
	{
		delete m_shotgunIcon;
		m_shotgunIcon = nullptr;
	}
	if (m_scoreIcon)
	{
		delete m_scoreIcon;
		m_scoreIcon = nullptr;
	}
	if (m_scoreText != nullptr)
	{
		delete m_scoreText;
		m_scoreText = nullptr;
	}
	for (auto enemy : m_enemy)
	{
		if (enemy != nullptr)
		{
			delete enemy;
			enemy = nullptr;
		}
	}
}

// Render all of the game objects in the scene
void GameScreenLevel1::Render()
{
	if (v_skyboxRender)
	{
		m_skybox->Render();
	}


	m_background_texture->Render(Vector2D(v_backgroundX, v_backgroundY), SDL_FLIP_NONE, 0.0);


	// Shotgun Icon renders for a breif moment after the score reaches 100
	if (g_score >= 100 && !v_shotgunGetToggle)
	{
		if (m_shotgun_get != nullptr)
		{
			m_shotgun_get->Render();
		}

		v_shotgunGet = true;
		SDL_AddTimer(1500, [](Uint32 interval, void* param) -> Uint32
		{
			v_shotgunGetToggle = true;
			return 0;
		}, this);
	}

	// The don't render variable was in place for a game mechanic that was never implemented, use "1" and "0" if you want to see what it does
	if (!v_dontRender)
	{
		// Render enemy-flyers
		for (auto enemy : m_enemy)
		{
			if (enemy != nullptr)
			{
				enemy->Render();
			}
		}


		// Render enemy-ground
		for (auto enemyGround : m_enemyGround)
		{
			if (enemyGround != nullptr)
			{
				enemyGround->Render();
			}
		}

		m_timeIcon->Render();
		m_playerHealthIcon->Render();
		m_baseHealthIcon->Render();

		// Render bullets, if they exist
		for (auto& i : m_bullet)
		{
			if (i != nullptr)
			{
				i->Render();
			}
		}


		my_character->Render();
		m_normalGunIcon->Render();

		// Switch statement for the bullet counter, pretty simple but it works pretty dam well
		switch (v_bullets)
		{
		case 0:

			m_bulletCounter[0]->Render();

			break;

		case 1:

			m_bulletCounter[1]->Render();
			break;
		case 2:

			m_bulletCounter[2]->Render();
			break;

		case 3:

			m_bulletCounter[3]->Render();
			break;
		case 4:

			m_bulletCounter[4]->Render();
			break;
		case 5:

			m_bulletCounter[5]->Render();
			break;
		case 6:
			m_bulletCounter[6]->Render();
			break;
		default: break ;
		}
		m_shotgunIcon->Render();
		m_scoreIcon->Render();
		m_crosshair->Render();


		// Text rendering for the score, timer, player health and base health
		m_scoreText->SetColor(SDL_Color{255, 255, 0, 255});
		m_scoreText->RenderAt(std::to_string(g_score), 450, 10);
		m_timerText->SetColor(SDL_Color{255, 255, 0, 255});
		m_timerText->RenderAt(std::to_string(m_timer), 440, 40);
		m_playerHealthText->SetColor(SDL_Color{255, 255, 0, 255});
		m_playerHealthText->RenderAt(std::to_string(v_playerHealth), 445, 65);
		m_baseHealthText->SetColor(SDL_Color{255, 255, 0, 255});
		m_baseHealthText->RenderAt(std::to_string(v_baseHealth), 440, 95);

		m_swap0->Render();
		m_swap1->Render();
		m_swap2->Render();
		m_swap3->Render();
		m_swap4->Render();

		// Cross-hair to Character Line
		// If the shotgun is equipped, the line will be yellow, otherwise it will be red
		if (v_shotgun)
		{
			SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawLine(m_renderer, my_character->GetPosition().x + 15, my_character->GetPosition().y + 20,
			                   m_crosshair->GetPosition().x + 25, m_crosshair->GetPosition().y + 25);
		}
		else
		{
			SDL_SetRenderDrawColor(m_renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawLine(m_renderer, my_character->GetPosition().x + 15, my_character->GetPosition().y + 20,
			                   m_crosshair->GetPosition().x + 25, m_crosshair->GetPosition().y + 25);
		}
	}
}

// Update all of the game objects in the scene
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	// Reduce the timer ever tick
	m_timer--;

	// Set a global variable to true if the timer reaches 0
	if (m_timer <= 0)
	{
		g_levelComplete = true;
	}

	// Set the game over variable to true if the player or the base health reaches 0
	if (v_playerHealth <= 0 || v_baseHealth <= 0)
	{
		g_gameOver = true;
	}


	my_character->Update(deltaTime, e);
	m_crosshair->Update(deltaTime, e);

	// Mechanic that never got fully implemented, but it kind of works
	if (v_screenMovingLeft || v_screenMovingRight)
	{
		v_skyboxRender = true;
	}
	if (v_screenMovingLeft && !v_screenMovingRight)
	{
		v_dontRender = true;
		v_backgroundX += 5.0f;
	}
	if (!v_screenMovingLeft && v_screenMovingRight)
	{
		v_dontRender = true;
		v_backgroundX -= 5.0f;
	}
	if (v_backgroundX < -1)
	{
		v_dontRender = true;
		v_backgroundX += 3.0f;
	}
	if (v_backgroundX > 1)
	{
		v_dontRender = true;
		v_backgroundX -= 3.0f;
	}
	if (v_backgroundX >= 200)
	{
		v_backgroundX = 200;
	}
	if (v_backgroundX <= -200)
	{
		v_backgroundX = -200;
	}
	if (v_backgroundX >= -1.0f && v_backgroundX <= 1.0f)
	{
		v_dontRender = false;
	}

	// Bullet logic
	// Move the bullet if it exists, otherwise if it reaches the void, delete it
	for (auto& i : m_bullet)
	{
		if (i != nullptr)
		{
			i->Update(deltaTime, e);

			if (i->GetPosition().x == theVoid && i->GetPosition().y == theVoid)
			{
				delete i;
				i = nullptr;
			}
		}
	}

	// Enemy logic
	// if the enemy is not null, update it and move it towards the middle of the screen
	for (auto enemyGround : m_enemyGround)
	{
		if (enemyGround != nullptr)
		{
			enemyGround->Update(deltaTime, e);

			if (enemyGround->GetPosition().x <= baselocation)
			{
				enemyGround->MoveRight(deltaTime);
			}
			else if (enemyGround->GetPosition().x >= baselocation)
			{
				enemyGround->MoveLeft(deltaTime);
			}
		}
	}

	// If the enemy is within range of the base, move it back to the start and reduce the base health
	// Never used the "fabs" function before to be honest, but I was having trouble with measuring exact floating point numbers,
	// so I used this to get the absolute value of the float

	if (fabs(m_enemyGround[0]->GetPosition().x - baselocation) < v_range)
	{
		// Move the enemy back (Object Pooling)
		m_enemyGround[0]->SetPosition(Vector2D(-100, 430));

		// Play the sound effect
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);

		// Reduce the base health
		v_baseHealth -= 25;
		std::cout << v_baseHealth << std::endl;
	}

	if (fabs(m_enemyGround[1]->GetPosition().x - baselocation) < v_range)
	{
		m_enemyGround[1]->SetPosition(Vector2D(-200, 430));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_baseHealth -= 25;
		std::cout << v_baseHealth << std::endl;
	}


	if (fabs(m_enemyGround[2]->GetPosition().x - baselocation) < v_range)
	{
		m_enemyGround[2]->SetPosition(Vector2D(-300, 430));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_baseHealth -= 25;
		std::cout << v_baseHealth << std::endl;
	}


	if (fabs(m_enemyGround[3]->GetPosition().x - baselocation) < v_range)
	{
		m_enemyGround[3]->SetPosition(Vector2D(825, 430));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_baseHealth -= 25;
		std::cout << v_baseHealth << std::endl;
	}


	if (fabs(m_enemyGround[4]->GetPosition().x - baselocation) < v_range)
	{
		m_enemyGround[4]->SetPosition(Vector2D(925, 430));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_baseHealth -= 25;
		std::cout << v_baseHealth << std::endl;
	}


	if (fabs(m_enemyGround[5]->GetPosition().x - baselocation) < v_range)
	{
		m_enemyGround[5]->SetPosition(Vector2D(1025, 430));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_baseHealth -= 25;
		std::cout << v_baseHealth << std::endl;
	}


	// Flying Enemy logic
	// If the enemy is not null, update it and move it towards the player
	for (auto enemy : m_enemy)
	{
		if (enemy != nullptr)

			enemy->Update(deltaTime, e);
		{
			if (enemy->GetPosition().x <= my_character->GetPosition().x)
			{
				enemy->MoveRight(deltaTime);
			}
			else if (enemy->GetPosition().x >= my_character->GetPosition().x)
			{
				enemy->MoveLeft(deltaTime);
			}
			if (enemy->GetPosition().y <= my_character->GetPosition().y)
			{
				enemy->SetPosition(Vector2D(enemy->GetPosition().x, enemy->GetPosition().y + 1));
			}
			else if (enemy->GetPosition().y >= my_character->GetPosition().y)
			{
				enemy->SetPosition(Vector2D(enemy->GetPosition().x, enemy->GetPosition().y - 1));
			}
		}
	}

	// If the enemy collides with the player, move it back to the start and reduce the player health
	if (Collisions::Instance()->Box(my_character->GetCollisionBox(), m_enemy[0]->GetCollisionBox()))
	{
		// Move the enemy back (Object Pooling)
		m_enemy[0]->SetPosition(Vector2D(-40, 270));

		// Play the sound effect
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);

		// Reduce the player health
		v_playerHealth -= 25;
		std::cout << v_playerHealth << std::endl;
	}

	if (Collisions::Instance()->Box(my_character->GetCollisionBox(), m_enemy[1]->GetCollisionBox()))
	{
		m_enemy[1]->SetPosition(Vector2D(-350, 270));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_playerHealth -= 25;
		std::cout << v_playerHealth << std::endl;
	}

	if (Collisions::Instance()->Box(my_character->GetCollisionBox(), m_enemy[2]->GetCollisionBox()))
	{
		m_enemy[2]->SetPosition(Vector2D(850, 270));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_playerHealth -= 25;
		std::cout << v_playerHealth << std::endl;
	}

	if (Collisions::Instance()->Box(my_character->GetCollisionBox(), m_enemy[3]->GetCollisionBox()))
	{
		m_enemy[3]->SetPosition(Vector2D(1200, 270));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_playerHealth -= 25;
		std::cout << v_playerHealth << std::endl;
	}

	// Bullet Collision Logic
	for (auto& i : m_bullet)
	{
		if (i != nullptr)
		{
			// If the bullet collides with the enemy, move the enemy back to the start and increase the score
			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemy[0]->GetCollisionBox()) && m_enemy[0]->
				ReturnHit() == false)
			{
				// Play enemy animation
				m_enemy[0]->SetHitTrue();

				// Increase the score
				g_score += 10;

				// Play the sound effect
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);

				// Let the enemy play their death animation and then send them back to their start position
				SDL_AddTimer(800, [](Uint32 interval, void* param) -> Uint32
				{
					m_enemy[0]->SetPosition(Vector2D(-40, 270));
					return 0;
				}, this);
			}

			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemy[1]->GetCollisionBox()) && m_enemy[1]->
				ReturnHit() == false)
			{
				m_enemy[1]->SetHitTrue();
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				SDL_AddTimer(800, [](Uint32 interval, void* param) -> Uint32
				{
					m_enemy[1]->SetPosition(Vector2D(-350, 270));
					return 0;
				}, this);
			}

			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemy[2]->GetCollisionBox()) && m_enemy[2]->
				ReturnHit() == false)
			{
				m_enemy[2]->SetHitTrue();
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				SDL_AddTimer(800, [](Uint32 interval, void* param) -> Uint32
				{
					m_enemy[2]->SetPosition(Vector2D(850, 270));
					return 0;
				}, this);
			}

			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemy[3]->GetCollisionBox()) && m_enemy[3]->
				ReturnHit() == false)
			{
				m_enemy[3]->SetHitTrue();
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				SDL_AddTimer(800, [](Uint32 interval, void* param) -> Uint32
				{
					m_enemy[3]->SetPosition(Vector2D(1200, 270));
					return 0;
				}, this);
			}

			// If the bullet collides with the enemy, move the enemy back to the start and increase the score
			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround[0]->GetCollisionBox()))
			{
				// Increase the score
				g_score += 10;

				// Play the sound effect
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);

				// Move the ground enemies back to their start position instantly as they lack a death animation
				m_enemyGround[0]->SetPosition(Vector2D(-100, 430));
			}

			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround[1]->GetCollisionBox()))
			{
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				m_enemyGround[1]->SetPosition(Vector2D(-200, 430));
			}
			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround[2]->GetCollisionBox()))
			{
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				m_enemyGround[2]->SetPosition(Vector2D(-300, 430));
			}
			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround[3]->GetCollisionBox()))
			{
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				m_enemyGround[3]->SetPosition(Vector2D(825, 430));
			}

			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround[4]->GetCollisionBox()))
			{
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				m_enemyGround[4]->SetPosition(Vector2D(925, 430));
			}
			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround[5]->GetCollisionBox()))
			{
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				m_enemyGround[5]->SetPosition(Vector2D(1025, 430));
			}
		}
	}


	m_swap0->Update(deltaTime, e);
	m_swap1->Update(deltaTime, e);
	m_swap2->Update(deltaTime, e);
	m_swap3->Update(deltaTime, e);
	m_swap4->Update(deltaTime, e);

	// Keep the crosshair to the side of the screen that the character is on
	if (m_crosshair->GetPosition().x >= static_cast<float>(SCREEN_WIDTH) / 2 && v_leftScreen)
	{
		m_crosshair->SetPosition(Vector2D(m_crosshair->GetPosition().x - 5, m_crosshair->GetPosition().y));
	}
	if (m_crosshair->GetPosition().x <= static_cast<float>(SCREEN_WIDTH) / 2 && !v_leftScreen)
	{
		m_crosshair->SetPosition(Vector2D(m_crosshair->GetPosition().x + 5, m_crosshair->GetPosition().y));
	}


	// Keep the character on a tower
	if (my_character->GetPosition().x <= leftTowerLeftSide && v_leftScreen)
	{
		my_character->SetPosition(Vector2D(my_character->GetPosition().x + 2, my_character->GetPosition().y));
	}

	if (my_character->GetPosition().x >= leftTowerRightSide && v_leftScreen)
	{
		my_character->SetPosition(Vector2D(my_character->GetPosition().x - 2, my_character->GetPosition().y));
	}

	if (my_character->GetPosition().x >= rightTowerRightSide && !v_leftScreen)
	{
		my_character->SetPosition(Vector2D(my_character->GetPosition().x - 2, my_character->GetPosition().y));
	}

	if (my_character->GetPosition().x <= rightTowerLeftSide && !v_leftScreen)
	{
		my_character->SetPosition(Vector2D(my_character->GetPosition().x + 2, my_character->GetPosition().y));
	}

	// Check for keyboard input
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_o: // Change Tower Position to the left
			if (!v_leftScreen && !v_towerCooldown)
			{
				v_towerCooldown = true;
				MoveTowerLeft();
			}
			break;

		case SDLK_p: // Change Tower Position to the right
			if (v_leftScreen && !v_towerCooldown)
			{
				v_towerCooldown = true;
				MoveTowerRight();
			}
			break;

		case SDLK_1: // Mechanic not implemented

			v_screenMovingLeft = true;
			v_screenMovingRight = false;
			break;

		case SDLK_0: // Mechanic not implemented
			v_screenMovingLeft = false;
			v_screenMovingRight = true;
			break;

		case SDLK_e: // Change shotgun to normal gun
			if (v_shotgun && !v_gunSwapCooldown)
			{
				v_gunSwapCooldown = true;
				v_normalGun = true;
				v_shotgun = false;

				// Swap the gun icons, this was before I realised I could just stop rendering them, so instead I send them to the void
				m_normalGunIcon->SetPosition(Vector2D(375, 350));
				m_shotgunIcon->SetPosition(Vector2D(theVoid, theVoid));

				// Play the sound effect
				m_gunswapaudio->Play(1, m_gunswapaudio->m_chunk, 1);

				// Set a timer so the player can't swap guns too quickly
				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_gunSwapCooldown = false;
					return 0;
				}, this);
			}
			else if (v_normalGun && !v_gunSwapCooldown && v_shotgunGet) // Change normal gun to shotgun
			{
				v_gunSwapCooldown = true;
				v_normalGun = false;
				v_shotgun = true;

				m_normalGunIcon->SetPosition(Vector2D(theVoid, theVoid));
				m_shotgunIcon->SetPosition(Vector2D(375, 350));

				m_gunswapaudio->Play(1, m_gunswapaudio->m_chunk, 1);

				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_gunSwapCooldown = false;
					return 0;
				}, this);
			}

			break;
		case SDLK_RETURN: // Fire Bullets

			// Determine if the player can fire a bullet, if they can, fire it depending on the gun they have

			// Normal Gun
			if (v_bullets > 0 && v_inlevel && !v_bulletCooldown && v_normalGun)
			{
				v_bulletCooldown = true;

				// Create a bullet object based on the player and crosshair position and the number of bullets
				m_bullet[v_bullets] = new Bullet(m_renderer, "Images/Bullet.png",
				                                 Vector2D(my_character->GetPosition().x + 10,
				                                          my_character->GetPosition().y),
				                                 Vector2D(m_crosshair->GetPosition().x + 10,
				                                          m_crosshair->GetPosition().y + 10));


				// Play the sound effect
				m_bulletaudio->Play(1, m_bulletaudio->m_chunk, 0);

				// Reduce the number of bullets in the gun
				v_bullets--;

				// Set a timer so the player can't fire too quickly
				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_bulletCooldown = false;
					return 0;
				}, this);
			}
			// Shotgun
			else if (v_bullets >= 3 && v_inlevel && !v_bulletCooldown && v_shotgun && v_shotgunGet)
			{
				v_bulletCooldown = true;

				// Create 3 bullets based on the player and crosshair position and the number of bullets
				m_bullet[v_bullets] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                 Vector2D(my_character->GetPosition().x + 10,
				                                          my_character->GetPosition().y),
				                                 Vector2D(m_crosshair->GetPosition().x + 10,
				                                          m_crosshair->GetPosition().y + 10));
				v_bullets--;
				m_bullet[v_bullets] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                 Vector2D(my_character->GetPosition().x + 10,
				                                          my_character->GetPosition().y),
				                                 Vector2D(m_crosshair->GetPosition().x + 10,
				                                          m_crosshair->GetPosition().y + 40));
				v_bullets--;
				m_bullet[v_bullets] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                 Vector2D(my_character->GetPosition().x + 10,
				                                          my_character->GetPosition().y),
				                                 Vector2D(m_crosshair->GetPosition().x + 10,
				                                          m_crosshair->GetPosition().y + -40));

				v_bullets--;

				m_shotgunaudio->Play(1, m_shotgunaudio->m_chunk, 0);


				SDL_AddTimer(400, [](Uint32 interval, void* param) -> Uint32
				{
					v_bulletCooldown = false;
					return 0;
				}, this);
			}
		// Reload the gun if the player is out of bullets
			if (v_bullets <= 0 && v_normalGun && v_reload == false)
			{
				m_reloadaudio->Play(2, m_reloadaudio->m_chunk, 0);
				Reload();
			}
			// If the shotgun is equipped and there is not enough bullets to fire it, reload the gun
			else if (v_bullets < 3 && v_shotgun && v_reload == false)
			{
				m_reloadaudio->Play(2, m_reloadaudio->m_chunk, 0);
				Reload();
			}


			break;

		default: ;
		}
	}

	if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_1:
			v_screenMovingLeft = false;
			break;

		case SDLK_0:
			v_screenMovingRight = false;
			break;

		default: ;
		}
	}
	// Check for controller input
	if (e.type == SDL_JOYBUTTONUP)
	{
		switch (e.jbutton.button)
		{
		case 8:
			v_screenMovingLeft = false;
			break;

		case 6:
			v_screenMovingRight = false;
			break;

		default: ;
		}
	}

	if (e.type == SDL_JOYBUTTONDOWN)
	{
		switch (e.jbutton.button)
		{
		case 5:
			if (!v_leftScreen && !v_towerCooldown)
			{
				v_towerCooldown = true;
				MoveTowerLeft();
			}


			break;
		case 1:
			if (v_leftScreen && !v_towerCooldown)
			{
				v_towerCooldown = true;
				MoveTowerRight();
			}
			break;

		case 2:
			if (v_shotgun && !v_gunSwapCooldown)
			{
				v_gunSwapCooldown = true;
				v_normalGun = true;
				v_shotgun = false;
				m_normalGunIcon->SetPosition(Vector2D(375, 350));
				m_shotgunIcon->SetPosition(Vector2D(theVoid, theVoid));
				m_gunswapaudio->Play(1, m_gunswapaudio->m_chunk, 1);
				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_gunSwapCooldown = false;
					return 0;
				}, this);
			}
			else if (v_normalGun && !v_gunSwapCooldown && v_shotgunGet)
			{
				v_gunSwapCooldown = true;
				v_normalGun = false;
				v_shotgun = true;
				m_normalGunIcon->SetPosition(Vector2D(theVoid, theVoid));
				m_shotgunIcon->SetPosition(Vector2D(375, 350));
				m_gunswapaudio->Play(1, m_gunswapaudio->m_chunk, 1);
				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_gunSwapCooldown = false;
					return 0;
				}, this);
			}

			break;

		case 9:


			if (v_bullets > 0 && v_inlevel && !v_bulletCooldown && v_normalGun)
			{
				v_bulletCooldown = true;
				m_bullet[v_bullets] = new Bullet(m_renderer, "Images/Bullet.png",
				                                 Vector2D(my_character->GetPosition().x + 10,
				                                          my_character->GetPosition().y),
				                                 Vector2D(m_crosshair->GetPosition().x + 10,
				                                          m_crosshair->GetPosition().y + 10));


				m_shotgunaudio->Play(1, m_shotgunaudio->m_chunk, 0);

				v_bullets--;


				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_bulletCooldown = false;
					return 0;
				}, this);
			}
			else if (v_bullets >= 3 && v_inlevel && !v_bulletCooldown && v_shotgun && v_shotgunGet)
			{
				v_bulletCooldown = true;
				m_bullet[v_bullets] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                 Vector2D(my_character->GetPosition().x + 10,
				                                          my_character->GetPosition().y),
				                                 Vector2D(m_crosshair->GetPosition().x + 10,
				                                          m_crosshair->GetPosition().y + 10));
				v_bullets--;
				m_bullet[v_bullets] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                 Vector2D(my_character->GetPosition().x + 10,
				                                          my_character->GetPosition().y),
				                                 Vector2D(m_crosshair->GetPosition().x + 10,
				                                          m_crosshair->GetPosition().y + 40));
				v_bullets--;
				m_bullet[v_bullets] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                 Vector2D(my_character->GetPosition().x + 10,
				                                          my_character->GetPosition().y),
				                                 Vector2D(m_crosshair->GetPosition().x + 10,
				                                          m_crosshair->GetPosition().y + -40));

				m_shotgunaudio->Play(1, m_shotgunaudio->m_chunk, 0);

				v_bullets--;

				SDL_AddTimer(400, [](Uint32 interval, void* param) -> Uint32
				{
					v_bulletCooldown = false;
					return 0;
				}, this);
			}
			if (v_bullets <= 0 && v_normalGun && v_reload == false)
			{
				m_reloadaudio->Play(2, m_reloadaudio->m_chunk, 0);
				Reload();
			}
			else if (v_bullets < 3 && v_shotgun && v_reload == false)
			{
				m_reloadaudio->Play(2, m_reloadaudio->m_chunk, 0);
				Reload();
			}


			break;

		default: ;
		}
	}

	// After one update pass, you are in the level
	v_inlevel = true;
}


// Set up the level by initlising all of the game objects and local bools
bool GameScreenLevel1::SetUpLevel()
{
	// Set the health's to their max values, incase of upgrades
	v_playerHealth = g_maxplayerHealth;
	v_baseHealth = g_maxbaseHealth;

	// Reset varibles
	g_score = 0;
	v_inlevel = false;
	g_levelComplete = false;
	v_leftScreen = true;
	v_bullets = 6;
	v_reload = false;
	v_shotgunGet = false;
	v_shotgunGetToggle = false;
	v_bulletCooldown = false;
	v_towerCooldown = false;
	v_gunSwapCooldown = false;
	v_normalGun = true;
	v_shotgun = false;
	v_screenMovingLeft = false;
	v_screenMovingRight = false;
	v_dontRender = false;
	v_skyboxRender = false;
	v_backgroundX = 0.0f;
	v_backgroundY = 0.0f;

	// Set the background texture
	m_background_texture = new Texture2D(m_renderer);
	m_skybox = new GameObject(m_renderer, "Images/Skybox1.png", Vector2D(0, 0));

	//Set up the crosshair and character
	// I Love SteamMan
	my_character = new Character(m_renderer, "Images/Character/SteamMan.png", Vector2D(247, 246));
	m_crosshair = new Crosshair(m_renderer, "Images/Crosshair.png", Vector2D(100, 350));

	// Initilise the tower swap bar
	// I forgot about the use of an array here, so this is not pretty
	m_swap0 = new GameObject(m_renderer, "Images/Swap0.png", Vector2D(theVoid, theVoid));
	m_swap1 = new GameObject(m_renderer, "Images/Swap1.png", Vector2D(theVoid, theVoid));
	m_swap2 = new GameObject(m_renderer, "Images/Swap2.png", Vector2D(theVoid, theVoid));
	m_swap3 = new GameObject(m_renderer, "Images/Swap3.png", Vector2D(theVoid, theVoid));
	m_swap4 = new GameObject(m_renderer, "Images/Swap4.png", Vector2D(theVoid, theVoid));

	// Initilise the bullet counter
	m_bulletCounter[0] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount0.png", Vector2D(240, 10));
	m_bulletCounter[1] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount1.png", Vector2D(240, 10));
	m_bulletCounter[2] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount2.png", Vector2D(240, 10));
	m_bulletCounter[3] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount3.png", Vector2D(240, 10));
	m_bulletCounter[4] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount4.png", Vector2D(240, 10));
	m_bulletCounter[5] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount5.png", Vector2D(240, 10));
	m_bulletCounter[6] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount6.png", Vector2D(240, 10));

	// Initilise the icons
	m_shotgun_get = new GameObject(m_renderer, "Images/ShotGunGet.png", Vector2D(300, 150));
	m_timeIcon = new GameObject(m_renderer, "Images/Time Remaining.png", Vector2D(300, 30));
	m_normalGunIcon = new GameObject(m_renderer, "Images/NormalGun.png", Vector2D(375, 350));
	m_shotgunIcon = new GameObject(m_renderer, "Images/ShotGun.png", Vector2D(theVoid, theVoid));
	m_scoreIcon = new GameObject(m_renderer, "Images/Score.png", Vector2D(300, 10));
	m_playerHealthIcon = new GameObject(m_renderer, "Images/PlayerHealth.png", Vector2D(300, 60));
	m_baseHealthIcon = new GameObject(m_renderer, "Images/BaseHealth.png", Vector2D(300, 90));

	// Initilise the text 
	m_scoreText = new GameText(m_renderer, "fonts/arial.ttf", 24);
	m_timerText = new GameText(m_renderer, "fonts/arial.ttf", 20);
	m_playerHealthText = new GameText(m_renderer, "fonts/arial.ttf", 20);
	m_baseHealthText = new GameText(m_renderer, "fonts/arial.ttf", 20);

	// Initilise the flying enemies
	m_enemy[0] = new EnemyFlyers(m_renderer, "Images/EnemyFlyers/1.png", Vector2D(-40, 270));
	m_enemy[1] = new EnemyFlyers(m_renderer, "Images/EnemyFlyers/1.png", Vector2D(-350, 270));
	m_enemy[2] = new EnemyFlyers(m_renderer, "Images/EnemyFlyers/1.png", Vector2D(850, 270));
	m_enemy[3] = new EnemyFlyers(m_renderer, "Images/EnemyFlyers/1.png", Vector2D(1200, 270));

	// Initilise the ground enemies
	m_enemyGround[0] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(-100, 430));
	m_enemyGround[1] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(-200, 430));
	m_enemyGround[2] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(-300, 430));
	m_enemyGround[3] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(825, 430));
	m_enemyGround[4] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(925, 430));
	m_enemyGround[5] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(1025, 430));

	// Initilise the audio systems
	m_enemyhurt = new Audio();
	m_enemyhurt->LoadFromFile("Sound/EnemyFlyers Hurt.wav");
	m_playerHurt = new Audio();
	m_playerHurt->LoadFromFile("Sound/PlayerHurt.wav");
	m_bulletaudio = new Audio();
	m_bulletaudio->LoadFromFile("Sound/Bullet.wav");
	m_reloadaudio = new Audio();
	m_reloadaudio->LoadFromFile("Sound/Reload.wav");
	m_swapaudio = new Audio();
	m_swapaudio->LoadFromFile("Sound/Swap.wav");
	m_gunswapaudio = new Audio();
	m_gunswapaudio->LoadFromFile("Sound/GunSwap.wav");
	m_shotgunaudio = new Audio();
	m_shotgunaudio->LoadFromFile("Sound/ShotgunSound.wav");


	// Load the background texture
	if (!m_background_texture->LoadFromFile("Images/Day Level.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	return true;
}


// These functions were kinda weird to implement, I was stuck on them for about a week and new I needed to implement a asynchronous timer,
// but every function I tried (Like SDL_Delay) would freeze the game.
// I eventually found "SDL_AddTimer" and after realising that I cant encapsulate member functions inside the timers for some reason, it worked pretty well.
void GameScreenLevel1::MoveTowerLeft()
{
	// Play the tower swap sound effect
	m_swapaudio->Play(1, m_swapaudio->m_chunk, 0);

	// Loading bar animations
	// I had to use a timer to move the loading bar along, and I could not encapsulate member functions inside the timer,
	// so they dont look pretty but it works
	m_swap0->SetPosition(Vector2D(250, 50));
	SDL_AddTimer(100, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character != nullptr)
		{
			m_swap0->SetPosition(Vector2D(theVoid, theVoid));
			m_swap1->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character != nullptr)
		{
			m_swap1->SetPosition(Vector2D(theVoid, theVoid));
			m_swap2->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character != nullptr)
		{
			m_swap2->SetPosition(Vector2D(theVoid, theVoid));
			m_swap3->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(400, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character != nullptr)
		{
			m_swap3->SetPosition(Vector2D(theVoid, theVoid));
			m_swap4->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(500, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character != nullptr)
		{
			m_swap4->SetPosition(Vector2D(theVoid, theVoid));
			my_character->SetPosition(Vector2D(247, 246));
			m_crosshair->SetPosition(Vector2D(100, 300));
			v_leftScreen = true;
			v_towerCooldown = false;
		}
		return 0;
	}, this);
}

void GameScreenLevel1::MoveTowerRight()
{
	m_swapaudio->Play(1, m_swapaudio->m_chunk, 0);
	m_swap0->SetPosition(Vector2D(250, 50));
	SDL_AddTimer(100, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character != nullptr)
		{
			m_swap0->SetPosition(Vector2D(theVoid, theVoid));
			m_swap1->SetPosition(Vector2D(250, 50));
		}

		return 0;
	}, this);

	SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character != nullptr)
		{
			m_swap1->SetPosition(Vector2D(theVoid, theVoid));
			m_swap2->SetPosition(Vector2D(250, 50));
		}

		return 0;
	}, this);

	SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character != nullptr)
		{
			m_swap2->SetPosition(Vector2D(theVoid, theVoid));
			m_swap3->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(400, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character != nullptr)
		{
			m_swap3->SetPosition(Vector2D(theVoid, theVoid));
			m_swap4->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(500, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character != nullptr)
		{
			m_swap4->SetPosition(Vector2D(theVoid, theVoid));
			my_character->SetPosition(Vector2D(526, 244));
			m_crosshair->SetPosition(Vector2D(662, 300));
			v_leftScreen = false;
			v_towerCooldown = false;
		}
		return 0;
	}, this);
}
