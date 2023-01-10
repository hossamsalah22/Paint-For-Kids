#include "ActionToPlay.h"
#include "ActionSave.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionToPlay::ActionToPlay(ApplicationManager* pApp) :Action(pApp)
{

}

void ActionToPlay::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	if (pManager->getFigCount() > 0) {
		pGUI->CreatePlayToolBar();
		pGUI->PrintMessage("Switched to Play Mode! Let's Play!");
		pManager->ToPlay();
	}
	else {
		pGUI->PrintMessage("Please Draw Shapes Before Switch to Play Mode");
	}
	pManager->ResetPoint();
}