// ----------------------------- INCLUDE ----------------------------- //
#include "GameText.h"
// ----------------------------- INCLUDE ----------------------------- //

// Set the static member variable to false
bool GameText::ttfHasInit = false;

// Try to initialise TTF, the renderer and the font
GameText::GameText(SDL_Renderer* renderer, std::string fontPath, unsigned int fontSize)
{
	if (!InitTTF())
	{
		std::cerr << "Couldn't initialise TTF; error is " << TTF_GetError() << std::endl;
		errorEncountered = true;
		return;
	}

	this->m_renderer = renderer;

	this->LoadFont(fontPath, fontSize);
}

// Close the font and texture
GameText::~GameText()
{
	if (m_font != nullptr)
	{
		TTF_CloseFont(m_font);
		m_font = nullptr;
	}

	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

// Load the font from the path and size
bool GameText::LoadFont(const std::string& fontPath, unsigned int fontSize)
{
	// Load the font from a font path
	this->m_font = TTF_OpenFont(fontPath.c_str(), fontSize);

	// If the font is null, print an error message and return false
	if (!this->m_font)
	{
		std::cerr << "Couldn't load font from path " << fontPath << "; error is " << TTF_GetError() << std::endl;
		errorEncountered = true;
		return false;
	}

	return true;
}

// Render the text at the given position
void GameText::RenderAt(const std::string& text, int x, int y)
{
	// If an error has been encountered, return
	if (errorEncountered)
	{
		return;
	}

	// If the texture is not null, destroy it
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
	}

	// Initialise the width and height of the text
	int w, h;

	// Get the width and height of the text
	TTF_SizeText(m_font, text.c_str(), &w, &h);

	// Render the text using given parameters
	SDL_Surface* surf = TTF_RenderText_Blended(m_font, text.c_str(), m_color);
	m_texture = SDL_CreateTextureFromSurface(m_renderer, surf);
	SDL_FreeSurface(surf);

	// Set the render rect
	SDL_Rect renderRect{x, y, w, h};

	// Render the text
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &renderRect);
}

// Set the color of the text
void GameText::SetColor(SDL_Color color)
{
	this->m_color = color;
}


// Initialise TTF
bool GameText::InitTTF()
{
	if (ttfHasInit)
	{
		return true;
	}

	return (TTF_Init() >= 0);
}
