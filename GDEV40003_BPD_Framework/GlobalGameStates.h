// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef GLOBALGAMESTATES_H
#define GLOBALGAMESTATES_H
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- EXTERNALS ----------------------------- //

// Now I know that using externals is bad practice, I can see that, but they remain a pretty easy way to share variables between files without having to pass them around as parameters.
// I will try to avoid using them in the future, but for now, this is not the case.

// The examiners when they see my list of externals: https://www.youtube.com/watch?v=bOuc02gPmBw

// Global Game States
extern int g_highScore;
extern int g_score;
extern bool g_mainMenu;
extern bool g_playerconfirmation;
extern bool g_levelComplete;
extern bool g_controls;
extern bool g_levelOne;
extern bool g_levelTwo;
extern bool g_levelThree;
extern bool g_gameOver;
extern bool g_continue;
extern bool g_quit;

// Player Upgrades
extern bool g_playerHealthUpgrade1;
extern bool g_playerHealthUpgrade2;
extern bool g_playerHealthUpgrade3;

// Base Upgrades
extern bool g_baseHealthUpgrade1;
extern bool g_baseHealthUpgrade2;
extern bool g_baseHealthUpgrade3;

// Player Health and Base Health
extern int g_maxplayerHealth;
extern int g_maxbaseHealth;
#endif // GLOBALGAMESTATES_H
// ----------------------------- EXTERNALS ----------------------------- //
