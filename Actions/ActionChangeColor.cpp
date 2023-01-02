#include "ActionChangeColor.h"

ActionChangeColor::ActionChangeColor(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionChangeColor::Execute()
{
	Point P;
	int const itemsCount = 10;
	
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//Prepare Color menu images directorys
	string ColorItemImages[itemsCount];
	for (int i = 1; i <= itemsCount; i++)
		sprintf(&ColorItemImages[i - 1][0], "images\\Colors\\%02d.jpg", i);
	
	//Draw Color menu items one image at a time
	for (int i = 0; i < itemsCount; i++)
		pGUI->pWind->DrawImage(&ColorItemImages[i][0], i * UI.MenuItemWidth, UI.ToolBarHeight, UI.MenuItemWidth, UI.ToolBarHeight);

	pGUI->PrintMessage("Please choose the border color");
	//Read point and store in point P
	pGUI->GetPointClicked(P.x, P.y);

	if (P.x < UI.MenuItemWidth * itemsCount && P.y > UI.ToolBarHeight && P.y < UI.ToolBarHeight * 2)
	{
		int colorOrder = P.x / UI.MenuItemWidth;
		switch (colorOrder)
		{
		case 0: pGUI->setCrntDrawColor(CUSTOMCOLOR1); pManager->UpdateFigureColor(CUSTOMCOLOR1); break;
		case 1: pGUI->setCrntDrawColor(CUSTOMCOLOR2); pManager->UpdateFigureColor(CUSTOMCOLOR2); break;
		case 2: pGUI->setCrntDrawColor(CUSTOMCOLOR3); pManager->UpdateFigureColor(CUSTOMCOLOR3); break;
		case 3: pGUI->setCrntDrawColor(CUSTOMCOLOR4); pManager->UpdateFigureColor(CUSTOMCOLOR4); break;
		case 4: pGUI->setCrntDrawColor(CUSTOMCOLOR5); pManager->UpdateFigureColor(CUSTOMCOLOR5); break;
		case 5: pGUI->setCrntDrawColor(CUSTOMCOLOR6); pManager->UpdateFigureColor(CUSTOMCOLOR6); break;
		case 6: pGUI->setCrntDrawColor(CUSTOMCOLOR7); pManager->UpdateFigureColor(CUSTOMCOLOR7); break;
		case 7: pGUI->setCrntDrawColor(CUSTOMCOLOR8); pManager->UpdateFigureColor(CUSTOMCOLOR8); break;
		case 8: pGUI->setCrntDrawColor(CUSTOMCOLOR9); pManager->UpdateFigureColor(CUSTOMCOLOR9); break;
		case 9: pGUI->setCrntDrawColor(CUSTOMCOLOR10); pManager->UpdateFigureColor(CUSTOMCOLOR10); break;
		}
	}

	pGUI->ClearStatusBar();
	pManager->UpdateInterface();
}