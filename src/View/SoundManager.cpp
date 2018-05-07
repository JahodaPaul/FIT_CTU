#include "View/SoundManager.hpp"

SoundManager::SoundManager(unsigned int maxSounds ) :
    m_sound( maxSounds ),
    m_buffer( maxSounds )
{
    m_countSounds = maxSounds;
    m_lastActiveSound = 0;
    m_globalVolumeSound = 0;
    m_globalVolumeMusic = 0;
        
    ReadFile("../ListOfSound.txt", true);
    ReadFile("../ListOfMusic.txt", false);

    m_activeMusic = m_listOfMusic.begin();
}

void SoundManager::setListenerPosition( const sf::Vector3f & position ) {}

int SoundManager::PlaySound(std::string name, int volume, const sf::Vector3f & position )
{
    
    if(m_listOfSounds.find(name) == m_listOfSounds.end())
        return -1;

    m_lastActiveSound++;
    if(m_lastActiveSound == m_countSounds)
        m_lastActiveSound = 0;

    std::map<std::string, std::string>::iterator it;
    it = m_listOfSounds.find(name);
    m_buffer[m_lastActiveSound].loadFromFile(it->second);
    m_sound[m_lastActiveSound].setBuffer(m_buffer[m_lastActiveSound]);
    m_sound[m_lastActiveSound].setVolume(control(volume + m_globalVolumeSound));
    m_sound[m_lastActiveSound].play();
    return m_lastActiveSound;
}
/*
int SoundManager::PlaySound(std::string name, const sf::Vector3f & position, int volume ) {
    return PlaySound(name, volume, position);
}
*/
void SoundManager::setSoundPosition( int id, sf::Vector3f & position ) {}

bool SoundManager::PlayMusic(std::string name, int volume )
{
    if(m_listOfMusic.find(name) == m_listOfMusic.end())
        return false;

    m_music.stop();
    m_activeMusic = m_listOfMusic.find(name);
    m_music.openFromFile(m_activeMusic->second);
    m_music.setVolume(control(volume + m_globalVolumeMusic));
    m_music.play();
    return true;
}

bool SoundManager::PlayNextMusic( int volume )
{
    if(m_sizeListOfMusic == 0)
        return false;

    ++m_activeMusic; 
    if(m_activeMusic == m_listOfMusic.end())
        m_activeMusic = m_listOfMusic.begin();    
          
    PlayMusic(m_activeMusic->first, volume);
    return true;
}

bool SoundManager::PlayMusic( int volume, bool repeat ) 
{    
    if(m_sizeListOfMusic == 0)
        return false;

    std::string tmp = m_activeMusic->second;
    
    m_music.openFromFile(tmp);
    int tmp_volume = control(volume + m_globalVolumeMusic);
    m_music.setVolume(tmp_volume);
    m_music.setLoop(repeat);
    m_music.play();
    return true;
}

bool SoundManager::SoundStop() {
    for(int i = 0; i < m_countSounds; i++)
        m_sound[i].pause();

    return true;
}

bool SoundManager::MusicStop()
{
    m_music.pause();
    return true;
}

bool SoundManager::SoundResume() {
    for(int i = 0; i < m_countSounds; i++)
        m_sound[i].play();
    return true;
}

bool SoundManager::MusicResume()
{
    if(IsMusicPlaying())
        return false;

    m_music.play();
    return true;
}

bool SoundManager::SetSoundVolume(int change)
{
    m_globalVolumeSound+=change;
    for(int i =0; i < m_countSounds; i++)
        m_sound[i].setVolume(control(m_sound[i].getVolume()+change));    
    return true;
}

bool SoundManager::SetMusicVolume(int change)
{
    MusicStop();
    int tmp;
    m_globalVolumeMusic+=change;
    tmp = m_music.getVolume() + change;
    tmp = control(tmp);
    m_music.setVolume(tmp);
    MusicResume();
    return true;
}

bool SoundManager::IsMusicPlaying() const
{
    if(m_music.getStatus() == 2)
        return true;
    else
        return false;
}

int SoundManager::control(int volume)
{
    if(volume > 100)
        volume = 100;

    if(volume < 0)
        volume = 0;

    return volume;
}

bool SoundManager::ReadFile(std::string path, bool flag)
{
    m_file.open(path);
    if(m_file.fail())
    {
        std::cout << "nenasel jsem cestu" << path << std::endl; // TODO logger
        return false;
    }
   /* else
        std::cout << "nasel jsem cestu" << path << std::endl; // TODO logger */
   
    std::string str_tmp, name, m_path, use;
    int read = 0;
       
    while(getline(m_file, str_tmp))
    {
        if(str_tmp[0] == '#')
            continue;

        read = 0;
        name.erase();        
        m_path.erase();
        use.erase();
        for(unsigned int i = 0; i < str_tmp.size(); i++)
        {
            char tmp = str_tmp[i];

            if(tmp == '"')
            {
                read++;
                continue;
            }

            if(read == 0 || read == 2 || read == 4)
                continue;

            if(read== 1)
                name.push_back(tmp);

            if(read == 3)
                m_path.push_back(tmp);

            if(read == 5)
                use.push_back(tmp);
        }        
                
        if(use == "disable")
            continue;
  
        if(flag)
        {
            m_listOfSounds.insert(std::pair<std::string, std::string>(name, m_path));            
            m_sizeListOfSounds++;
        }
        else
        {
            m_listOfMusic.insert(std::pair<std::string, std::string>(name, m_path));
            m_sizeListOfMusic++;
        }     
    }
    m_file.close();
    return true;
}
