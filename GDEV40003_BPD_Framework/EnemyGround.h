// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _ENEMYGROUND_H
#define ENEMYGROUND_H
#include "GameObject.h"
#include "constants.h"
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- ENEMYGROUND CLASS ----------------------------- //
class EnemyGround : public GameObject // Inherit from GameObject.
{
public:
	/// <summary>
	/// Initialise the enemy  with a renderer, an image-path and a start position.
	/// </summary>
	EnemyGround(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);

	/// <summary>
	/// Overrided deconstructor pulls from gameobject class.
	/// </summary>
	~EnemyGround() override;

	/// <summary>
	/// Overrided renderer pulls from gameobject class, in this case, holds the directional facing logic.
	/// </summary>
	void Render() override;

	/// <summary>
	/// Overrided update pulls from gameobject class, in this case, holds the animation logic.
	/// </summary>
	void Update(float deltaTime, SDL_Event e) override;

	/// <summary>
	/// Moves the enemy left by using deltatime and a constant.
	/// </summary>
	void MoveLeft(float deltaTime);

	/// <summary>
	/// Moves the enemy right by using deltatime and a constant.
	/// </summary>
	void MoveRight(float deltaTime);

	/// <summary>
	/// Returns the collision box of the texture used.
	/// </summary>
	Rect2D GetCollisionBox() const override;

private:
	// Facing direction of the enemy.
	FACING m_facing_Direction;

	// Movement booleans.
	bool m_moving_right;
	bool m_moving_left;
};

#endif // !_ENEMYGROUND_H
// ----------------------------- ENEMYGROUND CLASS ----------------------------- //
