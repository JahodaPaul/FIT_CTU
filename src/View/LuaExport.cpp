#include "View/LuaExport.hpp"
#include "common.hpp"

namespace RG { namespace View {
    void LuaExport::ExportSoundManager( sol::state & state, std::shared_ptr<SoundManager> soundManager, const char * type_name, const char * instance_name ) {
        mainLog.Info( "Exporting SoundManger to Lua." );
        sol::table view = state.create_named_table("View");

        view.new_usertype<SoundManager>(type_name,
                "setListenerPosition", &SoundManager::setListenerPosition,
                "PlaySound", &SoundManager::PlaySound,
                "setSoundPosition", &SoundManager::setSoundPosition,
                "PlayMusic", static_cast<bool(SoundManager::*)(std::string,int)>(&SoundManager::PlayMusic),
                "PlayNextMusic", &SoundManager::PlayNextMusic,
                ///*"PlayNextMusic", &SoundManager::PlayNextMusic,*/
                "SoundStop", &SoundManager::SoundStop,
                "MusicStop", &SoundManager::MusicStop,
                "SoundResume", &SoundManager::SoundResume,
                "MusicResume", &SoundManager::MusicResume,
                "SetSoundVolume", &SoundManager::SetSoundVolume,
                "SetMusicVolume", &SoundManager::SetMusicVolume,
                "IsMusicPlaying", &SoundManager::IsMusicPlaying
                );

        view[instance_name] = soundManager;
    }
}}
