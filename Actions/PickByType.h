#ifndef PICK_BY_TYPE_H
#define PICK_BY_TYPE_H

#include "./Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

class PickByType : public Action
{
protected:
	GUI* pGUI;
	int FigAvailList[3];
	int FigID;
	int CorrectCounter;
	CFigure* FigList[200];
	int FigCount;
public:
	PickByType(ApplicationManager* pApp);
	void Execute();
	void Select(Point p);
};

#endif