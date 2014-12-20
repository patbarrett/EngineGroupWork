
class AudioC
{
//#include "AudioSystem.h"
#include <string>


public:

	AudioC(void);
	void setPath(std::string name);
	void setVolume(float v);
	void mute();
	int getPosition();
	void Play(int LoopCount);
	void Pause();
	void Resume();
	void Stop();
	~AudioC(void);
private:
	
	//irrklang::ISound* sound;
	float volume;
	std::string ChannelName;
	
};


