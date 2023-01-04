#include "ActionAddHexagon.h"

ActionAddHexagon::ActionAddHexagon(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddHexagon::Execute()
{
	Point P1, P2;
	bool validAction;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo HexGfxInfo;
	HexGfxInfo.isFilled = pGUI->getCrntFillStatus();	//default is not filled
	//get drawing, filling colors and pen width from the interface
	HexGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	HexGfxInfo.FillClr = pGUI->getCrntFillColor();
	HexGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	while (1)
	{
		validAction = true;
		//Step 1 - Read Hexagon data from the user
		pGUI->PrintMessage("New Hexagon: Click at first point");
		//Read 1st point and store in point P1
		if (!pGUI->GetPointClicked(P1.x, P1.y)) {
			pManager->SetPoint(P1.x, P1.y);
			return;
		}

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
					pGUI->PrintMessage("New Hexagon: Click at second point");
				else
				{
					if (P2.y < UI.ToolBarHeight)
						P2.y = UI.ToolBarHeight;
					if (P2.y > UI.height - UI.StatusBarHeight)
						P2.y = UI.height - UI.StatusBarHeight;
					pGUI->PrintMessage("Error: Hexagon borders must be inside the drawing area!");
				}
				pGUI->DrawHexagon(P1, P2, HexGfxInfo);
				Sleep(1000 / 60);
				pManager->UpdateInterface();
			}
		}

		//Read 2nd point and store in point P2
		if (validAction)
			if (!pGUI->GetPointClicked(P2.x, P2.y)) {
				pManager->SetPoint(P2.x, P2.y);
				return;
			}

		if (P2.x > 1070 && P2.x < 1200 && P2.y < UI.ToolBarHeight) //Exit Action
		{
			pGUI->ClearStatusBar();
			break;
		}

		if (!(P2.y > UI.ToolBarHeight && P2.y < UI.height - UI.StatusBarHeight))
			validAction = false;
		pGUI->ClearStatusBar();

		//Step 3 - Create a Hexagon with the parameters read from the user
		CHexagon* H = new CHexagon(P1, P2, HexGfxInfo);

		//Step 4 - Add the Hexagon to the list of figures
		if (validAction)
			pManager->AddFigure(H);

		pManager->UpdateInterface();
	}
}