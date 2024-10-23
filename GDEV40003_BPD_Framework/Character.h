// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _CHARACTER_H
#define CHARACTER_H
#include "GameObject.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "constants.h"
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- CHARACTER CLASS ----------------------------- //
class Character : public GameObject // Inherit from GameObject
{
public:
	/// <summary>
	/// Initialise the character with a renderer, an image-path and a start position.
	/// </summary>
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);

	/// <summary>
	/// Overrided deconstructor pulls from gameobject class.
	/// </summary>
	~Character() override;

	/// <summary>
	/// Overrided Renderer pulls from gameobject class, in this case, holds the character direction logic.
	/// </summary>
	void Render() override;

	/// <summary>
   /// Overrided deconstructor pulls from gameobject class, in this case, holds the character movement logic.
   /// </summary>
	void Update(float deltaTime, SDL_Event e) override;

private:
	// Character direction enum
	FACING m_facing_Direction;

	// Character movement bools
	bool m_moving_right;
	bool m_moving_left;

	/// <summary>
	///Moves the character left by using deltatime and a constant.
	/// </summary>
	void MoveLeft(float deltaTime);

	/// <summary>
	/// Moves the character right by using deltatime and a constant.
	/// </summary>
	void MoveRight(float deltaTime);
};

#endif // _CHARACTER_H
// ----------------------------- CHARACTER CLASS ----------------------------- //
