#include "ActionChangeFill.h"

ActionChangeFill::ActionChangeFill(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionChangeFill::Execute()
{
	Point P;
	int const itemsCount = 11;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//Prepare Color menu images directorys
	string ColorItemImages[itemsCount];
	for (int i = 0; i < itemsCount; i++)
		sprintf(&ColorItemImages[i][0], "images\\Colors\\%02d.jpg", i);

	//Draw Color menu items one image at a time
	for (int i = 0; i < itemsCount; i++)
		pGUI->pWind->DrawImage(&ColorItemImages[i][0], i * UI.MenuItemWidth, UI.ToolBarHeight, UI.MenuItemWidth, UI.ToolBarHeight);

	pGUI->PrintMessage("Please choose the fill color");
	//Read point and store in point P
	if (!pGUI->GetPointClicked(P.x, P.y)) {
		pManager->SetPoint(P.x, P.y);
		return;
	}

	if (P.x < UI.MenuItemWidth * itemsCount && P.y > UI.ToolBarHeight && P.y < UI.ToolBarHeight * 2)
	{
		int colorOrder = P.x / UI.MenuItemWidth;
		switch (colorOrder)
		{
		case 0: pGUI->setCrntFillColor(WHITE, false); pManager->UpdateFigureFill(WHITE, false); break;
		case 1: pGUI->setCrntFillColor(WHITE); pManager->UpdateFigureFill(WHITE); break;
		case 2: pGUI->setCrntFillColor(BLACK); pManager->UpdateFigureFill(BLACK); break;
		case 3: pGUI->setCrntFillColor(BROWN); pManager->UpdateFigureFill(BROWN); break;
		case 4: pGUI->setCrntFillColor(PURPLE); pManager->UpdateFigureFill(PURPLE); break;
		case 5: pGUI->setCrntFillColor(PINK); pManager->UpdateFigureFill(PINK); break;
		case 6: pGUI->setCrntFillColor(RED); pManager->UpdateFigureFill(RED); break;
		case 7: pGUI->setCrntFillColor(ORANGE); pManager->UpdateFigureFill(ORANGE); break;
		case 8: pGUI->setCrntFillColor(YELLOW); pManager->UpdateFigureFill(YELLOW); break;
		case 9: pGUI->setCrntFillColor(GREEN); pManager->UpdateFigureFill(GREEN); break;
		case 10: pGUI->setCrntFillColor(BLUE); pManager->UpdateFigureFill(BLUE); break;
		}
	}
	else
		pManager->ResetPoint();

	pGUI->ClearStatusBar();
	pManager->UpdateInterface();
}