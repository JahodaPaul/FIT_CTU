#include "View/SoundManager.hpp"

int main()
{
	SoundManager a;
	a.PlayMusic();
	int tmp;
	
	while(true)
	{
		std::cin >> tmp;

		if(tmp == 1 )
			a.PlayNextMusic();

		if(tmp ==2)
			a.MusicStop();

		if(tmp ==3)
			a.MusicResume();

		if(tmp == 4)
			a.SetMusicVolume(10);

		if(tmp ==5)
			a.SetMusicVolume(-10);

		if(tmp == 6)
		{
			std::string sound;
			std::cin >> sound;
			a.PlaySound(sound, 75);
		}

		if(tmp == 7)
			a.SoundStop();

		if(tmp == 8)
			a.SoundResume();
	}

	return 0;
}
