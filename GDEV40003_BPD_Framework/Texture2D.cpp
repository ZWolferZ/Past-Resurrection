// ----------------------------- INCLUDE ----------------------------- //
#include "Texture2D.h"
// ----------------------------- INCLUDE ----------------------------- //


// Initialise the texture by parsing a renderer
Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;

	m_texture = nullptr;

	m_width = 0;
	m_height = 0;
}

// Free the texture from memory and set the used renderer to nullptr
Texture2D::~Texture2D()
{
	Free();

	m_renderer = nullptr;
}

// Load a texture from a file
bool Texture2D::LoadFromFile(const std::string& path)
{
	// Free the texture if it exists
	Free();

	SDL_Surface* p_surface = IMG_Load(path.c_str());

	if (p_surface != nullptr)
	{
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0XFF, 0XFF));
		// Create the texture from the pixels on the surface
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);

		if (m_texture == nullptr)
		{
			std::cout << "Unable to create texture from surface. Error: " << IMG_GetError();
		}
		else
		{
			m_width = p_surface->w;
			m_height = p_surface->h;
		}
		// remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
	}
	return m_texture != nullptr;
}

// Free the texture from memory
void Texture2D::Free()
{
	if (m_texture != nullptr)
	{
		m_width = 0;
		m_height = 0;
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

// Render the texture to the screen
void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle) const
{
	SDL_Rect renderLocation = {new_position.x, new_position.y, m_width, m_height};

	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, angle, nullptr, flip
	);
}
