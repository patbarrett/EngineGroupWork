#include "Channel.h"


Channel::Channel(void)
{
	
}

void Channel::setVolume(float v)
{
	sound->setVolume(v);
}

void Channel::mute()
{
	sound->setVolume(0);

}
int Channel::getPosition()
{
	return sound->getPlayPosition();
}

void Channel::Play(bool isLooped)
{
	sound->setIsLooped(isLooped);
}

void Channel::Pause()
{
	sound->setIsPaused(true);
}
void Channel::Resume()
{
	sound->setIsPaused(false);
}
void Channel::Stop()
{
	sound->stop();
	sound->drop();
}


Channel::~Channel(void)
{
	sound->drop();
}
