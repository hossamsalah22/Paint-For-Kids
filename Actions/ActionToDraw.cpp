#include "ActionToDraw.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionToDraw::ActionToDraw(ApplicationManager* pApp) :Action(pApp)
{

}

void ActionToDraw::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->CreateDrawToolBar();
	pGUI->PrintMessage("Switched to Draw Mode! Start Drawing");
	pManager->ResetPoint();
}