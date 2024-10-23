// ----------------------------- INCLUDE ----------------------------- //
#include "Audio.h"
// ----------------------------- INCLUDE ----------------------------- //

// Initialize the audio class
Audio::Audio()
{
	m_chunk = nullptr;
	m_channel = 0;
}

// Deinitialize the audio class
Audio::~Audio()
{
	// Delete the chunk if it exists
	if (m_chunk != nullptr)
	{
		Mix_FreeChunk(m_chunk);
		delete m_chunk;
		m_chunk = nullptr;
	}
}

// Load a sound effect from a file
bool Audio::LoadFromFile(const std::string& path)
{
	// Delete the chunk if it exists
	if (m_chunk != nullptr)
	{
		Mix_FreeChunk(m_chunk);
		delete m_chunk;
		m_chunk = nullptr;
	}
	// Try to load the sound effect
	m_chunk = Mix_LoadWAV(path.c_str());

	// Check if the sound effect was loaded successfully
	if (m_chunk == nullptr)
	{
		std::cout << "Failed to load sound effect! Error: " << Mix_GetError() << std::endl;
		return false;
	}

	// Return true if the sound effect was loaded successfully
	return true;
}

// Play the sound effect
void Audio::Play(int channel, Mix_Chunk* chunk, int loops)
{
	m_chunk = chunk;
	//Number of loops to loop the sound effect for, -1 is infinite loops
	loops = 0;
	// Play the sound effect
	m_channel = Mix_PlayChannel(channel, chunk, loops);
}

// Stop the sound effect
void Audio::Pause(int channel)
{
	m_channel = channel;
	Mix_Pause(channel);
}

// Adjust the volume of the sound effect
void Audio::SetVolume(int channel, int volume)
{
	m_channel = channel;
	Mix_Volume(channel, volume);
}
