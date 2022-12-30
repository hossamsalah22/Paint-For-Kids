#ifndef ACTION_SELECT_H
#define ACTION_SELECT_H

#include "Action.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

//Select Figure(s) Action class
class ActionSelect : public Action
{
public:
	ActionSelect(ApplicationManager* pApp);

	//Add Square to the ApplicationManager
	virtual void Execute();

};

#endif