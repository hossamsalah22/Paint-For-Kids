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

	this->FigGfxInfo.BorderWdth = 3; //pass 3 as a default value for borderWidth
	this->SetSelected(false);
}

bool CEllipse::Resize(GUI* pGUI, float factor) {
	Point Center;
	Center.x = (P1.x + P2.x) / 2;
	Center.y = (P1.y + P2.y) / 2;

	int horizontal = abs(P1.x - Center.x);
	int vertical = abs(P1.y - Center.y);

	int resizedTopLeftX = Center.x + horizontal * factor;
	int resizedBottomRightX = Center.x - horizontal * factor;

	int resizedTopLeftY = Center.y + vertical * factor;
	int resizedBottomRightY = Center.y - vertical * factor;

	if (resizedTopLeftX > 0 && resizedTopLeftX < UI.width
		&& resizedTopLeftY > UI.ToolBarHeight && resizedTopLeftY < UI.height - UI.StatusBarHeight
		&& resizedBottomRightX > 0 && resizedBottomRightX < UI.width
		&& resizedBottomRightY > UI.ToolBarHeight && resizedBottomRightY < UI.height - UI.StatusBarHeight) {

		P1.x = resizedTopLeftX;
		P1.y = resizedTopLeftY;
		P2.x = resizedBottomRightX;
		P2.y = resizedBottomRightY;

		return true;
	}
	return false;
}