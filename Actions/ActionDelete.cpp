#include "ActionDelete.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionDelete::ActionDelete(ApplicationManager* pApp) :Action(pApp)
{

}

void ActionDelete::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	if (pManager->getSelected() != NULL)
	{
		int figNumber = pManager->DeleteFigure();
		pManager->shiftFigList(figNumber);
		pGUI->ClearDrawArea();
		//pManager->UpdateInterface();
		pGUI->PrintMessage("Deleted Successfully");
	}
	else {
		pGUI->PrintMessage("Select a shape before you can perform this action");
	}
}