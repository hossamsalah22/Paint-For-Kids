#include "ActionAddSquare.h"

ActionAddSquare::ActionAddSquare(ApplicationManager * pApp):Action(pApp)
{}

//Execute the action
void ActionAddSquare::Execute()
{
	Point P1, P2;
	bool validAction;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = pGUI->getCrntFillStatus();	//default is not filled
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	while (1)
	{
		validAction = true;
		//Step 1 - Read Square data from the user
		pGUI->PrintMessage("New Square: Click at first point");
		//Read 1st point and store in point P1
		pGUI->GetPointClicked(P1.x, P1.y);

		if (P1.x > 1070 && P1.x < 1200 && P1.y < UI.ToolBarHeight) //Exit Action
		{
			pGUI->ClearStatusBar();
			break;
		}

		if (!(P1.y > UI.ToolBarHeight && P1.y < UI.height - UI.StatusBarHeight)) {
			validAction = false;
			P2 = P1;
		}

		if (validAction)
		{
			while (pGUI->IsButtonUp(P2.x, P2.y))
			{
				if (P2.y > UI.ToolBarHeight && P2.y < UI.height - UI.StatusBarHeight)
					pGUI->PrintMessage("New Square: Click at second point");
				else
				{
					if (P2.y < UI.ToolBarHeight)
						P2.y = UI.ToolBarHeight;
					if (P2.y > UI.height - UI.StatusBarHeight)
						P2.y = UI.height - UI.StatusBarHeight;
					pGUI->PrintMessage("Error: Square borders must be inside the drawing area!");
				}
				pGUI->DrawSquare(P1, P2, SqrGfxInfo);
				Sleep(1000 / 60);
				pManager->UpdateInterface();
			}
		}

		//Read 2nd point and store in point P2
		if (validAction)
			pGUI->GetPointClicked(P2.x, P2.y);

		if (P2.x > 1070 && P2.x < 1200 && P2.y < UI.ToolBarHeight) //Exit Action
		{
			pGUI->ClearStatusBar();
			break;
		}

		if (!(P2.y > UI.ToolBarHeight && P2.y < UI.height - UI.StatusBarHeight))
			validAction = false;
		pGUI->ClearStatusBar();

		//Step 3 - Create a Square with the parameters read from the user
		CSquare* R = new CSquare(P1, P2, SqrGfxInfo);

		//Step 4 - Add the Square to the list of figures
		if (validAction)
			pManager->AddFigure(R);

		pManager->UpdateInterface();
	}
}