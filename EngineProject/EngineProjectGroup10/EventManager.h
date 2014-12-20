#ifndef EVTMGR_H
#define EVTMGR_H

#include <iostream>
#include <string>
#include "EventFunctionPtr.h"
#include "Event.h"
#include <map>
#include <vector>


using namespace std;

class EventManager
{
public:
	EventManager();
	~EventManager();

	void addEventListener(string name, EventFunctionPtr* funcPtr);
	void removeEventListener(string name, EventFunctionPtr* funcPtr);
	void dispatchEvent(Event* event);

private:
	map<string, vector<EventFunctionPtr*>> events;
};
#endif