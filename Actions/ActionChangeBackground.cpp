#include "ActionChangeBackground.h"

ActionChangeBackground::ActionChangeBackground(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionChangeBackground::Execute()
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

	pGUI->PrintMessage("Please choose the background color");
	//Read point and store in point P
	pGUI->GetPointClicked(P.x, P.y);

	if (P.x < UI.MenuItemWidth * itemsCount && P.y > UI.ToolBarHeight && P.y < UI.ToolBarHeight * 2)
	{
		int colorOrder = P.x / UI.MenuItemWidth;
		switch (colorOrder)
		{
		case 0: pGUI->setCrntBackgroundColor(CUSTOMCOLOR1); break;
		case 1: pGUI->setCrntBackgroundColor(CUSTOMCOLOR2); break;
		case 2: pGUI->setCrntBackgroundColor(CUSTOMCOLOR3); break;
		case 3: pGUI->setCrntBackgroundColor(CUSTOMCOLOR4); break;
		case 4: pGUI->setCrntBackgroundColor(CUSTOMCOLOR5); break;
		case 5: pGUI->setCrntBackgroundColor(CUSTOMCOLOR6); break;
		case 6: pGUI->setCrntBackgroundColor(CUSTOMCOLOR7); break;
		case 7: pGUI->setCrntBackgroundColor(CUSTOMCOLOR8); break;
		case 8: pGUI->setCrntBackgroundColor(CUSTOMCOLOR9); break;
		case 9: pGUI->setCrntBackgroundColor(CUSTOMCOLOR10); break;
		}
	}

	pGUI->ClearStatusBar();
	pManager->UpdateInterface();
}