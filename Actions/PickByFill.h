#ifndef PICK_BY_FILL_H
#define PICK_BY_FILL_H

#include "./Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <string.h>

class PickByFill : public Action
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
	PickByFill(ApplicationManager* pApp);
	void Execute();
	void Select(Point P);
	bool IsThereAColor();
	void randomColor();
	string getRandomFigure();
	int NumOfColors();
};

#endif