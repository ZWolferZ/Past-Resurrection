// ----------------------------- INCLUDE ----------------------------- //
#include "Character.h"
// ----------------------------- INCLUDE ----------------------------- //

// Initialize the Character and set the initial facing direction to left
Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : GameObject(
	renderer, imagePath, startPosition)
{
	m_facing_Direction = FACING_LEFT;
	m_moving_left = false;
	m_moving_right = false;
}

// Animation variables (Cannot be in the header file, for use in the SDL timers)
int m_currentCharacterFrame = 1;
bool m_animationCharacterToggle = false;
bool m_characterIsIdle = true;

// Destructor
Character::~Character()
= default;

// Render the character and flip the texture based on the facing direction
void Character::Render()
{
	if (m_texture != nullptr)
	{
		if (m_facing_Direction == FACING_RIGHT)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE);
		}
		else if (m_facing_Direction == FACING_LEFT)
		{
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
		}
	}
}

// Move the character left
void Character::MoveLeft(float deltaTime)
{
	m_position.x -= movementSpeed * deltaTime;
}

// Move the character right
void Character::MoveRight(float deltaTime)
{
	m_position.x += movementSpeed * deltaTime;
}

// Update the character based on the input
void Character::Update(float deltaTime, SDL_Event e)
{
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	// Check for keyboard input
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		// Move left
		case SDLK_a:
			m_moving_left = true;
			m_characterIsIdle = false;
			m_facing_Direction = FACING_LEFT;
			break;

		// Move right
		case SDLK_d:
			m_moving_right = true;
			m_characterIsIdle = false;
			m_facing_Direction = FACING_RIGHT;
			break;

		// Change facing direction to left (For tower switching)
		case SDLK_o:
			m_facing_Direction = FACING_LEFT;
			break;

		// Change facing direction to right (For tower switching)
		case SDLK_p:
			m_facing_Direction = FACING_RIGHT;
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
		case SDLK_a:
			m_characterIsIdle = true;
			m_moving_left = false;
			break;
		case SDLK_d:
			m_characterIsIdle = true;
			m_moving_right = false;
			break;

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
		case 8:
			m_moving_left = true;
			m_characterIsIdle = false;
			m_facing_Direction = FACING_LEFT;
			break;
		case 6:
			m_moving_right = true;
			m_characterIsIdle = false;
			m_facing_Direction = FACING_RIGHT;
			break;

		case 5:
			m_facing_Direction = FACING_LEFT;
			break;

		case 1:
			m_facing_Direction = FACING_RIGHT;
			break;

		default:
			break;
		}
	}

	if (e.type == SDL_JOYBUTTONUP)
	{
		switch (e.jbutton.button)
		{
		case 8:
			m_characterIsIdle = true;
			m_moving_left = false;
			break;
		case 6:
			m_characterIsIdle = true;
			m_moving_right = false;
			break;

		default:
			//Nothing
			break;
		}
	}

	// Animation for the character
	// Okay, so this is a bit of a mess, but it works. I'm using SDL timers to change the character frame,
	// Then I use a switch statement to change the texture based on the current frame/animation.

	// I can't tell if this is the most genius thing I 've ever done, or the most stupid.
	// But it works, so I'm happy with it.

	// It does cause a bit of a memory leak, but it's not too bad, and is the price I pay for cheap and dirty animation.

	// If someone could also tell me the magic behind the SDL timers, that would be great, because I don't really understand how they are working.

	// If the character is idle, play the idle animation
	if (m_characterIsIdle)
	{
		// If the animation is not already playing, start it
		if (m_animationCharacterToggle == false)
		{
			// Set the animation toggle to true
			m_animationCharacterToggle = true;

			// Set the current frame to 1
			SDL_AddTimer(150, [](Uint32 interval, void* param) -> Uint32
			{
				m_currentCharacterFrame = 1;


				return 0;
			}, this);

			// Set the current frame to 2
			SDL_AddTimer(250, [](Uint32 interval, void* param) -> Uint32
			{
				m_currentCharacterFrame = 2;

				return 0;
			}, this);

			// Set the current frame to 3
			SDL_AddTimer(350, [](Uint32 interval, void* param) -> Uint32
			{
				m_currentCharacterFrame = 3;
				return 0;
			}, this);

			// Set the current frame to 4
			SDL_AddTimer(450, [](Uint32 interval, void* param) -> Uint32
			{
				m_currentCharacterFrame = 4;

				m_animationCharacterToggle = false;
				return 0;
			}, this);
		}

		// Change the texture based on the current frame
		switch (m_currentCharacterFrame)
		{
		case 1:
			// My attempt to patch the memory leak (it doesn't work)
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/Character/Idle1.png");
			break;
		case 2:
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/Character/Idle2.png");
			break;
		case 3:
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/Character/Idle3.png");
			break;
		case 4:
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/Character/Idle4.png");
			break;

		default: break;
		}
	}
	// If the character is moving, play the walking animation
	else
	{
		// If the animation is not already playing, start it
		if (m_animationCharacterToggle == false)
		{
			// Set the animation toggle to true
			m_animationCharacterToggle = true;

			// Set the current frame to 1
			SDL_AddTimer(150, [](Uint32 interval, void* param) -> Uint32
			{
				m_currentCharacterFrame = 1;


				return 0;
			}, this);

			// Set the current frame to 2
			SDL_AddTimer(250, [](Uint32 interval, void* param) -> Uint32
			{
				m_currentCharacterFrame = 2;

				return 0;
			}, this);

			// Set the current frame to 3
			SDL_AddTimer(350, [](Uint32 interval, void* param) -> Uint32
			{
				m_currentCharacterFrame = 3;
				return 0;
			}, this);

			// Set the current frame to 4
			SDL_AddTimer(450, [](Uint32 interval, void* param) -> Uint32
			{
				m_currentCharacterFrame = 4;


				return 0;
			}, this);

			// Set the current frame to 5
			SDL_AddTimer(550, [](Uint32 interval, void* param) -> Uint32
			{
				m_currentCharacterFrame = 5;


				return 0;
			}, this);

			// Set the current frame to 6
			SDL_AddTimer(650, [](Uint32 interval, void* param) -> Uint32
			{
				m_currentCharacterFrame = 6;

				m_animationCharacterToggle = false;
				return 0;
			}, this);
		}
		// Change the texture based on the current frame
		switch (m_currentCharacterFrame)
		{
		case 1:
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/Character/Walk1.png");
			break;
		case 2:
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/Character/Walk2.png");
			break;
		case 3:
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/Character/Walk3.png");
			break;
		case 4:
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/Character/Walk4.png");
			break;

		case 5:
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/Character/Walk5.png");
			break;

		case 6:
			delete m_texture;
			m_texture = nullptr;
			m_texture = new Texture2D(m_renderer);
			m_texture->LoadFromFile("Images/Character/Walk6.png");
			break;
		default: break;
		}
	}
}
