#include "CSquare.h"

#include <iostream>
#include <fstream>

int CSquare::count = 0;

CSquare::CSquare(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	this->P1 = P1;
	this->P2 = P2;
	this->ID = (this->count++ * 10) + 0;
}
CSquare::CSquare() {}; //default constructor

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(P1, P2, FigGfxInfo, Selected);
	

}

void CSquare::Save(ofstream& OutFile) {

	OutFile << "CSquare\t"
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

void CSquare::Load(ifstream& Infile) {

	string squareData;
	Infile
		>> ID 
		>> P1.x 
		>> P1.y 
		>> P2.x 
		>> P2.y;
	
	Infile >> squareData;
	FigGfxInfo.DrawClr = this->ColorObject(squareData);

	Infile >> squareData;
	if (squareData == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.FillClr = this->ColorObject(squareData);
		FigGfxInfo.isFilled = true;
	}
	this->show();
	this->FigGfxInfo.BorderWdth = 5; //pass 3 as default value for borderWidth
	this->SetSelected(false);

}