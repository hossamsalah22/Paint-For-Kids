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
		int msgboxID = MessageBox(
			NULL,
			"Are You Sure You Have Delete Those Figures",
			"Delete?",
			MB_OKCANCEL | MB_ICONSTOP
		);
		switch (msgboxID)
		{
		case IDCANCEL:
			break;
		case IDOK:
			while (pManager->getSelected() != NULL) {
				int figNumber = pManager->DeleteFigure();
				pManager->shiftFigList(figNumber);
				pGUI->ClearDrawArea();
				pGUI->PrintMessage("Deleted Successfully");
			}
			break;
		}
	}
	pManager->ResetPoint();
}