#include "ActionSelect.h"

ActionSelect::ActionSelect(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionSelect::Execute()
{
	Point P;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//Get point to select/unselect a shape
	pGUI->PrintMessage("Click on a shape to Select/Unselect it");

	while (1)
	{
		//Read point and store in point P
		if (!pGUI->GetPointClicked(P.x, P.y)) {
			pManager->SetPoint(P.x, P.y);
			return;
		}

		if (P.x > 1070 && P.x < 1200 && P.y < UI.ToolBarHeight) //Exit Action
		{
			pGUI->ClearStatusBar();
			break;
		}

		if (P.y > UI.ToolBarHeight && P.y < UI.height - UI.StatusBarHeight)
			pManager->SelectFigure(P);
		pManager->UpdateInterface();
	}
	pManager->ResetPoint();
}