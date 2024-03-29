#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\GUI.h"
#include <iostream>

//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	Point P1;
	Point P2;
	/// Add more parameters if needed.
	

public:
	CFigure(GfxInfo FigureGfxInfo);
	CFigure();
	void SetSelected(bool );	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	int GetID() const;  //Return ID

	Point GetP1() const;  //Return P1
	Point GetP2() const;  //Return P2

	virtual void DrawMe(GUI*) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	void ChngFillStts(bool isFilled); //changes the figure's filling status
	bool IsFilled();
	string getFilledColor();
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Move() = 0;		//Move the figure

	string ColorString(color) const;
	color ColorObject(string) const;
	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar

	bool Resize(GUI* pGUI, float factor);	//Resize the figure
	void Move(Point P1, Point P2); //Move the figure
	bool IsHidden();
	void Hide();
	void show();
};

#endif