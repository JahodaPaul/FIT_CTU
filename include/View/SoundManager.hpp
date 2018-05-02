#pragma once

#include <SFML/Audio.hpp>

#include <string>
#include <set>
#include <pair>

class Path
{
public:
	std::string name;
	std::string path;
}

class SoundManager
{
public:

private:
	int m_countSounds;
	int m_lastActiveSound;
	int * m_volumeSounds;
	sf::Sound * m_sound;	
	sf::SoundBuffer * m_buffer;
	int m_sizeListOfSounds;
	int m_sizeListOfMusic;
	std::set<Path> m_listOfSounds;
	std::set<Path> m_listOfMusic;
	int m_globalVolumeSound;
	int m_globalVolumeMusic;

public:
	SoundManager();	
	~SoundManager();
	bool PlaySound(std::string name, int volume);
	bool PlayMusic(std::string name, int volume);
	bool SoundStop();
	bool SetSoundVolume(bool change);
	bool SetMusicVolume(bool change);
private:
	// zjistim pri implementaci jeslti budu potrebovat

	
};