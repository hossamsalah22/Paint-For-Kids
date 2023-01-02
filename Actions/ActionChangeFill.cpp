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
	pGUI->GetPointClicked(P.x, P.y);

	if (P.x < UI.MenuItemWidth * itemsCount && P.y > UI.ToolBarHeight && P.y < UI.ToolBarHeight * 2)
	{
		int colorOrder = P.x / UI.MenuItemWidth;
		switch (colorOrder)
		{
		case 0: pGUI->setCrntFillColor(CUSTOMCOLOR1, false); pManager->UpdateFigureFill(CUSTOMCOLOR1, false); break;
		case 1: pGUI->setCrntFillColor(CUSTOMCOLOR1); pManager->UpdateFigureFill(CUSTOMCOLOR1); break;
		case 2: pGUI->setCrntFillColor(CUSTOMCOLOR2); pManager->UpdateFigureFill(CUSTOMCOLOR2); break;
		case 3: pGUI->setCrntFillColor(CUSTOMCOLOR3); pManager->UpdateFigureFill(CUSTOMCOLOR3); break;
		case 4: pGUI->setCrntFillColor(CUSTOMCOLOR4); pManager->UpdateFigureFill(CUSTOMCOLOR4); break;
		case 5: pGUI->setCrntFillColor(CUSTOMCOLOR5); pManager->UpdateFigureFill(CUSTOMCOLOR5); break;
		case 6: pGUI->setCrntFillColor(CUSTOMCOLOR6); pManager->UpdateFigureFill(CUSTOMCOLOR6); break;
		case 7: pGUI->setCrntFillColor(CUSTOMCOLOR7); pManager->UpdateFigureFill(CUSTOMCOLOR7); break;
		case 8: pGUI->setCrntFillColor(CUSTOMCOLOR8); pManager->UpdateFigureFill(CUSTOMCOLOR8); break;
		case 9: pGUI->setCrntFillColor(CUSTOMCOLOR9); pManager->UpdateFigureFill(CUSTOMCOLOR9); break;
		case 10: pGUI->setCrntFillColor(CUSTOMCOLOR10); pManager->UpdateFigureFill(CUSTOMCOLOR10); break;
		}
	}

	pGUI->ClearStatusBar();
	pManager->UpdateInterface();
}