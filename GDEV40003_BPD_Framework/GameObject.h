// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SDL.h>
#include "Commons.h"
#include <iostream>
#include "Texture2D.h"

class Texture2D; // Forward declaration
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- GAMEOBJECT CLASS ----------------------------- //
class GameObject
{
public:
	/// <summary>
	/// Initialise a game object with a renderer, imagepath to a texture, circle collision radius and starting position.
	/// </summary>
	GameObject(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);

	/// <summary>
	/// Sets m_renderer to nullptr and deletes gameobject texture.
	/// </summary>
	virtual ~GameObject();

	/// <summary>
	/// Virtual renderer that renders the texture of the gameobject.
	/// </summary>
	virtual void Render();

	/// <summary>
	/// Virtual update that parses gameobject updates.
	/// </summary>
	virtual void Update(float deltaTime, SDL_Event e);

	/// <summary>
	/// Returns the current position of the gameobject.
	/// </summary>
	Vector2D GetPosition() const;

	/// <summary>
	/// Sets the current position of the gameobject to a specified point.
	/// </summary>
	void SetPosition(Vector2D new_position);

	/// <summary>
	/// Returns the collision radius of the gameobject.
	/// </summary>
	float GetCollisionRadius() const;

	/// <summary>
	/// Returns the collision box of the texture used.
	/// </summary>
	virtual Rect2D GetCollisionBox() const;

protected:
	// Gameobject variables
	SDL_Renderer* m_renderer = nullptr;
	Vector2D m_position;
	Texture2D* m_texture = nullptr;
	float m_collision_radius;
};

#endif // _GAMEOBJECT_H
// ----------------------------- GAMEOBJECT CLASS ----------------------------- //
