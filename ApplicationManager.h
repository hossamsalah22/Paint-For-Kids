#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#define M_PI 3.141592

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "Actions\ActionSelect.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\ActionAddEllipse.h"
#include "Actions\ActionAddHexagon.h"
#include "Actions\ActionChangeColor.h"
#include "Actions\ActionChangeFill.h"
#include "Actions\ActionChangeBackground.h"
#include <math.h>
#include "Actions\ActionSave.h"
#include "Actions\ActionLoad.h"
#include "Actions\ActionSendBack.h"
#include "Actions\ActionBringFront.h"
#include "Actions\ActionDelete.h"
#include "Actions\ActionToPlay.h"
#include "Actions\ActionToDraw.h"
#include<fstream>
#include <string>

class Action;	//Forward Declaration

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	//Pointers to Input and Output classes
	GUI* pGUI;

	//Current coordinates of selected menu action
	int x;
	int y;
	

public:	
	ApplicationManager(); 
	~ApplicationManager();

	void Run();		//to run the application
	
	// -- Action-Related Functions
	Action* CreateAction(ActionType);
	void ExecuteAction(Action*&) ; //Execute an action
	void SetPoint(int, int); //Set x and y to coordinates of last selected menu action
	void ResetPoint(); //Set x and y to -1

	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	void SelectFigure(Point P) const; //Return All figures
	void UpdateFigureColor(color _color) const; //Update border color of selected figure(s)
	void UpdateFigureFill(color _color, bool isFilled = true) const; //Update fill color of selected figure(s)
	int getSelectedFigure();// Return selected Figure
	//CFigure* getFigureAt(int index);
	void SendToBack(int selectedIndex); // Action Send to back 
	void BringToFront(int selectedIndex);// Action Bring to Forward 
	//--Actions-Related-To-Save-And-Load
	string colorString(color) const;
	color ColorObject(string) const;
	void SaveAll(ofstream& Out);
	void ClearFigList();
	CFigure* DrawnFigs(int i) const;
	int getFigCount() const;
	//Delete
	void Loop(CFigure*);
	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface() const;	//Redraws all the drawing window	
	CFigure* getSelected();
	int DeleteFigure(); //// Action Delete Figures  
	void shiftFigList(int _figCount); // After delete figure shift elements and delete null
	int ExitMessage(); //// Action Delete Figures  
};

#endif