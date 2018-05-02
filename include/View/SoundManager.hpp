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

// (vojta) Cokoliv kde je position muzes prozatim v implementaci ignorovat
// (vojta) Dej mi moznost prehrat jeden zvuk v jednu chvili vickrat, mam pocit ze s tvym setem by to ted nefungovalo
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
    // (vojta) Konstruktor by asi mohl brat maximum naraz prehravanych zvuku
	SoundManager( unsigned int maxSounds = 20 );	
	~SoundManager();
    // (vojta) nastav pozici posluchace
    void setListenerPosition( const sf::Vector3f & position );
    // (vojta) vrat identifikator zvuku ( jedinecny v ramci aktualne prehravanych zvuku )
	int PlaySound(std::string name, int volume = 50, const sf::Vector3f & position = {0,0,0} );
	int PlaySound(std::string name, const sf::Vector3f & position = {0,0,0}, int volume = 50 );
    // (vojta) nastav pozici pro zvuk kde id je to co vrati PlaySound()
    void setSoundPosition( int id );
    // (vojta) Prehraj jednu pisnicku
	bool PlayMusic(std::string name, int volume = 50);
    // (vojta) preskoc na dalsi pisnicku
	bool PlayNextMusic( int volume = 50);
    // (vojta) tato funkce zacne prehravat vsechny pisnicky ve smycce
	bool PlayMusic( int volume = 50);
	bool SoundStop();
    // (vojta) Pokud máš Sound stop, tak chceš asi i music stop a asi i resume
	bool MusicStop();
	bool SoundResume();
	bool MusicResume();
    // (vojta) změna bool -> int
	bool SetSoundVolume(int change);
	bool SetMusicVolume(int change);
private:
	// zjistim pri implementaci jeslti budu potrebovat
    // (vojta) v private casti si delej co chces
};
