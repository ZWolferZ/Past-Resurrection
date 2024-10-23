// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _COMMONS_H
#define COMMONS_H
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- STRUCTURES ----------------------------- //

// Vector2D structure
struct Vector2D
{
	float x = 0.0f;
	float y = 0.0f;

	/// <summary>
	/// Function that initialise a vector2d as 0,0.
	/// </summary>
	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	/// <summary>
	/// Function that initialise a vector2d as defined values.
	/// </summary>
	Vector2D(const float initialX, const float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

// Screen Enum structure
enum SCREENS
{
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_LEVEL3,
	SCREEN_GAMEOVER,
	SCREEN_CONTROLS,
	SCREEN_UPGRADE
};

// Facing Enum structure
enum FACING
{
	FACING_LEFT,
	FACING_RIGHT
};

// Rect2D structure
struct Rect2D
{
	float x;
	float y;
	float width;
	float height;


	/// <summary>
	/// Function that initialise a Rect2D as defined values.
	/// </summary>
	Rect2D(const float x_pos, const float y_pos, const float width, const float height)
	{
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;
	}
};

#endif // !_COMMONS_H
// ----------------------------- STRUCTURES ----------------------------- //
