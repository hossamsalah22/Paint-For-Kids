#ifndef PICK_BY_BOTH_H
#define PICK_BY_BOTH_H

#include "./Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <string.h>

class PickByBoth : public Action
{
protected:
	GUI* pGUI;
	int FigAvailList[3];
	int FigID;
	int CorrectCounter;
	CFigure* FigList[200];
	int FigCount;
	color pickColor;
	string pickColorString;
	bool fillFlag;
	int colorCounter;
	CFigure* colorList[200];
public:
	PickByBoth(ApplicationManager* pApp);
	void Execute();
	void Select(Point P);
	bool IsThereAColor();
	//void randomColor();
	void getRandomFigure();
	int NumOfColors();
};

#endif