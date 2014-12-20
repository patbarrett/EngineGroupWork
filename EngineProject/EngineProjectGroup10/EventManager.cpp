#include "EventManager.h"

EventManager::EventManager()
{}

EventManager::~EventManager()
{
	for ( map<string, vector<EventFunctionPtr*>>::iterator iter = events.begin(); iter != events.end(); ++iter )
	{
		for (int i = 0; i < iter->second.size(); i++)
		{
			delete iter->second[i];
			iter->second[i] = NULL;
		}
		iter->second.clear();
	}
	events.clear();
}

void EventManager::addEventListener(string name, EventFunctionPtr* funcPtr)
{
	events[name].push_back(funcPtr);
}

void EventManager::removeEventListener(string name, EventFunctionPtr* funcPtr)
{
	map<string, vector<EventFunctionPtr*>>::iterator iter = events.find(name);
	
	if( iter != events.end() )
	{
		for (int i = 0; i < iter->second.size(); i++)
		{
			if (funcPtr == iter->second[i])
			{
				iter->second.erase(iter->second.begin() + i);

				if (iter->second.size() <= 0)
				{
					events.erase(iter);
					break;
				}
			}
		}
	}
}

void EventManager::dispatchEvent(Event* event)
{
	map<string, vector<EventFunctionPtr*>>::iterator iter = events.find(event->GetName());
	
	if(iter != events.end())
	{
		for (int i = 0; i < iter->second.size(); i++)
		{
			iter->second[i]->Invoke(event);
		}
		//delete input;
	}
}