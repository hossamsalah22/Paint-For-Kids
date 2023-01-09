#ifndef PICK_BY_FILL_H
#define PICK_BY_FILL_H

#include "./Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

class PickByFill : public Action
{
protected:
	GUI* pGUI;
	int FigAvailList[3];
	int FigID;
	int CorrectCounter;
	CFigure* FigList[200];
	int FigCount;
public:
	PickByFill(ApplicationManager* pApp);
	void Execute();
	void Select(Point P);
};

#endif