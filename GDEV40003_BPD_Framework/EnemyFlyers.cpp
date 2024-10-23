// ----------------------------- INCLUDE ----------------------------- //
#include "EnemyFlyers.h"
// ----------------------------- INCLUDE ----------------------------- //

// Initialize the enemy flyer, and set the default facing direction to left
EnemyFlyers::EnemyFlyers(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : GameObject(
	renderer, imagePath, startPosition)
{
	m_facing_Direction = FACING_LEFT;
	m_moving_left = false;
	m_moving_right = false;
}

// Animation varibles for the enemy flyer (Cannot be moved to the header file, for timers to work)
int m_currentFrameFlyer = 1;
bool m_animationToggleFlyer = false;

// Destructor
EnemyFlyers::~EnemyFlyers()
= default;

// Render the enemy flyer and flip the texture based on the facing direction
void EnemyFlyers::Render()
{
	if (m_texture != nullptr)
	{
		if (m_facing_Direction == FACING_LEFT)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE);
		}
		else if (m_facing_Direction == FACING_RIGHT)
		{
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
		}
	}
}

// Update the enemy flyer
void EnemyFlyers::Update(float deltaTime, SDL_Event e)
{
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	// Refer to the character source file for a explanation of the animation code
	if (m_animationToggleFlyer == false)
	{
		m_animationToggleFlyer = true;

		// If the enemy is not hit, play the normal animation
		if (!m_enemyIsHit)
		{
			// Checking for the boolean of the enemy being hit ever timer to catch the change
			if (!m_enemyIsHit)
			{
				// Set the current frame to 1
				SDL_AddTimer(150, [](Uint32 interval, void* param) -> Uint32
				{
					m_currentFrameFlyer = 1;

					return 0;
				}, this);
			}

			if (!m_enemyIsHit)
			{
				// Set the current frame to 2
				SDL_AddTimer(250, [](Uint32 interval, void* param) -> Uint32
				{
					m_currentFrameFlyer = 2;
					return 0;
				}, this);
			}
			if (!m_enemyIsHit)
			{
				// Set the current frame to 3
				SDL_AddTimer(350, [](Uint32 interval, void* param) -> Uint32
				{
					m_currentFrameFlyer = 3;
					return 0;
				}, this);
			}
			if (!m_enemyIsHit)
			{
				// Set the current frame to 4
				SDL_AddTimer(450, [](Uint32 interval, void* param) -> Uint32
				{
					m_currentFrameFlyer = 4;

					m_animationToggleFlyer = false;
					return 0;
				}, this);
			}
		}
		// If the enemy is hit, play the hit animation
		else
		{
			if (m_enemyIsHit)
			{
				// Set the current frame to 1
				SDL_AddTimer(150, [](Uint32 interval, void* param) -> Uint32
				{
					m_currentFrameFlyer = 1;

					return 0;
				}, this);
			}

			if (m_enemyIsHit)
			{
				// Set the current frame to 2
				SDL_AddTimer(250, [](Uint32 interval, void* param) -> Uint32
				{
					m_currentFrameFlyer = 2;
					return 0;
				}, this);
			}

			if (m_enemyIsHit)
			{
				// Set the current frame to 3
				SDL_AddTimer(350, [](Uint32 interval, void* param) -> Uint32
				{
					m_currentFrameFlyer = 3;
					return 0;
				}, this);
			}

			if (m_enemyIsHit)
			{
				// Set the current frame to 4
				SDL_AddTimer(450, [](Uint32 interval, void* param) -> Uint32
				{
					m_currentFrameFlyer = 4;


					return 0;
				}, this);
			}

			if (m_enemyIsHit)
			{
				// Set the current frame to 5
				SDL_AddTimer(550, [](Uint32 interval, void* param) -> Uint32
				{
					m_currentFrameFlyer = 5;


					return 0;
				}, this);
			}
			if (m_enemyIsHit)
			{
				// Set the current frame to 6
				SDL_AddTimer(650, [](Uint32 interval, void* param) -> Uint32
				{
					m_currentFrameFlyer = 6;

					m_animationToggleFlyer = false;
					return 0;
				}, this);
			}
		}
	}

	// Switch statement to change the texture based on the current frame
	switch (m_currentFrameFlyer)
	{
	case 1:

		if (m_enemyIsHit)
		{
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/EnemyFlyers/Hit1.png");
		}
		else
		{
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/EnemyFlyers/1.png");
		}

		break;
	case 2:

		if (m_enemyIsHit)
		{
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/EnemyFlyers/Hit2.png");
		}
		else
		{
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/EnemyFlyers/2.png");
		}

		break;
	case 3:

		if (m_enemyIsHit)
		{
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/EnemyFlyers/Hit3.png");
		}
		else
		{
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/EnemyFlyers/3.png");
		}
		break;
	case 4:

		if (m_enemyIsHit)
		{
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/EnemyFlyers/Hit4.png");
		}
		else
		{
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/EnemyFlyers/4.png");
		}
		break;

	case 5:

		delete m_texture;
		m_texture = nullptr;
		m_texture = new Texture2D(m_renderer);
		m_texture->LoadFromFile("Images/EnemyFlyers/Hit5.png");

		break;
	case 6:

		delete m_texture;
		m_texture = nullptr;
		m_texture = new Texture2D(m_renderer);
		m_texture->LoadFromFile("Images/EnemyFlyers/Hit6.png");

		m_enemyIsHit = false;
		break;

	default: break;
	}
}


// Move the enemy flyer left
void EnemyFlyers::MoveLeft(float deltaTime)
{
	if (!m_enemyIsHit)
	{
		m_position.x -= enemyflyspeed * deltaTime;
		m_facing_Direction = FACING_LEFT;
	}
}

// Move the enemy flyer right
void EnemyFlyers::MoveRight(float deltaTime)
{
	if (!m_enemyIsHit)
	{
		m_position.x += enemyflyspeed * deltaTime;
		m_facing_Direction = FACING_RIGHT;
	}
}

// Get the collision box of the enemy flyer
Rect2D EnemyFlyers::GetCollisionBox() const
{
	return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight() * 1.5f);
}
