// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _TEXTURE2D_H
#define TEXTURE2D_H
#include <SDL.h>
#include <string>
#include "Commons.h"
#include <SDL_image.h>
#include <iostream>
// ----------------------------- INCLUDES ----------------------------- //


// ----------------------------- TEXTURE2D CLASS ----------------------------- //
class Texture2D
{
public:
	/// <summary>
	/// Initialise the texture by using the renderer.
	/// </summary>
	explicit Texture2D(SDL_Renderer* renderer);

	/// <summary>
	/// Call the free function and set the renderer to nullptr.
	/// </summary>
	~Texture2D();

	/// <summary>
	/// Load the texture from a image path.
	/// </summary>
	bool LoadFromFile(const std::string& path);

	/// <summary>
	/// Delete the texture and set it to a nullptr.
	/// </summary>
	void Free();

	/// <summary>
	/// Render the texture on the renderer.
	/// </summary>
	void Render(Vector2D new_position, SDL_RendererFlip flip, double angle = 0.0) const;

	/// <summary>
	/// Returns the width of a texture.
	/// </summary>
	int GetWidth() const { return m_width; }

	/// <summary>
	/// Returns the height of a texture.
	/// </summary>
	int GetHeight() const { return m_height; }

private:
	// Texture and renderer members.
	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;

	// Width and height of the texture members.
	int m_width;
	int m_height;
};
#endif // _TEXTURE2D_H
// ----------------------------- TEXTURE2D CLASS ----------------------------- //
