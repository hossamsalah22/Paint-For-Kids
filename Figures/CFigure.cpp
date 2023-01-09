#include "CFigure.h"

CFigure::CFigure()
{
	Selected = false;
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	FigGfxInfo.IsClickable = true;
	FigGfxInfo.IsHidden = false;
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
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::ChngFillStts(bool isFilled)
{
	FigGfxInfo.isFilled = isFilled;
}


string CFigure::ColorString(color ClrObj) const  //Convert from Color Type to String Type
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

color CFigure::ColorObject(string ClrStr) const  //Convert from string to color object
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


bool CFigure::Resize(GUI* pGUI, float factor) {
	Point Center;
	Center.x = (P1.x + P2.x) / 2;
	Center.y = (P1.y + P2.y) / 2;

	int horizontal = abs(P1.x - Center.x);
	int vertical = abs(P1.y - Center.y);

	int resizedTopLeftX = Center.x + horizontal * factor;
	int resizedBottomRightX = Center.x - horizontal * factor;

	int resizedTopLeftY = Center.y + vertical * factor;
	int resizedBottomRightY = Center.y - vertical * factor;
	int lenDeff = abs(abs(resizedBottomRightX - resizedTopLeftX) - abs(resizedTopLeftY - resizedBottomRightY));
	while (lenDeff < 20) {
		return false;
	}
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

bool CFigure::IsHidden() {
	return FigGfxInfo.IsHidden;
};

void CFigure::Hide() {
	FigGfxInfo.IsHidden=true;
	Selected = false;
};

void CFigure::show() {
	FigGfxInfo.IsHidden = false;
};

void CFigure::Move(Point P1, Point P2)
{
	this->P1 = P1;
	this->P2 = P2;
}