#include "CHexagon.h"
#include <iostream>
#include <fstream>
#include "../DEFS.h"

int CHexagon::count = 0;

CHexagon::CHexagon(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	this->P1 = P1;
	this->P2 = P2;
	this->ID = (this->count++ * 10) + 2;
}
CHexagon::CHexagon() {}; //default constructor

void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawHexagon(P1, P2, FigGfxInfo, Selected);
}


void CHexagon::Save(ofstream& OutFile) {
	OutFile << "CHexagon\t"
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

void CHexagon::Load(ifstream& Infile) {
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
	this->FigGfxInfo.BorderWdth = 3; //pass 3 as default value for borderWidth
	this->SetSelected(false);
}


bool CHexagon::Resize(float factor, GUI* pGUI) {
//Resize Code
	return false;
}