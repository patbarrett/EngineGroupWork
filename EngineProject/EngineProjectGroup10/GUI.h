#ifndef _GUI_H_
#define _GUI_H_

#include "d3dclass.h"
#include "GUIElement.h"
#include "Input.h"
#include <map>
#include <vector>

using namespace std;

typedef vector<GUIElement> GuiElementVector; 

class GUI
{
public:
	//Constructor & Destructor
	GUI();
	~GUI();

	//
	GUIElement elements;
	

	//Vectors to scale GUI
	D3DXVECTOR3 Scale;
	D3DXVECTOR2 screenSize;

	//Input Manager Reference
	Input input;

	void Initialize();
	void Shutdown();
	void Update(float _dt);
	void Render();
	void AddElement(GUIElement E);
	void RemoveElement(GUIElement E);

	D3DXVECTOR3 GetScale ();
	void SetScale(D3DXVECTOR3 _scale);

private:

	GuiElementVector _elements;
};

#endif