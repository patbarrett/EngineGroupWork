#ifndef EVENT_H
#define EVENT_H

#include <iostream>

using namespace std;

class Event
{
private:
	string name;

public:
	Event(void) {}

	Event(string _name)
	{
		name = _name;
	}
	inline string GetName() {return name;};
};

#endif