#ifndef ACTION_CHANGE_BACKGROUND_H
#define ACTION_CHANGE_BACKGROUND_H

#include "Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

//Change Background Color Action class
class ActionChangeBackground : public Action
{
public:
	ActionChangeBackground(ApplicationManager* pApp);

	//Change background color
	virtual void Execute();

};

#endif