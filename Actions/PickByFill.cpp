#include "PickByFill.h"

#include "..\ApplicationManager.h"
#include <cmath>
#include "..\GUI\GUI.h"

PickByFill::PickByFill(ApplicationManager* pApp) :Action(pApp)
{

}

void PickByFill::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	int FigList[3] = { 0,0,0 };
	int num = -1;
	pManager->getFigureList(FigList);
	int flag = 0;
	if (FigList[0] == 1 || FigList[1] == 1 || FigList[2] == 1)
		while (flag == 0) {
			num = rand() * 10 % 3;
			if (FigList[num] == 1)
			{
				flag = 1;
			}
		}
	pGUI->CreatePlayToolBar();
	if (num == 0) {
		pGUI->PrintMessage("remove all sqares to win");
	}
	else if (num == 1) {
		pGUI->PrintMessage("remove all circules to win");
	}
	else if (num == 2) {
		pGUI->PrintMessage("remove all hexagons to win");
	}
	else {
		pGUI->PrintMessage("no figures to select");
	}
	
	pManager->ResetPoint();
}