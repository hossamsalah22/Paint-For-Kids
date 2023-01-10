#include "CEllipse.h"

#include <iostream>
#include <fstream>

int CEllipse::count = 0;

CEllipse::CEllipse(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	this->P1 = P1;
	this->P2 = P2;
	this->ID = (this->count++ * 10) + 1;
}

CEllipse::CEllipse() {}; //default constructor

void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Ellipse on the screen	
	pGUI->DrawEllipse(P1, P2, FigGfxInfo, Selected);
}


void CEllipse::Save(ofstream& OutFile) {

	OutFile << "CEllipse\t" 
		<< this->ID << "\t"
		<< this->P1.x << "\t"
		<< this->P1.y << "\t"
		<< this->P2.x << "\t"
		<< this->P2.y << "\t"
		<< this->ColorString(this->FigGfxInfo.DrawClr) << "\t";
		// check figure is filled or not
		if (this->FigGfxInfo.isFilled)
			OutFile << this->ColorString(this->FigGfxInfo.FillClr) << "\n";
		else
			OutFile << "NO_FILL\n";
}


void CEllipse::Load(ifstream& Infile) {
	string ellipseData;
	Infile >> ID
		>> P1.x
		>> P1.y
		>> P2.x
		>> P2.y;

	Infile >> ellipseData;
	FigGfxInfo.DrawClr = this->ColorObject(ellipseData);

	Infile >> ellipseData;
	if (ellipseData == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.FillClr = this->ColorObject(ellipseData);
		FigGfxInfo.isFilled = true;
	}
	this->show();
	this->FigGfxInfo.BorderWdth = 5;
	this->SetSelected(false);
}

