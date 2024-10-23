// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _CROSSHAIR_H
#define CROSSHAIR_H
#include "GameObject.h"
#include "Character.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "constants.h"
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- CROSSHAIR CLASS ----------------------------- //
class Crosshair : public GameObject // Inherit from GameObject
{
public:
	/// <summary>
	/// Initialise the crosshair with a renderer, an image-path and a start position.
	/// </summary>
	Crosshair(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);

	/// <summary>
	/// Overrided deconstructor pulls from gameobject class.
	/// </summary>
	~Crosshair() override;

	/// <summary>
	/// Overrided renderer pulls from gameobject class.
	/// </summary>
	void Render() override;

	/// <summary>
	/// Overrided update pulls from gameobject class, in this case, holds the movement logic.
	/// </summary>
	void Update(float deltaTime, SDL_Event e) override;

private:
	// Movement booleans
	bool m_moving_right;
	bool m_moving_left;
	bool m_moving_up;
	bool m_moving_down;

	/// <summary>
	/// Moves the crosshair left by using deltatime and a constant.
	/// </summary>
	void MoveLeft(float deltaTime);

	/// <summary>
	/// Moves the crosshair right by using deltatime and a constant.
	/// </summary>
	void MoveRight(float deltaTime);

	/// <summary>
	/// Moves the crosshair up by using deltatime and a constant.
	/// </summary>
	void MoveUp(float deltaTime);

	/// <summary>
	/// Moves the crosshair down by using deltatime and a constant.
	/// </summary>
	void MoveDown(float deltaTime);
};

#endif // _CROSSHAIR_H
// ----------------------------- CROSSHAIR CLASS ----------------------------- //
