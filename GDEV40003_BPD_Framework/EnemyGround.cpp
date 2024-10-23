// ----------------------------- INCLUDE ----------------------------- //
#include "EnemyGround.h"
// ----------------------------- INCLUDE ----------------------------- //

// Initialize the ground-type enemy
EnemyGround::EnemyGround(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : GameObject(
	renderer, imagePath, startPosition)
{
	m_facing_Direction = FACING_LEFT;
	m_moving_left = false;
	m_moving_right = false;
}

// Animation varibles for the enemy (Cannot be moved to the header file, for timers to work)
int m_currentFrame = 1;
bool m_animationToggle = false;

// Destructor
EnemyGround::~EnemyGround()
= default;

// Render the enemy and flip the image based on the direction it is facing
void EnemyGround::Render()
{
	if (m_texture != nullptr)
	{
		if (m_facing_Direction == FACING_LEFT)
		{
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
		}
		else if (m_facing_Direction == FACING_RIGHT)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE);
		}
	}
}

// Update the enemy 
void EnemyGround::Update(float deltaTime, SDL_Event e)
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
	if (m_animationToggle == false)
	{
		m_animationToggle = true;

		// Set the current frame to 1
		SDL_AddTimer(150, [](Uint32 interval, void* param) -> Uint32
		{
			m_currentFrame = 1;

			return 0;
		}, this);

		// Set the current frame to 2
		SDL_AddTimer(250, [](Uint32 interval, void* param) -> Uint32
		{
			m_currentFrame = 2;
			return 0;
		}, this);

		//	Set the current frame to 3
		SDL_AddTimer(350, [](Uint32 interval, void* param) -> Uint32
		{
			m_currentFrame = 3;
			return 0;
		}, this);

		// Set the current frame to 4
		SDL_AddTimer(450, [](Uint32 interval, void* param) -> Uint32
		{
			m_currentFrame = 4;

			m_animationToggle = false;
			return 0;
		}, this);
	}

	// Switch statement to change the texture based on the current frame
	switch (m_currentFrame)
	{
	case 1:


		m_texture->LoadFromFile("Images/EnemyGround/1.png");


		break;
	case 2:


		m_texture->LoadFromFile("Images/EnemyGround/2.png");


		break;
	case 3:


		m_texture->LoadFromFile("Images/EnemyGround/3.png");

		break;
	case 4:


		m_texture->LoadFromFile("Images/EnemyGround/4.png");

		break;


	default: break;
	}
}

// Move the enemy left
void EnemyGround::MoveLeft(float deltaTime)
{
	m_position.x -= enemyflyspeed * deltaTime;
	m_facing_Direction = FACING_LEFT;
}

// Move the enemy right
void EnemyGround::MoveRight(float deltaTime)
{
	m_position.x += enemyflyspeed * deltaTime;
	m_facing_Direction = FACING_RIGHT;
}

// Return the collision box of the enemy
Rect2D EnemyGround::GetCollisionBox() const
{
	return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight() * 1.5f);
}
