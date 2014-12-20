#pragma once

#include "include\irrKlang.h"

#pragma( lib, "irrKlang.lib")


#include <string>
class Channel
{
public:
	Channel(void);
	void setVolume(float v);
	void mute();
	int getPosition();
	void Play(bool isLooped);
	void Pause();
	void Resume();
	void Stop();
	~Channel(void);

	irrklang::ISound* sound;

private:

	

};

