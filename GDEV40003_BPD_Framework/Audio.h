// ----------------------------- INCLUDES ----------------------------- //
#pragma once
#ifndef _AUDIO_H
#define AUDIO_H
#include "SDL.h"
#include "SDL_mixer.h"
#include <string>
#include <iostream>
// ----------------------------- INCLUDES ----------------------------- //

// ----------------------------- AUDIO CLASS ----------------------------- //
class Audio
{
public:
	/// <summary>
	/// Initialise the audio system with a channel and mix chunk.
	/// </summary>
	Audio();

	/// <summary>
	/// Deletes the audio system and mix chunk.
	/// </summary>
	~Audio();

	/// <summary>
	/// Loads a sound file from a path (NEEDS TO A BE A WAV).
	/// </summary>
	bool LoadFromFile(const std::string& path);

	/// <summary>
	/// Play a sound by using the correct channel, mix chunk and number of loops.
	/// </summary>
	void Play(int channel, Mix_Chunk* chunk, int loops);

	/// <summary>
	/// Pause a sound by specifying the channel.
	/// </summary>
	void Pause(int channel);

	/// <summary>
	/// Set the volume of a channel by specifying the channel and the volume.
	/// </summary>
	void SetVolume(int channel, int volume);

	Mix_Chunk* m_chunk = nullptr;

private:
	int m_channel;
};

#endif // _AUDIO_H
// ----------------------------- AUDIO CLASS ----------------------------- //
