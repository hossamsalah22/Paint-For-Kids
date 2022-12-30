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
		case 0: pGUI->setCrntBackgroundColor(WHITE); break;
		case 1: pGUI->setCrntBackgroundColor(BLACK); break;
		case 2: pGUI->setCrntBackgroundColor(BROWN); break;
		case 3: pGUI->setCrntBackgroundColor(PURPLE); break;
		case 4: pGUI->setCrntBackgroundColor(PINK); break;
		case 5: pGUI->setCrntBackgroundColor(RED); break;
		case 6: pGUI->setCrntBackgroundColor(ORANGE); break;
		case 7: pGUI->setCrntBackgroundColor(YELLOW); break;
		case 8: pGUI->setCrntBackgroundColor(GREEN); break;
		case 9: pGUI->setCrntBackgroundColor(BLUE); break;
		}
	}

	pGUI->ClearStatusBar();
	pManager->UpdateInterface();
}