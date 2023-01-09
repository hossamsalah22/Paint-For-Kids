#include "ActionMove.h"

ActionMove::ActionMove(ApplicationManager* pApp) :Action(pApp)
{}

//Check whether the shape is inside the drawing area
bool ActionMove::isInside(Point P)
{
	return (P.x > 0 && P.x < UI.width&& P.y > UI.ToolBarHeight && P.y < UI.height - UI.StatusBarHeight);
}

//Execute the action
void ActionMove::Execute()
{
	Point P1, P2, P3, P4;
	bool validAction = true;
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	
	pGUI->PrintMessage("Click anywhere in drawing mode to take reference point");

	int selectedIndex = pManager->getSelectedFigure();
	if (selectedIndex != -1) {
		CFigure* selectedShape = pManager->GetFigure();
		P3 = selectedShape->GetP1();
		P4 = selectedShape->GetP2();

		if (!pGUI->GetPointClicked(P1.x, P1.y)) {
			pManager->SetPoint(P1.x, P1.y);
			return;
		}

		if (!(P1.y > UI.ToolBarHeight && P1.y < UI.height - UI.StatusBarHeight)) {
			validAction = false;
		}

		Point tempP1, tempP2;
		if (validAction)
		{
			P2 = P1;
			int deltaX, deltaY;
			while (pGUI->IsButtonUp(P2.x, P2.y))
			{
				deltaX = P2.x - P1.x;
				deltaY = P2.y - P1.y;

				tempP1.x = P3.x + deltaX;
				tempP1.y = P3.y + deltaY;
				tempP2.x = P4.x + deltaX;
				tempP2.y = P4.y + deltaY;

				selectedShape->Move(tempP1, tempP2);

				if (isInside(tempP1) && isInside(tempP2))
				{
					pGUI->PrintMessage("Click anywhere in drawing mode to set the new position");
					validAction = true;
				}
				else
				{
					pGUI->PrintMessage("Error: Shape borders must be inside the drawing area!");
					pGUI->CreateDrawToolBar();
					validAction = false;
				}
				Sleep(1000 / 60);
				pManager->UpdateInterface();
			}
		}
		pGUI->CreateDrawToolBar();
		pGUI->ClearStatusBar();
		pGUI->ClearDrawArea();
		if (!validAction)
			selectedShape->Move(P3, P4);
	}
	else {
		pGUI->PrintMessage("Select One Shape before you can perform this action");
	}
	pManager->ResetPoint();
}