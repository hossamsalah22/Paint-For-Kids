#include "ActionResize.h"


ActionResize::ActionResize(ApplicationManager* pApp, float factor) : Action(pApp)
{
	resizeFactor = factor;
}

void ActionResize::Execute() {
	GUI* pGUI = pManager->GetGUI();
	int selectedIndex = pManager->getSelectedFigure();
	if (selectedIndex != -1) {
		CFigure* figure = pManager->getSelected();
		bool ableToResize = figure->Resize(pGUI, resizeFactor);
		if (ableToResize) {
			pManager->UpdateInterface();
			pGUI->PrintMessage("Resized Successfully");
		}
		else {
			pGUI->PrintMessage("Can't Resize Due To Boundries");
		}
	}
	else {
		pGUI->PrintMessage("Select One Shape before you can perform this action");
	}
	pManager->ResetPoint();
}