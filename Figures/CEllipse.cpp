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
	//Call Output::DrawRect to draw a Square on the screen	
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

		if (this->FigGfxInfo.isFilled)
			OutFile << this->ColorString(this->FigGfxInfo.FillClr) << "\n";
		else
			OutFile << "NO_FILL\n";
}


void CEllipse::Load(ifstream& Infile) {
	string s;
	Infile >> ID
		>> P1.x
		>> P1.y
		>> P2.x
		>> P2.y;

	Infile >> s;
	FigGfxInfo.DrawClr = this->ColorObject(s);

	Infile >> s;
	if (s == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.FillClr = this->ColorObject(s);
		FigGfxInfo.isFilled = true;
	}
	this->show();
	this->FigGfxInfo.BorderWdth = 5; //pass 3 as a default value for borderWidth
	this->SetSelected(false);
}