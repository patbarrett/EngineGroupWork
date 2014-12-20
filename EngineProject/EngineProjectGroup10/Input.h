
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_



///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define DIRECTINPUT_VERSION 0x0800 //this is setting the version of direct input to version 8

/////////////
// LINKING //
/////////////
#pragma comment(lib, "dinput8.lib") //we need these to use direct input
#pragma comment(lib, "dxguid.lib")

// we also need this header 
//////////////
// INCLUDES //
//////////////
#include <dinput.h>
#include <XInput.h>


class Input
{

public:
	Input();
	Input(const Input&);
	~Input();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsEscapePressed();
	void GetMouseLocation(int&, int&);
	
	//game pad inits, one for default valuse, one for custom
    void GamepadInit();
	void GamepadInit(float dzX, float dzY);


	//values for different axis within the xbox controller.
	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;
	float leftTrigger;
	float rightTrigger;
 
	//get the portnumber that the gamepad is connected to
	int  GetGamepadPort();

	//pointer to controller state
	XINPUT_GAMEPAD *GetState();

	//make sure the controller is connected
	bool CheckConnection();

	//upate on the controller
	bool GamePadRefresh();

	//checking for button press on the controller
	bool IsButtonPressed(WORD);

	

private:


	//controller ID
	int cId;
	//controller state, checking if the controller is connected and what it is doing
	XINPUT_STATE state;
	//values for the deadzone
	float deadzoneX;
	float deadzoneY;

	bool ReadKeyboard();
	bool ReadMouse();
	bool ReadGamepad();
	void ProcessInput();

	// these are interfaces to to Direct input, keyboard, mouse and the gamepad;
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;
	

	// these are used to record the state of the actual input devices.
	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;
	
	

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
	
};


#endif