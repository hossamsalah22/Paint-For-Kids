#include "ApplicationManager.h"
#include <iostream>
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType();

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	int selectedIndex = getSelectedFigure();

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case SELECT:
			newAct = new ActionSelect(this);
			break;

		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;

		case DRAW_ELPS:
			newAct = new ActionAddEllipse(this);
			break;

		case DRAW_HEX:
			newAct = new ActionAddHexagon(this);
			break;

		case CHNG_DRAW_CLR:
			newAct = new ActionChangeColor(this);
			break;

		case CHNG_FILL_CLR:
			newAct = new ActionChangeFill(this);
			break;

		case CHNG_BG_CLR:
			newAct = new ActionChangeBackground(this);
			break;
		case SAVE:
			newAct = new ActionSave(this, FigCount, 0);
			break;
		case LOAD:
			newAct = new ActionLoad(this, FigCount);
			break;
		case SEND_BACK:	//Send a figure to the back of all figures
			newAct = new ActionSendBack(this);
			break;
		case BRNG_FRNT: //Send a figure to the Front of all figures
			newAct = new ActionBringFront(this);
			break;
		case TO_PLAY:
			newAct = new ActionToPlay(this);
			break;
		/*	//Play Mode Actions//
		case P_H_TYPE:
			newAct = new PickByType(this);
			break;

		case P_H_FILL:
			newAct = new PickByFill(this);
			break;
		case P_H_BOTH:
			newAct = new PickByBoth(this);
			break;*/
		case TO_DRAW:
			newAct = new ActionToDraw(this);
			break;
			// Rest of Draw
		case EXIT:
			DisplayMessageBox();
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	///Add your code here to search for a figure given a point x,y	

	return NULL;
}

void ApplicationManager::SelectFigure(Point P) const //Return All figures
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
					else
						FigList[i]->SetSelected(true);

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
					else
						FigList[i]->SetSelected(true);

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
					else
						FigList[i]->SetSelected(true);

					break;
				}
			}
		}
	}
}

void ApplicationManager::UpdateFigureColor(color _color) const //Update border color of selected figure(s)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
			FigList[i]->ChngDrawClr(_color);
	}
}

void ApplicationManager::UpdateFigureFill(color _color, bool isFilled) const //Update fill color of selected figure(s)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->ChngFillStts(isFilled);
			FigList[i]->ChngFillClr(_color);
		}
	}
}



//==================================================================================//
//							Save And load Functions									//
//==================================================================================//

//Convert from color object to string to save
string ApplicationManager::colorString(color ClrObj) const
{
	if (ClrObj == WHITE) return "WHITE";
	else if (ClrObj == BLACK) return "BLACK";
	else if (ClrObj == BROWN) return "BROWN";
	else if (ClrObj == PURPLE) return "PURPLE";
	else if (ClrObj == PINK) return "PINK";
	else if (ClrObj == RED) return "RED";
	else if (ClrObj == ORANGE) return "ORANGE";
	else if (ClrObj == YELLOW) return "YELLOW";
	else if (ClrObj == GREEN) return "GREEN";
	else if (ClrObj == BLUE) return "BLUE";
	else return "BLUE";
}
//Convert from string to color object to load
color ApplicationManager::ColorObject(string ClrStr) const
{
	if (ClrStr == "WHITE") return WHITE;
	else if (ClrStr == "BLACK") return BLACK;
	else if (ClrStr == "BROWN") return BROWN;
	else if (ClrStr == "PURPLE") return PURPLE;
	else if (ClrStr == "PINK") return PINK;
	else if (ClrStr == "RED") return RED;
	else if (ClrStr == "ORANGE") return ORANGE;
	else if (ClrStr == "YELLOW") return YELLOW;
	else if (ClrStr == "GREEN") return GREEN;
	else if (ClrStr == "BLUE") return BLUE;
	else return BLUE;
}

void ApplicationManager::SaveAll(ofstream& Out)   //Call the Save function for each Figure
{
	for (int i = 0; i < FigCount; ++i)
		FigList[i]->Save(Out);
}
//Transfer figures in FigList to playmode
CFigure* ApplicationManager::DrawnFigs(int i) const
{
	return FigList[i];
}
////////////////////////////////////////////////////////////////////////////////////
//Transfer FigCount to playmode to avoid unnessecary loops
int ApplicationManager::getFigCount() const
{
	return FigCount;
}
////////////////////////////////////////////////////////////////////////////////////


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pGUI->ClearDrawArea();
	for (int i = 0; i < FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
}

// Clear draw area 
void ApplicationManager::ClearFigList()
{
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0;
}

// Return index of selected figure 
int ApplicationManager::getSelectedFigure()
{
	int selectedFiguresCount = 0;
	int index = -1;

	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			index = i;
			selectedFiguresCount++;
		}
	}

	if (selectedFiguresCount == 1)
		return index;
	return -1;
}


//==================================================================================//
//							Send To Back											//
//==================================================================================//

void ApplicationManager::SendToBack(int selectedIndex)
{
	if (selectedIndex != 0) {
		for (int i = selectedIndex; i > 0; i--) {
			CFigure* tmp = FigList[i - 1];
			FigList[i - 1] = FigList[i];
			FigList[i] = tmp;
		}
	}
}


//==================================================================================//
//							Bring To Front											//
//==================================================================================//

void ApplicationManager::BringToFront(int selectedIndex)
{
	if (selectedIndex != FigCount - 1)
	{
		for (int i = selectedIndex; i < FigCount - 1; i++) {
			CFigure* tmp = FigList[i + 1];
			FigList[i + 1] = FigList[i];
			FigList[i] = tmp;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}


//==================================================================================//
//							------EXIT WINDOW----------      						//
//==================================================================================//

int ApplicationManager::DisplayMessageBox()
{
	int msgboxID = MessageBox(
		NULL,
		"Are You Sure You Have Saved Your File?\n Click ok to Leave\nClick cancel to Save",
		"Exit",
		MB_OKCANCEL | MB_DEFBUTTON2 | MB_ICONWARNING
	);

	switch (msgboxID)
	{
	case IDCANCEL:
		break;
	case IDOK:
		exit(0);
		break;
	}
	//thia will execute the save and then exit immediatelly
	Action* newAct = new ActionSave(this, FigCount, true);
	ExecuteAction(newAct);


	return msgboxID;
}