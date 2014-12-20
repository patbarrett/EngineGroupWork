#include "AudioSystem.h"


AudioSystem::AudioSystem(void)
{
}

void AudioSystem::Initialize()
{
	engine = irrklang::createIrrKlangDevice();
	
}


Channel* AudioSystem::PlaySound(const char* path)
{
	
	

	irrklang::ISound* snd = engine->play2D("song.mp3",true);
	
	Channel* m_Channel = new Channel();
	m_Channel->sound = snd;
	//activeChannels.push_back(
	activeChannels.push_back(m_Channel);
	return(m_Channel);

}


void AudioSystem::StopAllSounds()
{
	engine->stopAllSounds();
}

void AudioSystem::stopSound(Channel* Channel)
{
	//Channel->StopSound();
}

void AudioSystem::PauseAllSounds()
{
	engine->setAllSoundsPaused(true);

}

void AudioSystem::ResumeAllSounds()
{
	engine->setAllSoundsPaused(false);
}

void AudioSystem::MuteAll()
{
	engine->setSoundVolume(0);
}

void AudioSystem::UnMute()
{
	engine->setSoundVolume(1.0f);
}



AudioSystem::~AudioSystem(void)
{
	
}
