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
	if (!pGUI->GetPointClicked(P.x, P.y)) {
		pManager->SetPoint(P.x, P.y);
		return;
	}

	if (P.x < UI.MenuItemWidth * itemsCount && P.y > UI.ToolBarHeight && P.y < UI.ToolBarHeight * 2)
	{
		int colorOrder = P.x / UI.MenuItemWidth;
		switch (colorOrder)
		{
			  
		case 0: pGUI->setCrntDrawColor(false); pManager->UpdateFigureColor(false); break;
		case 1: pGUI->setCrntDrawColor(WHITE); pManager->UpdateFigureColor(WHITE); break;
		case 2: pGUI->setCrntDrawColor(BLACK); pManager->UpdateFigureColor(BLACK); break;
		case 3: pGUI->setCrntDrawColor(BROWN); pManager->UpdateFigureColor(BROWN); break;
		case 4: pGUI->setCrntDrawColor(PURPLE); pManager->UpdateFigureColor(PURPLE); break;
		case 5: pGUI->setCrntDrawColor(PINK); pManager->UpdateFigureColor(PINK); break;
		case 6: pGUI->setCrntDrawColor(RED); pManager->UpdateFigureColor(RED); break;
		case 7: pGUI->setCrntDrawColor(ORANGE); pManager->UpdateFigureColor(ORANGE); break;
		case 8: pGUI->setCrntDrawColor(YELLOW); pManager->UpdateFigureColor(YELLOW); break;
		case 9: pGUI->setCrntDrawColor(GREEN); pManager->UpdateFigureColor(GREEN); break;
		case 10: pGUI->setCrntDrawColor(BLUE); pManager->UpdateFigureColor(BLUE); break;
		}
	}
	else
		pManager->ResetPoint();

	pGUI->ClearStatusBar();
	pManager->UpdateInterface();
}