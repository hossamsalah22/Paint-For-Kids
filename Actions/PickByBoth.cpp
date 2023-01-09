#include "PickByBoth.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

PickByBoth::PickByBoth(ApplicationManager* pApp) :Action(pApp)
{

}

void PickByBoth::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->CreatePlayToolBar();
	pGUI->PrintMessage("Switched to Play Mode! Let's Play!");
	pManager->ResetPoint();
}