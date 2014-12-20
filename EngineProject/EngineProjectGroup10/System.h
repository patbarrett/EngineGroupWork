#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

#pragma once
#pragma comment(lib, "lua5.1.lib")

// PRE-PROCESSING DIRECTIVES //
// this reduces the size of the Win32 Header files and speeds up build time

#define WIN32_LEAN_AND_MEAN

// INCLUDES //
//included so we can use win32functions

#include <windows.h>


// MY CLASS INCLUDES 
//these are the systems that have been created so far, so we want them included in our engine

#include "input.h"
#include "graphics.h"
#include "EventManager.h"
#include "AudioSystem.h"
#include "ScriptManager.h"


class System
{
public:
	System();//default constructer
	System(const System&);//copy constructer
	~System();//destructor

	bool Initialize();//initializer
	void Shutdown();//engine shutdown
	void Run();//engine run

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();//where all the processing for the application is done
	void InitializeWindows(int&, int&);// this function actually builds the window
	void ShutdownWindows();
	

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	// pointers to the Input and graphics objects 
	Input* m_Input;
	Graphics* m_Graphics;
	EventManager* m_EventManager;
	AudioSystem* m_AudioSystem;
	ScriptManager *m_sciptManager;
};



static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


static System* ApplicationHandle = 0;

#endif