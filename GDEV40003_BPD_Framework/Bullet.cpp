// ----------------------------- INCLUDE ----------------------------- //
#include "Bullet.h"
// ----------------------------- INCLUDE ----------------------------- //

// Initialize the Bullet and set the start and end position
Bullet::Bullet(SDL_Renderer* renderer, const std::string& imagePath, Vector2D startPosition, Vector2D endPosition) :
	GameObject(
		renderer, imagePath, startPosition)
{
	m_renderer = renderer;
	m_startpositionX = startPosition.x;
	m_startpositionY = startPosition.y;
	m_endpositionX = endPosition.x;
	m_endpositionY = endPosition.y;
	m_deleteBullet = false;
	m_directionX = 0;
	m_directionY = 0;
	m_distance = 0;
	m_nextPositionX = 0;
	m_nextPositionY = 0;
	std::cout << "Bullet Spawned" << '\n';
}

// Deconstructor
Bullet::~Bullet()
= default;

// Update the Bullet to get it to the end position
void Bullet::Update(float deltaTime, SDL_Event e)
{
	// If the bullet is not deleted
	if (!m_deleteBullet)
	{
		// Check if the bullet is not at the end position
		if (GetPosition().x != m_endpositionX && GetPosition().y != m_endpositionY)
		{
			// Calculate the direction and distance
			m_directionX = m_endpositionX - GetPosition().x;
			m_directionY = m_endpositionY - GetPosition().y;
			m_distance = sqrt(m_directionX * m_directionX + m_directionY * m_directionY);

			// If the distance is less than the speed, set the position to the end position
			if (m_distance <= m_speed)
			{
				SetPosition(Vector2D(m_endpositionX, m_endpositionY));
			}
			else
			{
				//Normalise the direction, I think
				// It's kind of hard to tell when I am bad at math
				m_directionX /= m_distance;
				m_directionY /= m_distance;

				// Calculate the next position
				m_nextPositionX = GetPosition().x + m_directionX * m_speed;
				m_nextPositionY = GetPosition().y + m_directionY * m_speed;

				// Set the next position
				SetPosition(Vector2D(m_nextPositionX, m_nextPositionY));
			}
		}
		else
		{
			// If the bullet is at the end position, delete it
			m_deleteBullet = true;
			// Set the position to the void
			SetPosition(Vector2D(theVoid, theVoid));
			std::cout << "Bullet Deleted" << '\n';
		}
	}
}
