// ----------------------------- INCLUDE ----------------------------- //
#include "Collisions.h"
// ----------------------------- INCLUDE ----------------------------- //


//Initialise the instance to null.
Collisions* Collisions::m_instance = nullptr;

//Constructor
Collisions::Collisions()
= default;

// Delete the instance of the class
Collisions::~Collisions()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

// Create the instance of the class, if one has not been created yet.
Collisions* Collisions::Instance()
{
	if (!m_instance)
	{
		m_instance = new Collisions();
	}
	return m_instance;
}

// Check for collisions between two circle based game objects
// I am not great with maths so I could not tell you how this works, but it does.
bool Collisions::Circle(GameObject* a, GameObject* b)
{
	const auto vec = Vector2D((a->GetPosition().x - b->GetPosition().x), (a->GetPosition().y - b->GetPosition().y));
	const double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	const double combinedDistance = (a->GetCollisionRadius() + b->GetCollisionRadius());
	return distance < combinedDistance;
}

// Check for collisions between two rectangle based game objects,
// by comparing their width and height in a distance calulation.
bool Collisions::Box(const Rect2D rect1, const Rect2D rect2)
{
	if (rect1.x + rect1.width > rect2.x &&
		rect1.x + rect1.width < rect2.x + rect2.width &&
		rect1.y + rect1.height > rect2.y &&
		rect1.y + rect1.height < rect2.y + rect2.height)
	{
		return true;
	}
	return false;
}
