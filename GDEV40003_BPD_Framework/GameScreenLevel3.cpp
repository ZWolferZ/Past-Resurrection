// ----------------------------- INCLUDE ----------------------------- //
#include "GameScreenLevel3.h"
// ----------------------------- INCLUDE ----------------------------- //

// For Level Comments see GameScreenLevel1.cpp, this is the same but with different values and objects.

GameObject* m_swap0_3 = nullptr;
GameObject* m_swap1_3 = nullptr;
GameObject* m_swap2_3 = nullptr;
GameObject* m_swap3_3 = nullptr;
GameObject* m_swap4_3 = nullptr;
Character* my_character_3 = nullptr;
Crosshair* m_crosshair_3 = nullptr;
EnemyFlyers* m_enemy_3[4];
EnemyGround* m_enemyGround_3[6];


bool v_leftScreen_3 = true;
int v_bullets_3 = 6;
bool v_reload_3 = false;
bool v_inlevel_3 = false;
bool v_bulletCooldown_3 = false;
bool v_towerCooldown_3 = false;
bool v_gunSwapCooldown_3 = false;
bool v_normalGun_3 = true;
bool v_shotgun_3 = false;
bool v_shotgunGet_3 = false;
bool v_screenMovingLeft_3 = false;
bool v_screenMovingRight_3 = false;
bool v_dontRender_3 = false;
bool v_skyboxRender_3 = false;
bool v_shotgunGetToggle_3 = false;
float v_backgroundX_3 = 0.0f;
float v_backgroundY_3 = 0.0f;
int v_playerHealth_3 = 100;
int v_baseHealth_3 = 100;


GameScreenLevel3::GameScreenLevel3(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	m_background_texture = nullptr;

	for (auto& i : m_bullet)
	{
		i = nullptr;
	}

	for (auto& i : m_bulletCounter)
	{
		i = nullptr;
	}

	for (auto& i : m_enemy_3)
	{
		i = nullptr;
	}

	for (auto& i : m_enemyGround_3)
	{
		i = nullptr;
	}

	SetUpLevel();
}


void GameScreenLevel3::Reload()
{
	std::cout << "Reloading" << '\n';
	v_reload_3 = true;


	SDL_TimerCallback reloadCooldown = [](Uint32 interval, void* param) -> Uint32
	{
		v_bullets_3 = 6;
		v_reload_3 = false;
		return 0;
	};


	SDL_AddTimer(2000, reloadCooldown, this);
}


GameScreenLevel3::~GameScreenLevel3()
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
	if (my_character_3 != nullptr)
	{
		delete my_character_3;
		my_character_3 = nullptr;
	}
	if (m_crosshair_3 != nullptr)
	{
		delete m_crosshair_3;
		m_crosshair_3 = nullptr;
	}

	for (auto bullet : m_bullet)
	{
		if (bullet != nullptr)
		{
			delete bullet;
			bullet = nullptr;
		}
	}

	for (auto enemyground : m_enemyGround_3)
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
	if (m_swap0_3 != nullptr)
	{
		delete m_swap0_3;
		m_swap0_3 = nullptr;
	}
	if (m_swap1_3 != nullptr)
	{
		delete m_swap1_3;
		m_swap1_3 = nullptr;
	}
	if (m_swap2_3 != nullptr)
	{
		delete m_swap2_3;
		m_swap2_3 = nullptr;
	}
	if (m_swap3_3 != nullptr)
	{
		delete m_swap3_3;
		m_swap3_3 = nullptr;
	}
	if (m_swap4_3 != nullptr)
	{
		delete m_swap4_3;
		m_swap4_3 = nullptr;
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
	for (auto enemy : m_enemy_3)
	{
		if (enemy != nullptr)
		{
			delete enemy;
			enemy = nullptr;
		}
	}
}

void GameScreenLevel3::Render()
{
	if (v_skyboxRender_3)
	{
		m_skybox->Render();
	}


	m_background_texture->Render(Vector2D(v_backgroundX_3, v_backgroundY_3), SDL_FLIP_NONE, 0.0);


	if (g_score >= 100 && !v_shotgunGetToggle_3)
	{
		if (m_shotgun_get != nullptr)
		{
			m_shotgun_get->Render();
		}

		v_shotgunGet_3 = true;
		SDL_AddTimer(1500, [](Uint32 interval, void* param) -> Uint32
		{
			v_shotgunGetToggle_3 = true;
			return 0;
		}, this);
	}


	if (!v_dontRender_3)
	{
		for (auto enemy : m_enemy_3)
		{
			if (enemy != nullptr)
			{
				enemy->Render();
			}
		}

		for (auto enemyGround : m_enemyGround_3)
		{
			if (enemyGround != nullptr)
			{
				enemyGround->Render();
			}
		}

		m_timeIcon->Render();
		m_playerHealthIcon->Render();
		m_baseHealthIcon->Render();

		for (auto& i : m_bullet)
		{
			if (i != nullptr)
			{
				i->Render();
			}
		}


		my_character_3->Render();
		m_normalGunIcon->Render();

		switch (v_bullets_3)
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
		default: break;
		}
		m_shotgunIcon->Render();
		m_scoreIcon->Render();
		m_crosshair_3->Render();


		m_scoreText->SetColor(SDL_Color{255, 255, 0, 255});
		m_scoreText->RenderAt(std::to_string(g_score), 450, 10);
		m_timerText->SetColor(SDL_Color{255, 255, 0, 255});
		m_timerText->RenderAt(std::to_string(m_timer), 440, 40);
		m_playerHealthText->SetColor(SDL_Color{255, 255, 0, 255});
		m_playerHealthText->RenderAt(std::to_string(v_playerHealth_3), 445, 65);
		m_baseHealthText->SetColor(SDL_Color{255, 255, 0, 255});
		m_baseHealthText->RenderAt(std::to_string(v_baseHealth_3), 440, 95);

		m_swap0_3->Render();
		m_swap1_3->Render();
		m_swap2_3->Render();
		m_swap3_3->Render();
		m_swap4_3->Render();

		// Cross-hair to Character Line
		if (v_shotgun_3)
		{
			SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawLine(m_renderer, my_character_3->GetPosition().x + 15, my_character_3->GetPosition().y + 20,
			                   m_crosshair_3->GetPosition().x + 25, m_crosshair_3->GetPosition().y + 25);
		}
		else
		{
			SDL_SetRenderDrawColor(m_renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawLine(m_renderer, my_character_3->GetPosition().x + 15, my_character_3->GetPosition().y + 20,
			                   m_crosshair_3->GetPosition().x + 25, m_crosshair_3->GetPosition().y + 25);
		}
	}
}


void GameScreenLevel3::Update(float deltaTime, SDL_Event e)
{
	m_timer--;

	if (m_timer <= 0)
	{
		g_levelComplete = true;
	}

	if (v_playerHealth_3 <= 0 || v_baseHealth_3 <= 0)
	{
		g_gameOver = true;
	}

	if (v_screenMovingLeft_3 || v_screenMovingRight_3)
	{
		v_skyboxRender_3 = true;
	}


	my_character_3->Update(deltaTime, e);
	m_crosshair_3->Update(deltaTime, e);

	if (v_screenMovingLeft_3 && !v_screenMovingRight_3)
	{
		v_dontRender_3 = true;
		v_backgroundX_3 += 5.0f;
	}
	if (!v_screenMovingLeft_3 && v_screenMovingRight_3)
	{
		v_dontRender_3 = true;
		v_backgroundX_3 -= 5.0f;
	}
	if (v_backgroundX_3 < -1)
	{
		v_dontRender_3 = true;
		v_backgroundX_3 += 3.0f;
	}
	if (v_backgroundX_3 > 1)
	{
		v_dontRender_3 = true;
		v_backgroundX_3 -= 3.0f;
	}
	if (v_backgroundX_3 >= 200)
	{
		v_backgroundX_3 = 200;
	}
	if (v_backgroundX_3 <= -200)
	{
		v_backgroundX_3 = -200;
	}
	if (v_backgroundX_3 >= -1.0f && v_backgroundX_3 <= 1.0f)
	{
		v_dontRender_3 = false;
	}

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

	for (auto enemyGround : m_enemyGround_3)
	{
		if (enemyGround != nullptr)
		{
			enemyGround->Update(deltaTime, e);

			if (enemyGround->GetPosition().x <= 400)
			{
				enemyGround->MoveRight(deltaTime);
			}
			else if (enemyGround->GetPosition().x >= 400)
			{
				enemyGround->MoveLeft(deltaTime);
			}
		}
	}
	if (fabs(m_enemyGround_3[0]->GetPosition().x - 400.0f) < v_range)
	{
		m_enemyGround_3[0]->SetPosition(Vector2D(-100, 430));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_baseHealth_3 -= 25;
		std::cout << v_baseHealth_3 << std::endl;
	}

	if (fabs(m_enemyGround_3[1]->GetPosition().x - 400.0f) < v_range)
	{
		m_enemyGround_3[1]->SetPosition(Vector2D(-200, 430));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_baseHealth_3 -= 25;
		std::cout << v_baseHealth_3 << std::endl;
	}


	if (fabs(m_enemyGround_3[2]->GetPosition().x - 400.0f) < v_range)
	{
		m_enemyGround_3[2]->SetPosition(Vector2D(-300, 430));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_baseHealth_3 -= 25;
		std::cout << v_baseHealth_3 << std::endl;
	}


	if (fabs(m_enemyGround_3[3]->GetPosition().x - 400.0f) < v_range)
	{
		m_enemyGround_3[3]->SetPosition(Vector2D(825, 430));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_baseHealth_3 -= 25;
		std::cout << v_baseHealth_3 << std::endl;
	}


	if (fabs(m_enemyGround_3[4]->GetPosition().x - 400.0f) < v_range)
	{
		m_enemyGround_3[4]->SetPosition(Vector2D(925, 430));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_baseHealth_3 -= 25;
		std::cout << v_baseHealth_3 << std::endl;
	}


	if (fabs(m_enemyGround_3[5]->GetPosition().x - 400.0f) < v_range)
	{
		m_enemyGround_3[5]->SetPosition(Vector2D(1025, 430));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_baseHealth_3 -= 25;
		std::cout << v_baseHealth_3 << std::endl;
	}


	for (auto enemy : m_enemy_3)
	{
		if (enemy != nullptr)

			enemy->Update(deltaTime, e);
		{
			if (enemy->GetPosition().x <= my_character_3->GetPosition().x)
			{
				enemy->MoveRight(deltaTime);
			}
			else if (enemy->GetPosition().x >= my_character_3->GetPosition().x)
			{
				enemy->MoveLeft(deltaTime);
			}
			if (enemy->GetPosition().y <= my_character_3->GetPosition().y)
			{
				enemy->SetPosition(Vector2D(enemy->GetPosition().x, enemy->GetPosition().y + 1));
			}
			else if (enemy->GetPosition().y >= my_character_3->GetPosition().y)
			{
				enemy->SetPosition(Vector2D(enemy->GetPosition().x, enemy->GetPosition().y - 1));
			}
		}
	}


	if (Collisions::Instance()->Box(my_character_3->GetCollisionBox(), m_enemy_3[0]->GetCollisionBox()))
	{
		m_enemy_3[0]->SetPosition(Vector2D(-40, 270));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_playerHealth_3 -= 25;
		std::cout << v_playerHealth_3 << std::endl;
	}

	if (Collisions::Instance()->Box(my_character_3->GetCollisionBox(), m_enemy_3[1]->GetCollisionBox()))
	{
		m_enemy_3[1]->SetPosition(Vector2D(-350, 270));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_playerHealth_3 -= 25;
		std::cout << v_playerHealth_3 << std::endl;
	}

	if (Collisions::Instance()->Box(my_character_3->GetCollisionBox(), m_enemy_3[2]->GetCollisionBox()))
	{
		m_enemy_3[2]->SetPosition(Vector2D(850, 270));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_playerHealth_3 -= 25;
		std::cout << v_playerHealth_3 << std::endl;
	}

	if (Collisions::Instance()->Box(my_character_3->GetCollisionBox(), m_enemy_3[3]->GetCollisionBox()))
	{
		m_enemy_3[3]->SetPosition(Vector2D(1200, 270));
		m_playerHurt->Play(1, m_playerHurt->m_chunk, 0);
		v_playerHealth_3 -= 25;
		std::cout << v_playerHealth_3 << std::endl;
	}


	for (auto& i : m_bullet)
	{
		if (i != nullptr)
		{
			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemy_3[0]->GetCollisionBox()) && m_enemy_3[0]->
				ReturnHit() == false)
			{
				m_enemy_3[0]->SetHitTrue();
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				SDL_AddTimer(800, [](Uint32 interval, void* param) -> Uint32
				{
					m_enemy_3[0]->SetPosition(Vector2D(-40, 270));
					return 0;
				}, this);
			}

			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemy_3[1]->GetCollisionBox()) && m_enemy_3[1]->
				ReturnHit() == false)
			{
				m_enemy_3[1]->SetHitTrue();
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				SDL_AddTimer(800, [](Uint32 interval, void* param) -> Uint32
				{
					m_enemy_3[1]->SetPosition(Vector2D(-350, 270));
					return 0;
				}, this);
			}

			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemy_3[2]->GetCollisionBox()) && m_enemy_3[2]->
				ReturnHit() == false)
			{
				m_enemy_3[2]->SetHitTrue();
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				SDL_AddTimer(800, [](Uint32 interval, void* param) -> Uint32
				{
					m_enemy_3[2]->SetPosition(Vector2D(850, 270));
					return 0;
				}, this);
			}

			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemy_3[3]->GetCollisionBox()) && m_enemy_3[3]->
				ReturnHit() == false)
			{
				m_enemy_3[3]->SetHitTrue();
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				SDL_AddTimer(800, [](Uint32 interval, void* param) -> Uint32
				{
					m_enemy_3[3]->SetPosition(Vector2D(1200, 270));
					return 0;
				}, this);
			}

			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround_3[0]->GetCollisionBox()))
			{
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				m_enemyGround_3[0]->SetPosition(Vector2D(-100, 430));
			}

			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround_3[1]->GetCollisionBox()))
			{
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				m_enemyGround_3[1]->SetPosition(Vector2D(-200, 430));
			}
			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround_3[2]->GetCollisionBox()))
			{
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				m_enemyGround_3[2]->SetPosition(Vector2D(-300, 430));
			}
			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround_3[3]->GetCollisionBox()))
			{
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				m_enemyGround_3[3]->SetPosition(Vector2D(825, 430));
			}

			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround_3[4]->GetCollisionBox()))
			{
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				m_enemyGround_3[4]->SetPosition(Vector2D(925, 430));
			}
			if (Collisions::Instance()->Box(i->GetCollisionBox(), m_enemyGround_3[5]->GetCollisionBox()))
			{
				g_score += 10;
				m_enemyhurt->Play(1, m_enemyhurt->m_chunk, 0);
				m_enemyGround_3[5]->SetPosition(Vector2D(1025, 430));
			}
		}
	}


	m_swap0_3->Update(deltaTime, e);
	m_swap1_3->Update(deltaTime, e);
	m_swap2_3->Update(deltaTime, e);
	m_swap3_3->Update(deltaTime, e);
	m_swap4_3->Update(deltaTime, e);

	if (m_crosshair_3->GetPosition().x >= static_cast<float>(SCREEN_WIDTH) / 2 && v_leftScreen_3)
	{
		m_crosshair_3->SetPosition(Vector2D(m_crosshair_3->GetPosition().x - 5, m_crosshair_3->GetPosition().y));
	}
	if (m_crosshair_3->GetPosition().x <= static_cast<float>(SCREEN_WIDTH) / 2 && !v_leftScreen_3)
	{
		m_crosshair_3->SetPosition(Vector2D(m_crosshair_3->GetPosition().x + 5, m_crosshair_3->GetPosition().y));
	}


	if (my_character_3->GetPosition().x <= leftTowerLeftSide && v_leftScreen_3)
	{
		my_character_3->SetPosition(Vector2D(my_character_3->GetPosition().x + 2, my_character_3->GetPosition().y));
	}

	if (my_character_3->GetPosition().x >= leftTowerRightSide && v_leftScreen_3)
	{
		my_character_3->SetPosition(Vector2D(my_character_3->GetPosition().x - 2, my_character_3->GetPosition().y));
	}

	if (my_character_3->GetPosition().x >= rightTowerRightSide && !v_leftScreen_3)
	{
		my_character_3->SetPosition(Vector2D(my_character_3->GetPosition().x - 2, my_character_3->GetPosition().y));
	}

	if (my_character_3->GetPosition().x <= rightTowerLeftSide && !v_leftScreen_3)
	{
		my_character_3->SetPosition(Vector2D(my_character_3->GetPosition().x + 2, my_character_3->GetPosition().y));
	}


	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_o:
			if (!v_leftScreen_3 && !v_towerCooldown_3)
			{
				v_towerCooldown_3 = true;
				MoveTowerLeft();
			}
			break;
		case SDLK_p:
			if (v_leftScreen_3 && !v_towerCooldown_3)
			{
				v_towerCooldown_3 = true;
				MoveTowerRight();
			}
			break;

		case SDLK_1:

			v_screenMovingLeft_3 = true;
			v_screenMovingRight_3 = false;
			break;

		case SDLK_0:
			v_screenMovingLeft_3 = false;
			v_screenMovingRight_3 = true;
			break;

		case SDLK_e:
			if (v_shotgun_3 && !v_gunSwapCooldown_3)
			{
				v_gunSwapCooldown_3 = true;
				v_normalGun_3 = true;
				v_shotgun_3 = false;
				m_normalGunIcon->SetPosition(Vector2D(375, 350));
				m_shotgunIcon->SetPosition(Vector2D(theVoid, theVoid));
				m_gunswapaudio->Play(1, m_gunswapaudio->m_chunk, 1);
				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_gunSwapCooldown_3 = false;
					return 0;
				}, this);
			}
			else if (v_normalGun_3 && !v_gunSwapCooldown_3 && v_shotgunGet_3)
			{
				v_gunSwapCooldown_3 = true;
				v_normalGun_3 = false;
				v_shotgun_3 = true;
				m_normalGunIcon->SetPosition(Vector2D(theVoid, theVoid));
				m_shotgunIcon->SetPosition(Vector2D(375, 350));
				m_gunswapaudio->Play(1, m_gunswapaudio->m_chunk, 1);
				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_gunSwapCooldown_3 = false;
					return 0;
				}, this);
			}

			break;
		case SDLK_RETURN:


			if (v_bullets_3 > 0 && v_inlevel_3 && !v_bulletCooldown_3 && v_normalGun_3)
			{
				v_bulletCooldown_3 = true;
				m_bullet[v_bullets_3] = new Bullet(m_renderer, "Images/Bullet.png",
				                                   Vector2D(my_character_3->GetPosition().x + 10,
				                                            my_character_3->GetPosition().y),
				                                   Vector2D(m_crosshair_3->GetPosition().x + 10,
				                                            m_crosshair_3->GetPosition().y + 10));


				m_bulletaudio->Play(1, m_bulletaudio->m_chunk, 0);

				v_bullets_3--;


				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_bulletCooldown_3 = false;
					return 0;
				}, this);
			}
			else if (v_bullets_3 >= 3 && v_inlevel_3 && !v_bulletCooldown_3 && v_shotgun_3 && v_shotgunGet_3)
			{
				v_bulletCooldown_3 = true;
				m_bullet[v_bullets_3] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                   Vector2D(my_character_3->GetPosition().x + 10,
				                                            my_character_3->GetPosition().y),
				                                   Vector2D(m_crosshair_3->GetPosition().x + 10,
				                                            m_crosshair_3->GetPosition().y + 10));
				v_bullets_3--;
				m_bullet[v_bullets_3] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                   Vector2D(my_character_3->GetPosition().x + 10,
				                                            my_character_3->GetPosition().y),
				                                   Vector2D(m_crosshair_3->GetPosition().x + 10,
				                                            m_crosshair_3->GetPosition().y + 40));
				v_bullets_3--;
				m_bullet[v_bullets_3] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                   Vector2D(my_character_3->GetPosition().x + 10,
				                                            my_character_3->GetPosition().y),
				                                   Vector2D(m_crosshair_3->GetPosition().x + 10,
				                                            m_crosshair_3->GetPosition().y + -40));

				m_shotgunaudio->Play(1, m_shotgunaudio->m_chunk, 0);

				v_bullets_3--;

				SDL_AddTimer(400, [](Uint32 interval, void* param) -> Uint32
				{
					v_bulletCooldown_3 = false;
					return 0;
				}, this);
			}
			if (v_bullets_3 <= 0 && v_normalGun_3 && v_reload_3 == false)
			{
				m_reloadaudio->Play(2, m_reloadaudio->m_chunk, 0);
				Reload();
			}
			else if (v_bullets_3 < 3 && v_shotgun_3 && v_reload_3 == false)
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
			v_screenMovingLeft_3 = false;
			break;

		case SDLK_0:
			v_screenMovingRight_3 = false;
			break;

		default: ;
		}
	}

	if (e.type == SDL_JOYBUTTONUP)
	{
		switch (e.jbutton.button)
		{
		case 8:
			v_screenMovingLeft_3 = false;
			break;

		case 6:
			v_screenMovingRight_3 = false;
			break;

		default: ;
		}
	}

	if (e.type == SDL_JOYBUTTONDOWN)
	{
		switch (e.jbutton.button)
		{
		case 5:
			if (!v_leftScreen_3 && !v_towerCooldown_3)
			{
				v_towerCooldown_3 = true;
				MoveTowerLeft();
			}


			break;
		case 1:
			if (v_leftScreen_3 && !v_towerCooldown_3)
			{
				v_towerCooldown_3 = true;
				MoveTowerRight();
			}
			break;

		case 2:
			if (v_shotgun_3 && !v_gunSwapCooldown_3)
			{
				v_gunSwapCooldown_3 = true;
				v_normalGun_3 = true;
				v_shotgun_3 = false;
				m_normalGunIcon->SetPosition(Vector2D(375, 350));
				m_shotgunIcon->SetPosition(Vector2D(theVoid, theVoid));
				m_gunswapaudio->Play(1, m_gunswapaudio->m_chunk, 1);
				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_gunSwapCooldown_3 = false;
					return 0;
				}, this);
			}
			else if (v_normalGun_3 && !v_gunSwapCooldown_3 && v_shotgunGet_3)
			{
				v_gunSwapCooldown_3 = true;
				v_normalGun_3 = false;
				v_shotgun_3 = true;
				m_normalGunIcon->SetPosition(Vector2D(theVoid, theVoid));
				m_shotgunIcon->SetPosition(Vector2D(375, 350));
				m_gunswapaudio->Play(1, m_gunswapaudio->m_chunk, 1);
				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_gunSwapCooldown_3 = false;
					return 0;
				}, this);
			}

			break;

		case 9:


			if (v_bullets_3 > 0 && v_inlevel_3 && !v_bulletCooldown_3 && v_normalGun_3)
			{
				v_bulletCooldown_3 = true;
				m_bullet[v_bullets_3] = new Bullet(m_renderer, "Images/Bullet.png",
				                                   Vector2D(my_character_3->GetPosition().x + 10,
				                                            my_character_3->GetPosition().y),
				                                   Vector2D(m_crosshair_3->GetPosition().x + 10,
				                                            m_crosshair_3->GetPosition().y + 10));


				m_shotgunaudio->Play(1, m_shotgunaudio->m_chunk, 0);

				v_bullets_3--;


				SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
				{
					v_bulletCooldown_3 = false;
					return 0;
				}, this);
			}
			else if (v_bullets_3 >= 3 && v_inlevel_3 && !v_bulletCooldown_3 && v_shotgun_3 && v_shotgunGet_3)
			{
				v_bulletCooldown_3 = true;
				m_bullet[v_bullets_3] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                   Vector2D(my_character_3->GetPosition().x + 10,
				                                            my_character_3->GetPosition().y),
				                                   Vector2D(m_crosshair_3->GetPosition().x + 10,
				                                            m_crosshair_3->GetPosition().y + 10));
				v_bullets_3--;
				m_bullet[v_bullets_3] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                   Vector2D(my_character_3->GetPosition().x + 10,
				                                            my_character_3->GetPosition().y),
				                                   Vector2D(m_crosshair_3->GetPosition().x + 10,
				                                            m_crosshair_3->GetPosition().y + 40));
				v_bullets_3--;
				m_bullet[v_bullets_3] = new Bullet(m_renderer, "Images/FastBullet.png",
				                                   Vector2D(my_character_3->GetPosition().x + 10,
				                                            my_character_3->GetPosition().y),
				                                   Vector2D(m_crosshair_3->GetPosition().x + 10,
				                                            m_crosshair_3->GetPosition().y + -40));

				m_shotgunaudio->Play(1, m_shotgunaudio->m_chunk, 0);

				v_bullets_3--;

				SDL_AddTimer(400, [](Uint32 interval, void* param) -> Uint32
				{
					v_bulletCooldown_3 = false;
					return 0;
				}, this);
			}
			if (v_bullets_3 <= 0 && v_normalGun_3 && v_reload_3 == false)
			{
				m_reloadaudio->Play(2, m_reloadaudio->m_chunk, 0);
				Reload();
			}
			else if (v_bullets_3 < 3 && v_shotgun_3 && v_reload_3 == false)
			{
				m_reloadaudio->Play(2, m_reloadaudio->m_chunk, 0);
				Reload();
			}


			break;

		default: ;
		}
	}

	v_inlevel_3 = true;
}


bool GameScreenLevel3::SetUpLevel()
{
	v_playerHealth_3 = g_maxplayerHealth;
	v_baseHealth_3 = g_maxbaseHealth;
	g_score = 0;
	v_inlevel_3 = false;
	g_levelComplete = false;


	v_leftScreen_3 = true;
	v_bullets_3 = 6;
	v_reload_3 = false;
	v_shotgunGet_3 = false;
	v_shotgunGetToggle_3 = false;
	v_bulletCooldown_3 = false;
	v_towerCooldown_3 = false;
	v_gunSwapCooldown_3 = false;
	v_normalGun_3 = true;
	v_shotgun_3 = false;
	v_screenMovingLeft_3 = false;
	v_screenMovingRight_3 = false;
	v_dontRender_3 = false;
	v_skyboxRender_3 = false;
	v_backgroundX_3 = 0.0f;
	v_backgroundY_3 = 0.0f;
	m_background_texture = new Texture2D(m_renderer);
	m_skybox = new GameObject(m_renderer, "Images/Skybox2.png", Vector2D(0, 0));
	// I Love SteamMan
	my_character_3 = new Character(m_renderer, "Images/Character/SteamMan.png", Vector2D(247, 246));
	m_crosshair_3 = new Crosshair(m_renderer, "Images/Crosshair.png", Vector2D(100, 350));
	m_shotgun_get = new GameObject(m_renderer, "Images/ShotGunGet.png", Vector2D(300, 150));
	m_swap0_3 = new GameObject(m_renderer, "Images/Swap0.png", Vector2D(theVoid, theVoid));
	m_swap1_3 = new GameObject(m_renderer, "Images/Swap1.png", Vector2D(theVoid, theVoid));
	m_swap2_3 = new GameObject(m_renderer, "Images/Swap2.png", Vector2D(theVoid, theVoid));
	m_swap3_3 = new GameObject(m_renderer, "Images/Swap3.png", Vector2D(theVoid, theVoid));
	m_swap4_3 = new GameObject(m_renderer, "Images/Swap4.png", Vector2D(theVoid, theVoid));
	m_bulletCounter[0] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount0.png", Vector2D(240, 10));
	m_bulletCounter[1] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount1.png", Vector2D(240, 10));
	m_bulletCounter[2] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount2.png", Vector2D(240, 10));
	m_bulletCounter[3] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount3.png", Vector2D(240, 10));
	m_bulletCounter[4] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount4.png", Vector2D(240, 10));
	m_bulletCounter[5] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount5.png", Vector2D(240, 10));
	m_bulletCounter[6] = new GameObject(m_renderer, "Images/BulletCounter/BulletsCount6.png", Vector2D(240, 10));
	m_timeIcon = new GameObject(m_renderer, "Images/Time Remaining.png", Vector2D(300, 30));
	m_normalGunIcon = new GameObject(m_renderer, "Images/NormalGun.png", Vector2D(375, 350));
	m_shotgunIcon = new GameObject(m_renderer, "Images/ShotGun.png", Vector2D(theVoid, theVoid));
	m_scoreIcon = new GameObject(m_renderer, "Images/Score.png", Vector2D(300, 10));
	m_scoreText = new GameText(m_renderer, "fonts/arial.ttf", 24);
	m_timerText = new GameText(m_renderer, "fonts/arial.ttf", 20);
	m_playerHealthText = new GameText(m_renderer, "fonts/arial.ttf", 20);
	m_baseHealthText = new GameText(m_renderer, "fonts/arial.ttf", 20);
	m_playerHealthIcon = new GameObject(m_renderer, "Images/PlayerHealth.png", Vector2D(300, 60));
	m_baseHealthIcon = new GameObject(m_renderer, "Images/BaseHealth.png", Vector2D(300, 90));
	m_enemy_3[0] = new EnemyFlyers(m_renderer, "Images/EnemyFlyers/1.png", Vector2D(-40, 270));
	m_enemy_3[1] = new EnemyFlyers(m_renderer, "Images/EnemyFlyers/1.png", Vector2D(-350, 270));
	m_enemy_3[2] = new EnemyFlyers(m_renderer, "Images/EnemyFlyers/1.png", Vector2D(850, 270));
	m_enemy_3[3] = new EnemyFlyers(m_renderer, "Images/EnemyFlyers/1.png", Vector2D(1200, 270));
	m_enemyGround_3[0] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(-100, 430));
	m_enemyGround_3[1] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(-200, 430));
	m_enemyGround_3[2] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(-300, 430));
	m_enemyGround_3[3] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(825, 430));
	m_enemyGround_3[4] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(925, 430));
	m_enemyGround_3[5] = new EnemyGround(m_renderer, "Images/EnemyGround/1.png", Vector2D(1025, 430));
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


	if (!m_background_texture->LoadFromFile("Images/Night Level.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	return true;
}


void GameScreenLevel3::MoveTowerLeft()
{
	m_swapaudio->Play(1, m_swapaudio->m_chunk, 0);
	m_swap0_3->SetPosition(Vector2D(250, 50));
	SDL_AddTimer(100, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character_3 != nullptr)
		{
			m_swap0_3->SetPosition(Vector2D(theVoid, theVoid));
			m_swap1_3->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character_3 != nullptr)
		{
			m_swap1_3->SetPosition(Vector2D(theVoid, theVoid));
			m_swap2_3->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character_3 != nullptr)
		{
			m_swap2_3->SetPosition(Vector2D(theVoid, theVoid));
			m_swap3_3->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(400, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character_3 != nullptr)
		{
			m_swap3_3->SetPosition(Vector2D(theVoid, theVoid));
			m_swap4_3->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(500, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character_3 != nullptr)
		{
			m_swap4_3->SetPosition(Vector2D(theVoid, theVoid));
			my_character_3->SetPosition(Vector2D(247, 246));
			m_crosshair_3->SetPosition(Vector2D(100, 300));
			v_leftScreen_3 = true;
			v_towerCooldown_3 = false;
		}
		return 0;
	}, this);
}

void GameScreenLevel3::MoveTowerRight()
{
	m_swapaudio->Play(1, m_swapaudio->m_chunk, 0);
	m_swap0_3->SetPosition(Vector2D(250, 50));
	SDL_AddTimer(100, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character_3 != nullptr)
		{
			m_swap0_3->SetPosition(Vector2D(theVoid, theVoid));
			m_swap1_3->SetPosition(Vector2D(250, 50));
		}

		return 0;
	}, this);

	SDL_AddTimer(200, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character_3 != nullptr)
		{
			m_swap1_3->SetPosition(Vector2D(theVoid, theVoid));
			m_swap2_3->SetPosition(Vector2D(250, 50));
		}

		return 0;
	}, this);

	SDL_AddTimer(300, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character_3 != nullptr)
		{
			m_swap2_3->SetPosition(Vector2D(theVoid, theVoid));
			m_swap3_3->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(400, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character_3 != nullptr)
		{
			m_swap3_3->SetPosition(Vector2D(theVoid, theVoid));
			m_swap4_3->SetPosition(Vector2D(250, 50));
		}
		return 0;
	}, this);

	SDL_AddTimer(500, [](Uint32 interval, void* param) -> Uint32
	{
		if (my_character_3 != nullptr)
		{
			m_swap4_3->SetPosition(Vector2D(theVoid, theVoid));
			my_character_3->SetPosition(Vector2D(526, 244));
			m_crosshair_3->SetPosition(Vector2D(662, 300));
			v_leftScreen_3 = false;
			v_towerCooldown_3 = false;
		}
		return 0;
	}, this);
}
