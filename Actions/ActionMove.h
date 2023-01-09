#ifndef ACTION_MOVE_H
#define ACTION_MOVE_H

#include "Action.h"
#include "..\Figures\CSquare.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

//Add Square Action class
class ActionMove : public Action
{
public:
	ActionMove(ApplicationManager* pApp);

	//Move shape
	virtual void Execute();
	bool isInside(Point P);
};

#endif