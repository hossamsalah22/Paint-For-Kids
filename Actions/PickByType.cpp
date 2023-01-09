#include "PickByType.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

GUI* pGUI;
int FigAvailList[3] = { 0,0,0 };
int num;
CFigure* tempFigList[200];//not done yet


PickByType::PickByType(ApplicationManager* pApp) :Action(pApp)
{
	pGUI = pManager->GetGUI();
	num = -1;
	pManager->getFigureList(FigAvailList);
	int flag = 0;
	if (FigAvailList[0] == 1 || FigAvailList[1] == 1 || FigAvailList[2] == 1)
		while (flag == 0) {
			num = rand() * 10 % 3;
			if (FigAvailList[num] == 1)
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

}

void PickByType::Execute()
{
	
	Point P;

	while (1)
	{

		pManager->UpdateInterface();
		//Read point and store in point P
		if (!pGUI->GetPointClicked(P.x, P.y)) {
			pManager->SetPoint(P.x, P.y);
			return;
		}
		if (P.y > UI.ToolBarHeight && P.y < UI.height - UI.StatusBarHeight)
			pManager->SelectFigure(P);
	}


}