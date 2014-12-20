//Engine Project Group 10
//Patrick Barrett
//Kent Li
//Colin Rumball

#include "system.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	System* EngineSystem;
	bool result;
	
	
	// Create the system object.
	EngineSystem = new System;
	if(!EngineSystem)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = EngineSystem->Initialize();
	if(result)
	{
		EngineSystem->Run();
	}

	// Shutdown and release the system object.
	EngineSystem->Shutdown();
	delete EngineSystem;
	EngineSystem = 0;

	return 0;
}