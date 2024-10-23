// ----------------------------- INCLUDE ----------------------------- //
#include "GameObject.h"
// ----------------------------- INCLUDE ----------------------------- //

// Initialize the GameObject by setting the renderer, the image path and the start position
GameObject::GameObject(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition)
{
	m_renderer = renderer;
	m_position = startPosition;
	m_texture = new Texture2D(m_renderer);
	m_collision_radius = 15;

	// Load the image
	if (!m_texture->LoadFromFile(imagePath))
	{
		// Error message
		std::cout << "Failed to load background texture!";
	}
}

// Destructor to delete the texture and set the renderer to nullptr
GameObject::~GameObject()
{
	if (m_texture != nullptr)
	{
		delete m_texture;
		m_texture = nullptr;
	}

	m_renderer = nullptr;
}

// Render the GameObject
void GameObject::Render()
{
	if (m_texture != nullptr)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
}

// Update the GameObject
void GameObject::Update(float deltaTime, SDL_Event e)
{
}

// Get the position of the GameObject
Vector2D GameObject::GetPosition() const
{
	return m_position;
}

// Set the position of the GameObject
void GameObject::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

// Get the collision radius of the GameObject
float GameObject::GetCollisionRadius() const
{
	return m_collision_radius;
}

// Get the collision box of the GameObject
Rect2D GameObject::GetCollisionBox() const
{
	return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
}
