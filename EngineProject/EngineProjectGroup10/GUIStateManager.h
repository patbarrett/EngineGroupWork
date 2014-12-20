#ifndef _GUIStateManager_H_
#define _GUIStateManager_H_

#include <iostream>
#include <string>

using namespace std;

class GUIStateManager
{
public:
	//Constructor & Destructure
	GUIStateManager();
	~GUIStateManager();

	enum States
	{
		Up, 
		Down, 
	};

	string currentState;
	//Getter & Setter for State
	string GetState();
	void SetState(States _s);
};

#endif