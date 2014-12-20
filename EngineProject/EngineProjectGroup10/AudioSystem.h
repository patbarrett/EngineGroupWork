#pragma once
#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H


#include "Channel.h"
#include "SoundResource.h"
#include "include\irrKlang.h"

#pragma( lib, "irrKlang.lib")


#include<stdio.h>
#include<vector>
#include<string>

using namespace std;

class AudioSystem
{
public:
	
	


	vector<Channel*>activeChannels;
	
	AudioSystem(void);
	~AudioSystem(void);
	void Initialize();
	void Update( float dt);
	Channel* PlaySound( const char* path);
	void stopSound(Channel* Channel);
	void StopAllSounds();
	//void stopSoundsofType(AudioType Type)
	//void setVolumeOfType(AudioType Type, float Volume)
	void PauseAllSounds();
	void ResumeAllSounds();
	void MuteAll();
	void UnMute();
private:
	
	irrklang::ISoundEngine* engine;
	
};
#endif

