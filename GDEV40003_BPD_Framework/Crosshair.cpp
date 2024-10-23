// ----------------------------- INCLUDE ----------------------------- //
#include "Crosshair.h"
// ----------------------------- INCLUDE ----------------------------- //

// Initialize the crosshair and set the moving variables to false
Crosshair::Crosshair(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition): GameObject(
	renderer, imagePath, startPosition)
{
	m_moving_left = false;
	m_moving_right = false;
	m_moving_up = false;
	m_moving_down = false;
}

// Deconstructor
Crosshair::~Crosshair() = default;

// Render the crosshair, if it exists
void Crosshair::Render()
{
	if (m_texture != nullptr)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
}

// Move the crosshair left
void Crosshair::MoveLeft(float deltaTime)
{
	m_position.x -= crosshairSpeed * deltaTime;
}

// Move the crosshair right
void Crosshair::MoveRight(float deltaTime)
{
	m_position.x += crosshairSpeed * deltaTime;
}

// Move the crosshair up
void Crosshair::MoveUp(float deltaTime)
{
	m_position.y -= crosshairSpeed * deltaTime;
}

// Move the crosshair down
void Crosshair::MoveDown(float deltaTime)
{
	m_position.y += crosshairSpeed * deltaTime;
}

// Update the crosshairs position based on the input
void Crosshair::Update(float deltaTime, SDL_Event e)
{
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
	else if (m_moving_up)
	{
		MoveUp(deltaTime);
	}
	else if (m_moving_down)
	{
		MoveDown(deltaTime);
	}


	// Keep the crosshair within the screen bounds
	if (GetPosition().x >= rightScreenBounds) // Right Screen Bounds
	{
		SetPosition(Vector2D(GetPosition().x - 5, GetPosition().y));
	}
	if (GetPosition().x <= leftScreenBounds) // Left Screen Bounds
	{
		SetPosition(Vector2D(GetPosition().x + 5, GetPosition().y));
	}
	if (GetPosition().y >= bottomScreenBounds) // Bottom Screen Bounds
	{
		SetPosition(Vector2D(GetPosition().x, GetPosition().y - 5));
	}
	if (GetPosition().y <= topScreenBounds) // Top Screen Bounds
	{
		SetPosition(Vector2D(GetPosition().x, GetPosition().y + 5));
	}

	// Check for keyboard input
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;

			break;
		case SDLK_RIGHT:
			m_moving_right = true;

			break;

		case SDLK_UP:
			m_moving_up = true;
			break;

		case SDLK_DOWN:
			m_moving_down = true;
			break;
		default:
			// Nothing
			break;
		}
	}


	if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
			break;

		case SDLK_UP:
			m_moving_up = false;
			break;
		case SDLK_DOWN:
			m_moving_down = false;
		default:
			// Nothing
			break;
		}
	}

	// Check for controller input
	if (e.type == SDL_JOYBUTTONDOWN)
	{
		switch (e.jbutton.button)
		{
		case 14:
			m_moving_left = true;

			break;
		case 15:
			m_moving_right = true;

			break;

		case 13:
			m_moving_up = true;
			break;

		case 16:
			m_moving_down = true;
			break;
		default:
			// Nothing
			break;
		}
	}

	if (e.type == SDL_JOYBUTTONUP)
	{
		switch (e.jbutton.button)
		{
		case 14:
			m_moving_left = false;
			break;
		case 15:
			m_moving_right = false;
			break;

		case 13:
			m_moving_up = false;
			break;
		case 16:
			m_moving_down = false;
			break; // Oops, their was a break missing here on the evercade port, luckily it didnt matter
		default:
			// Nothing
			break;
		}
	}
}
