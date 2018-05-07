#pragma once

#include <SFML/Audio.hpp>

#include <string>
#include <map>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>


/**	* \brief
This class work with audio data.*/
class SoundManager
{
public:

private:
	sf::Music m_music;

	/**	* \brief
	How many songs can be played at one time.*/
	int m_countSounds;

	/**	* \brief
	The index in the field on which I assigned the last sound request*/
	int m_lastActiveSound;

    /**	* \brief
	The field of Sounds.*/
    std::vector<sf::Sound> m_sound;

    /**	* \brief
	The field of data sounds, which are playing.*/
    std::vector<sf::SoundBuffer> m_buffer;

	/**	* \brief
	The number of sounds which are available. */
	int m_sizeListOfSounds;
	
	/**	* \brief
	The number of music which are available.*/
	int m_sizeListOfMusic;
	
	/**	* \brief
	Here are safe name of sound and file path.*/
	std::map<std::string, std::string> m_listOfSounds;

	/**	* \brief
	Here are safe name of music and file path.*/
	std::map<std::string, std::string> m_listOfMusic;

	/**	* \brief
	Iterator on music, which is actually playing. */
	std::map<std::string, std::string>::iterator m_activeMusic;

	/**	* \brief
	Loud of sounds  */
	int m_globalVolumeSound;
	
	/**	* \brief
	Loud of music. */
	int m_globalVolumeMusic;

	/**	* \brief
	For read list of sound and music from file */
	std::ifstream m_file;

public:
    /**	* \brief
	Construktor, you can set how many song can be plaing on same time. */
	SoundManager( unsigned int maxSounds = 20 );	
    
    // (vojta) nastav pozici posluchace
    void setListenerPosition( const sf::Vector3f & position );

    /**	* \brief
	Plays the sound by name of sound. */
	int PlaySound(std::string name, int volume = 50, const sf::Vector3f & position = {0,0,0} );
	//int PlaySound(std::string name, const sf::Vector3f & position = {0,0,0}, int volume = 50 );
    
    // (vojta) nastav pozici pro zvuk kde id je to co vrati PlaySound()
    void setSoundPosition( int id, sf::Vector3f & position );
    
    /**	* \brief
    Plays the music by name of music. */
	bool PlayMusic(std::string name, int volume = 50);

    /**	* \brief
    Plays the next music on the list. */
	bool PlayNextMusic( int volume = 50);

    /**	* \brief
    Plays the first music on the list. */
	bool PlayMusic( int volume = 50, bool repeat = true);

	 /**	* \brief
    Stop playing all the sounds. */
	bool SoundStop();

     /**	* \brief
    Stop playing the music. */
    bool MusicStop();

	 /**	* \brief
    Continue of playing all the sounds. */
	bool SoundResume();

	 /**	* \brief
    Continue of playing music. */
	bool MusicResume();
    
	 /**	* \brief
    Setting  of loud all sounds. */
	bool SetSoundVolume(int change);

	 /**	* \brief
    Setting of loud music */
	bool SetMusicVolume(int change);

	bool IsMusicPlaying() const;
private:
	 /**	* \brief
    Read list of music and sound. If flag is true, write the data on the list of sound, if false write data on the list of music. */
	bool ReadFile(std::string path, bool flag);
	
	/**	* \brief
    Check that any sound of music volume have dropped below zero or above 100 */
	int control(int volume);
};
