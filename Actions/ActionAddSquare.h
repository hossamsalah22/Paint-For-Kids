#ifndef ACTION_ADD_SQUARE_H
#define ACTION_ADD_SQUARE_H

#include "Action.h"
#include "..\Figures\CSquare.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

//Add Square Action class
class ActionAddSquare: public Action
{
public:
	ActionAddSquare(ApplicationManager *pApp);
	
	//Add Square to the ApplicationManager
	virtual void Execute() ;
	
};

#endif