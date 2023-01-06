#include "ActionResize.h"


ActionResize::ActionResize(ApplicationManager* pApp, float factor) : Action(pApp)
{
	resizeFactor = factor;
}

void ActionResize::Execute() {
	GUI* pGUI = pManager->GetGUI();
	CFigure* figure = pManager->getSelected();

	if (figure == NULL) {
		pGUI->PrintMessage("Select a shape before you can perform this action");
		Point point;
		pGUI->GetPointClicked(point.x, point.y);
		figure = pManager->GetFigure(point.x, point.y);
	}


	if (figure != NULL) {
		bool ableToResize = figure->Resize(pGUI, resizeFactor);
		if (ableToResize) {
			pManager->UpdateInterface();
			pGUI->PrintMessage("Resized Successfully");
		}
		else {
			pGUI->PrintMessage("Can't Resize Due To Boundries");
		}
	}
}