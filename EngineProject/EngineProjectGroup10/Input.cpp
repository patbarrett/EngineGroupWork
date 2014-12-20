////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "input.h"


Input::Input()
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
	
	
}


Input::Input(const Input& other)
{
}


Input::~Input()
{
}

bool Input::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;

	

	// Store the screen size which will be used for positioning the mouse cursor.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Initialize the location of the mouse on the screen.
	m_mouseX = 0;
	m_mouseY = 0;

	// Initialize the main direct input interface.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Initialize the direct input interface for the keyboard.
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the keyboard to not share with other programs.
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if(FAILED(result))
	{
		return false;
	}

	// Now acquire the keyboard.
	result = m_keyboard->Acquire();
	if(FAILED(result))
	{
		return false;
	}

	// Initialize the direct input interface for the mouse.
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Set the data format for the mouse using the pre-defined mouse data format.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if(FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the mouse to share with other programs.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if(FAILED(result))
	{
		return false;
	}

	// Acquire the mouse.
	result = m_mouse->Acquire();
	if(FAILED(result))
	{
		return false;
	}

	
	
	

	return true;
}

void Input::Shutdown()
{
	// Release the mouse.
	if(m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// Release the keyboard.
	if(m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	
	// Release the main interface to direct input.
	if(m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return;
}

bool Input::Frame()
{
	bool result;


	// Read the current state of the keyboard.
	result = ReadKeyboard();
	if(!result)
	{
		return false;
	}

	// Read the current state of the mouse.
	result = ReadMouse();
	if(!result)
	{
		return false;
	}

	GamePadRefresh();
	

	

	// Process the changes in the mouse and keyboard.
	ProcessInput();

	return true;
}

bool Input::ReadKeyboard()
{
	HRESULT result;


	// Read the keyboard device.
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if(FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
		
	return true;
}

bool Input::ReadMouse()
{
	HRESULT result;


	// Read the mouse device.
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if(FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}



void Input::ProcessInput()
{
	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if(m_mouseX < 0)  { m_mouseX = 0; }
	if(m_mouseY < 0)  { m_mouseY = 0; }
	
	if(m_mouseX > m_screenWidth)  { m_mouseX = m_screenWidth; }
	if(m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }
	
	return;
}



bool Input::IsEscapePressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}

	return false;
}



void Input::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
	return;
}



void Input::GamepadInit()
{
	deadzoneX = 0.05f;
	deadzoneY = 0.02f;
}

void Input::GamepadInit( float dzX, float dzY)
{
	deadzoneX = dzX;
	deadzoneY = dzY;
}

int Input::GetGamepadPort()
{
	return cId+1;
}

XINPUT_GAMEPAD *Input::GetState()
{
	return &state.Gamepad;
}
bool Input::CheckConnection()
{
	int controllerId = -1;
 
	//loop thought the number of controllers and check if they are connected
		for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
		{
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));
 
				if (XInputGetState(i, &state) == ERROR_SUCCESS)
				controllerId = i;
		}
 
	 cId = controllerId;
 
	 //returns if we have connected controllers;
    return controllerId != -1;

}

bool Input::GamePadRefresh()
{
	if (cId == -1)
		CheckConnection();
 
	if (cId != -1)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));
			if (XInputGetState(cId, &state) != ERROR_SUCCESS)
			{
				cId = -1;
				return false;
			}
 
	//math required to keep track of the dead zone. 		
	float normLX = max(-1, (float) state.Gamepad.sThumbLX / 32767);
	float normLY = max(-1, (float) state.Gamepad.sThumbLY / 32767);
 
	leftStickX = (abs((long)normLX) < deadzoneX ? 0 : (abs((long)normLX) - deadzoneX) * (normLX / abs((long)normLX)));
	leftStickY = (abs((long)normLY) < deadzoneY ? 0 : (abs((long)normLY) - deadzoneY) * (normLY / abs((long)normLY)));
 
	if (deadzoneX > 0) 
		leftStickX *= 1 / (1 - deadzoneX);
	if (deadzoneY > 0) 
		leftStickY *= 1 / (1 - deadzoneY);
 
	float normRX = max(-1, (float) state.Gamepad.sThumbRX / 32767);
	float normRY = max(-1, (float) state.Gamepad.sThumbRY / 32767);
 
	rightStickX = (abs((long)normRX) < deadzoneX ? 0 : (abs((long)normRX) - deadzoneX) * (normRX / abs((long)normRX)));
	rightStickY = (abs((long)normRY) < deadzoneY ? 0 : (abs((long)normRY) - deadzoneY) * (normRY / abs((long)normRY)));
 
	if (deadzoneX > 0) 
		rightStickX *= 1 / (1 - deadzoneX);
	if (deadzoneY > 0) 
		rightStickY *= 1 / (1 - deadzoneY);
 
	leftTrigger = (float) state.Gamepad.bLeftTrigger / 255;
	rightTrigger = (float) state.Gamepad.bRightTrigger / 255;
 
	return true;
	}
	return false;
}

bool Input::IsButtonPressed(WORD button)
{
	return (state.Gamepad.wButtons & button) != 0;
}


