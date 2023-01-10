#include "ActionAddEllipse.h"

ActionAddEllipse::ActionAddEllipse(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddEllipse::Execute()
{
	Point P1, P2;
	bool validAction;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo EllpsGfxInfo;
	EllpsGfxInfo.isFilled = pGUI->getCrntFillStatus();	//default is not filled
	//get drawing, filling colors and pen width from the interface
	EllpsGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	EllpsGfxInfo.FillClr = pGUI->getCrntFillColor();
	EllpsGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	while (1)
	{
		validAction = true;
		//Step 1 - Read Ellipse data from the user
		pGUI->PrintMessage("New Ellipse: Click at first point");
		//Read 1st point and store in point P1
		if (!pGUI->GetPointClicked(P1.x, P1.y)) {
			pManager->SetPoint(P1.x, P1.y);
			return;
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
					pGUI->PrintMessage("New Ellipse: Click at second point");
				else
				{
					if (P2.y < UI.ToolBarHeight)
						P2.y = UI.ToolBarHeight;
					if (P2.y > UI.height - UI.StatusBarHeight)
						P2.y = UI.height - UI.StatusBarHeight;
					pGUI->PrintMessage("Error: Ellipse borders must be inside the drawing area!");
				}
				pGUI->DrawEllipse(P1, P2, EllpsGfxInfo);
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

		if (!(P2.y > UI.ToolBarHeight && P2.y < UI.height - UI.StatusBarHeight))
			validAction = false;
		pGUI->ClearStatusBar();

		//Step 3 - Create an Ellipse with the parameters read from the user
		CEllipse* E = new CEllipse(P1, P2, EllpsGfxInfo);

		//Step 4 - Add the Ellipse to the list of figures
		if (validAction)
			pManager->AddFigure(E);

		pManager->UpdateInterface();
	}
}