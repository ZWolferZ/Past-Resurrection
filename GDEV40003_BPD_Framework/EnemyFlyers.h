// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _ENEMYFLYERS_H
#define ENEMYFLYERS_H
#include "GameObject.h"
#include "constants.h"
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- ENEMYFLYERS CLASS ----------------------------- //
class EnemyFlyers : public GameObject // Inherit from GameObject
{
public:
	/// <summary>
	/// Initialise the enemy flyer with a renderer, an image-path and a start position.
	/// </summary>
	EnemyFlyers(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);

	/// <summary>
	/// Overrided deconstructor pulls from gameobject class.
	/// </summary>
	~EnemyFlyers() override;

	/// <summary>
	/// Overrided renderer pulls from gameobject class, in this case, holds the directional facing logic.
	/// </summary>
	void Render() override;

	/// <summary>
	/// Overrided update pulls from gameobject class, in this case, holds the animation logic.
	/// </summary>
	void Update(float deltaTime, SDL_Event e) override;

	/// <summary>
	/// Moves the enemy flyer left by using deltatime and a constant.
	/// </summary>
	void MoveLeft(float deltaTime);

	/// <summary>
	/// Moves the enemy flyer right by using deltatime and a constant.
	/// </summary>
	void MoveRight(float deltaTime);

	/// <summary>
	/// Returns the collision box of the texture used.
	/// </summary>
	Rect2D GetCollisionBox() const override;

	/// <summary>
	/// Returns m_enemyIsHit bool.
	/// </summary>
	bool ReturnHit() const { return m_enemyIsHit; }

	// I forgot how to make a setter for a second and only remembered after implmentation so ummmm... here's two setters :(.

	/// <summary>
	/// Sets m_enemyIsHit bool to true.
	/// </summary>
	void SetHitTrue() { m_enemyIsHit = true; }

	/// <summary>
	/// Sets m_enemyIsHit bool to false.
	/// </summary>
	void SetHitFalse() { m_enemyIsHit = false; }

private:
	// Facing direction of the enemy flyer.
	FACING m_facing_Direction;

	// Movement booleans.
	bool m_moving_right;
	bool m_moving_left;

	// Animation boolean.
	bool m_enemyIsHit = false;
};

#endif // !_ENEMYFLYERS_H
// ----------------------------- ENEMYFLYERS CLASS ----------------------------- //
