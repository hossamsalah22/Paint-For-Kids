#ifndef ACTION_CHANGE_COLOR_H
#define ACTION_CHANGE_COLOR_H

#include "Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

//Change Color Action class
class ActionChangeColor : public Action
{
public:
	ActionChangeColor(ApplicationManager* pApp);

	//Change color of figure(s)
	virtual void Execute();

};

#endif