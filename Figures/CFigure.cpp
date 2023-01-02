#include "CFigure.h"

CFigure::CFigure()
{
	Selected = false;
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

int CFigure::GetID() const
{	return ID; }

Point CFigure::GetP1() const
{ return P1; }

Point CFigure::GetP2() const
{	return P2; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::ChngFillStts(bool isFilled)
{
	UI.IsFilled = isFilled;
}


string CFigure::ColorString(color ClrObj) const  //Convert from Color Type to String Type
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
	else return "BLUE";
}

color CFigure::ColorObject(string ClrStr) const  //Convert from string to color object
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
	return BLUE;
}