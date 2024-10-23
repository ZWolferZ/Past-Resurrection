// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _CONSTANTS_H
#define CONSTANTS_H
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- CONSTANTS ----------------------------- //

// Constants for the game
//Changed to enum because macros are bad
enum Constants
{
	// Screen Dimensions
	SCREEN_WIDTH = 800,
	SCREEN_HEIGHT = 480,
	FPS = 60,
	frameDelay = 1000 / FPS,
	movementSpeed = 100,
	enemyflyspeed = 25,
	crosshairSpeed = 300,
	theVoid = 1000,
	rightScreenBounds = 770,
	leftScreenBounds = -20,
	topScreenBounds = -20,
	bottomScreenBounds = 450,
	baselocation = 400,
	leftTowerLeftSide = 232,
	leftTowerRightSide = 332,
	rightTowerLeftSide = 446,
	rightTowerRightSide = 547
};

#endif // !_CONSTANTS_H
// ----------------------------- CONSTANTS ----------------------------- //
