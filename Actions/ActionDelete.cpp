#include "ActionDelete.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionDelete::ActionDelete(ApplicationManager* pApp) :Action(pApp)
{

}

void ActionDelete::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	if (pManager->getSelected() == NULL)
	{
		pGUI->PrintMessage("Select a shape before you can perform this action");
	}
	else {
		while (pManager->getSelected() != NULL) {
			int figNumber = pManager->DeleteFigure();
			pManager->shiftFigList(figNumber);
			pGUI->ClearDrawArea();
			pGUI->PrintMessage("Deleted Successfully");
		}
	}
}