// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _COLLISIONS_H
#define COLLISIONS_H
#include "Commons.h"
#include "GameObject.h"
#include "Character.h"

class Character; // Forward Declaration
// ----------------------------- INCLUDES ----------------------------- //


// ----------------------------- COLLISIONS CLASS ----------------------------- //
class Collisions
{
public:
	/// <summary>
	/// Singleton instance of the collision class.
	/// </summary>
	static Collisions* Instance();

	/// <summary>
	/// Delete the instance of the singleton.
	/// </summary>
	~Collisions();

	/// <summary>
	/// Circle distance calculation that returns a true if gameobjects are overlapping.
	/// </summary>
	static bool Circle(GameObject* a, GameObject* b);

	/// <summary>
	/// Box distance calculation that returns a true if Rect2d's are overlapping.
	/// </summary>
	static bool Box(Rect2D rect1, Rect2D rect2);

private:
	/// <summary>
	/// Default class constructor.
	/// </summary>
	Collisions();

	// Instance of the singleton.
	static Collisions* m_instance;
};
#endif // _COLLISIONS_H
// ----------------------------- COLLISIONS CLASS ----------------------------- //
