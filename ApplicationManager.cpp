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
		case DEL:
			newAct= new ActionDelete(this);
			break;
		case SEND_BACK:	//Send a figure to the back of all figures
			newAct = new ActionSendBack(this);
			break;
		case BRNG_FRNT: //Send a figure to the Front of all figures
			newAct = new ActionBringFront(this);
			break;
		case EXIT:
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
	if (ClrObj == CUSTOMCOLOR1) return "CUSTOMCOLOR1";
	else if (ClrObj == CUSTOMCOLOR2) return "CUSTOMCOLOR2";
	else if (ClrObj == CUSTOMCOLOR3) return "CUSTOMCOLOR3";
	else if (ClrObj == CUSTOMCOLOR4) return "CUSTOMCOLOR4";
	else if (ClrObj == CUSTOMCOLOR5) return "CUSTOMCOLOR5";
	else if (ClrObj == CUSTOMCOLOR6) return "CUSTOMCOLOR6";
	else if (ClrObj == CUSTOMCOLOR7) return "CUSTOMCOLOR7";
	else if (ClrObj == CUSTOMCOLOR8) return "CUSTOMCOLOR8";
	else if (ClrObj == CUSTOMCOLOR9) return "CUSTOMCOLOR9";
	else if (ClrObj == CUSTOMCOLOR10) return "CUSTOMCOLOR10";
	else return "WHITE";
}
//Convert from string to color object to load
color ApplicationManager::ColorObject(string ClrStr) const
{
	if (ClrStr == "CUSTOMCOLOR1") return CUSTOMCOLOR1;
	else if (ClrStr == "CUSTOMCOLOR2") return CUSTOMCOLOR2;
	else if (ClrStr == "CUSTOMCOLOR3") return CUSTOMCOLOR3;
	else if (ClrStr == "CUSTOMCOLOR4") return CUSTOMCOLOR4;
	else if (ClrStr == "CUSTOMCOLOR5") return CUSTOMCOLOR5;
	else if (ClrStr == "CUSTOMCOLOR6") return CUSTOMCOLOR6;
	else if (ClrStr == "CUSTOMCOLOR7") return CUSTOMCOLOR7;
	else if (ClrStr == "CUSTOMCOLOR8") return CUSTOMCOLOR8;
	else if (ClrStr == "CUSTOMCOLOR9") return CUSTOMCOLOR9;
	else if (ClrStr == "CUSTOMCOLOR10") return CUSTOMCOLOR10;
	else return WHITE;
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


CFigure* ApplicationManager::getSelected()
{
	int index = getSelectedFigure();
	if (index >= 0 && index < FigCount)
		return FigList[index];
	return NULL;
}

// Return index of selected figure 
int ApplicationManager::getSelectedFigure()
{

	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
			return i;
	return -1;
}


//==================================================================================//
//							Send To Back											//
//==================================================================================//

void ApplicationManager::SendToBack(int selectedIndex)
{
	if (selectedIndex != 0)
	{
		CFigure* spare = FigList[0];
		FigList[0] = FigList[selectedIndex];
		FigList[selectedIndex] = spare;
	}
}


//==================================================================================//
//							Bring To Front											//
//==================================================================================//

void ApplicationManager::BringToFront(int selectedIndex)
{
	if (selectedIndex != FigCount - 1)
	{
		CFigure* tmp = FigList[FigCount - 1];
		FigList[FigCount - 1] = FigList[selectedIndex];
		FigList[selectedIndex] = tmp;
	}
}

//==================================================================================//
//							Delete           										//
//==================================================================================//

// -- For  Figure Deleted 
int ApplicationManager::DeleteFigure()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			delete FigList[i];
			FigList[i] = NULL;
			FigCount--;
			return i;
		}
	}
}

// After delete figure shift elements and delete null
void ApplicationManager::shiftFigList(int _figCount)
{
	for (int j = _figCount; j < FigCount; j++)
	{
		FigList[j] = FigList[j + 1];
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
