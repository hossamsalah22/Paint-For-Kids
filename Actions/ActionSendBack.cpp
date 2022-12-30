#include "ActionSendBack.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionSendBack::ActionSendBack(ApplicationManager* pApp) :Action(pApp)
{

}

void ActionSendBack::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	int selectedIndex = pManager->getSelectedFigure();
	if (selectedIndex != -1) {
		pManager->SendToBack(selectedIndex);
		pGUI->ClearDrawArea();
	}
	else {
		pGUI->PrintMessage("Select only one shape before you can perform this action");
	}
}