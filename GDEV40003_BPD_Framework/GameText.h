// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _GAMETEXT_H
#define GAMETEXT_H
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- GAMETEXT CLASS ----------------------------- //
class GameText
{
public:
	/// <summary>
	/// Initialise text using the renderer, a font path and a font size.
	/// </summary>
	GameText(SDL_Renderer* renderer, std::string fontPath, unsigned int fontSize);

	/// <summary>
	/// Deletes the texture and closes the font.
	/// </summary>
	~GameText();

	/// <summary>
	/// Loads a font file from a specified file path.
	/// </summary>
	bool LoadFont(const std::string& fontPath, unsigned int fontSize);

	/// <summary>
	/// Renders the text as a string at specific coords.
	/// </summary>
	void RenderAt(const std::string& text, int x, int y);

	/// <summary>
	/// Sets the colour of the gametext.
	/// </summary>
	void SetColor(SDL_Color color);

protected:
	// Texture and font
	SDL_Texture* m_texture = nullptr;
	TTF_Font* m_font = nullptr;

	// Text colour
	SDL_Color m_color{255, 255, 255, 255};

	// Renderer
	SDL_Renderer* m_renderer = nullptr;

private:
	// Static bool to check if TTF has been initialised
	static bool ttfHasInit;

	/// <summary>
	/// Initilises TTF for the text to work.
	/// </summary>
	static bool InitTTF();

	// Error handling
	bool errorEncountered = false;
};

#endif // _GAMETEXT_H
// ----------------------------- GAMETEXT CLASS ----------------------------- //
