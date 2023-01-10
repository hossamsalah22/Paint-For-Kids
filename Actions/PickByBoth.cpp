#include "PickByBoth.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
PickByBoth::PickByBoth(ApplicationManager* pApp) :Action(pApp)
{
	pManager->copy(FigList);
	CorrectCounter = 0;
	pGUI = pManager->GetGUI();
	FigID = -1;
	pManager->getFigureList(FigAvailList);
	FigCount = pManager->getCounter();
	PickByBoth::getRandomFigure();
	pGUI->CreatePlayToolBar();
	colorCounter = PickByBoth::NumOfColors();
	if (FigCount == 0) { pGUI->PrintMessage("no figures to select"); }
	else {
		string pickMessage;
		if (FigID == 0) {
			pickMessage = "pick All squares with color : " + pickColorString;
			pGUI->PrintMessage(pickMessage);
		}
		else if (FigID == 1) {
			pickMessage = "pick All circules with color : " + pickColorString;
			pGUI->PrintMessage(pickMessage);
		}
		else if (FigID == 2) {
			pickMessage = "pick All hexagons with color : " + pickColorString;
			pGUI->PrintMessage(pickMessage);
		}
	}
}

void PickByBoth::Execute()
{
	Point P;
	while (1)
	{

		pManager->UpdateInterface();
		//Read point and store in point P
		if (!pGUI->GetPointClicked(P.x, P.y)) {
			pManager->SetPoint(P.x, P.y);
			return;
		}
		if (P.y > UI.ToolBarHeight && P.y < UI.height - UI.StatusBarHeight)
			PickByBoth::Select(P);
		if (CorrectCounter >= colorCounter) {
			pGUI->PrintMessage("you won");
			pManager->show();
		}
	}
}

void PickByBoth::Select(Point P) //Return All figures
{
	Point p;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->GetP1().x < FigList[i]->GetP2().x)
		{
			x1 = FigList[i]->GetP1().x;
			x2 = FigList[i]->GetP2().x;
		}
		else
		{
			x1 = FigList[i]->GetP2().x;
			x2 = FigList[i]->GetP1().x;
		}

		if (FigList[i]->GetP1().y < FigList[i]->GetP2().y)
		{
			y1 = FigList[i]->GetP1().y;
			y2 = FigList[i]->GetP2().y;
		}
		else
		{
			y1 = FigList[i]->GetP2().y;
			y2 = FigList[i]->GetP1().y;
		}
		if (P.x >= x1 && P.x <= x2)
		{
			if (FigList[i]->GetID() % 10 == 0) //Select/Unselect CSquare
			{
				if (P.y >= y1 && P.y <= y2) //Point is inside Square
				{
					if (FigList[i]->IsSelected())
						FigList[i]->SetSelected(false);
					else {
						FigList[i]->SetSelected(true);
						if (FigList[i]->getFilledColor() == pickColorString&& FigID == 0)
						{
							CorrectCounter++;
							FigList[i]->Hide();
							string score = " score : ";
							score += std::to_string(CorrectCounter);
							pGUI->PrintMessage(score);
						}
						else {
							pGUI->PrintMessage("wrong selection");
							FigList[i]->SetSelected(false);
						}
					}
					break;
				}
			}

			if (FigList[i]->GetID() % 10 == 1) //Select/Unselect CEllipse
			{
				int baseY = y1, height = y2 - y1;
				y1 = y2 = baseY + 0.5 * height;
				int width = x2 - x1;
				double deltaX = (P.x - x1) / (double)width;
				y1 += -(sin(M_PI * deltaX)) * height / 2;
				y2 += (sin(M_PI * deltaX)) * height / 2;

				if (P.y >= y1 && P.y <= y2) //Point is inside Ellipse
				{
					if (FigList[i]->IsSelected())
						FigList[i]->SetSelected(false);
					else {
						FigList[i]->SetSelected(true);
						if (FigList[i]->getFilledColor() == pickColorString&& FigID == 1)
						{
							CorrectCounter++;
							FigList[i]->Hide();
							string score = " score : ";
							score += std::to_string(CorrectCounter);
							pGUI->PrintMessage(score);
						}
						else {
							pGUI->PrintMessage("wrong selection");
							FigList[i]->SetSelected(false);
						}
					}
					break;
				}
			}

			if (FigList[i]->GetID() % 10 == 2) //Select/Unselect CHexagon
			{
				int width = x2 - x1;
				double deltaX = (P.x - x1) / (double)width;

				if (deltaX < 0.25)  //Left part
				{
					int baseY = y1, height = y2 - y1;
					y1 = y2 = baseY + 0.5 * height;
					double deltaY = deltaX * 4 * height / 2;
					y1 -= deltaY;
					y2 += deltaY;
				}
				else if (deltaX > 0.75)  //Right part
				{
					int baseY = y1, height = y2 - y1;
					y1 = y2 = baseY + 0.5 * height;
					double deltaY = (1 - deltaX) * 4 * height / 2;
					y1 -= deltaY;
					y2 += deltaY;
				}
				if (P.y >= y1 && P.y <= y2)
				{
					if (FigList[i]->IsSelected())
						FigList[i]->SetSelected(false);
					else {
						FigList[i]->SetSelected(true);
						if (FigList[i]->getFilledColor() == pickColorString&& FigID == 2)
						{
							CorrectCounter++;
							FigList[i]->Hide();
							string score = " score : ";
							score += std::to_string(CorrectCounter);
							pGUI->PrintMessage(score);
						}
						else {
							pGUI->PrintMessage("wrong selection");
							FigList[i]->SetSelected(false);
						}
					}
					break;
				}
			}
		}
	}
}

bool PickByBoth::IsThereAColor() {
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->IsFilled()) {
			fillFlag = true;
			return 1;
		}
	}
	return 0;
}
void PickByBoth::getRandomFigure()
{
	srand(time(NULL));
	int num = rand() % FigCount;
	pickColorString = FigList[num]->getFilledColor();
	FigID= FigList[num]->GetID() * 10 % 3;
}

int PickByBoth::NumOfColors() {
	int counter = 0;
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->getFilledColor() == pickColorString&&FigList[i]->GetID() == FigID)
			counter++;
	}
	return counter;
}

/*void PickByBoth::randomColor() {
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->IsFilled()) {
			colorList[i] = FigList[i];
			colorCounter++;
		}
	}
	int i = rand() * colorCounter;
	pickColorString = colorList[i]->getFilledColor();
}*/