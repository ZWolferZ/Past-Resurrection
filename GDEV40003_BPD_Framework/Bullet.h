// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _BULLET_H
#define BULLET_H
#include "GameObject.h"
#include "constants.h"
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- BULLET CLASS ----------------------------- //
class Bullet : public GameObject // Inherit from GameObject
{
public:
	/// <summary>
	/// Initialise the bullet projectile with a renderer, an image-path and a start/end position.
	/// </summary>
	Bullet(SDL_Renderer* renderer, const std::string& imagePath, Vector2D startPosition, Vector2D endPosition);

	/// <summary>
	/// Overrided deconstructor pulls from gameobject class.
	/// </summary>
	~Bullet() override;

	/// <summary>
	/// Overrided update pulls from gameobject class, in this case holds the bullet traveling logic.
	/// </summary>
	void Update(float deltaTime, SDL_Event e) override;

private:
	// Bullet variables
	float m_startpositionX;
	float m_startpositionY;
	float m_endpositionX;
	float m_endpositionY;
	float m_directionX;
	float m_directionY;
	float m_distance;
	float m_nextPositionX;
	float m_nextPositionY;
	float m_speed = 5.0f;
	bool m_deleteBullet = false;

	GameObject* m_bullet = nullptr;
};

#endif // _BULLET_H
// ----------------------------- BULLET CLASS ----------------------------- //
