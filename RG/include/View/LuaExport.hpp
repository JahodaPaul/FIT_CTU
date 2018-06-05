#pragma once

#include <sol.hpp>
#include <memory>

#include "View/SoundManager.hpp"

namespace RG { namespace View {
    class LuaExport {
        public:
            static void ExportSoundManager( sol::state & state
                    ,std::shared_ptr<SoundManager> soundManager
                    ,const char * type_name = "SoundManager"
                    ,const char * instance_name = "soundManager" );
        private:
    };

}}
