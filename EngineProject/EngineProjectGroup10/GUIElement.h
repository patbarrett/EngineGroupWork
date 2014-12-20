#ifndef _GUIElement_H_
#define _GUIElement_H_

using namespace std;

class GUIElement
{
public:
	GUIElement();
	~GUIElement();

	void Initialize();
	void Update(float _dt);
	void Shutdown();
	void Render();
	//Gets which elements are rendered over each other
	void GetZOrder();

};

#endif