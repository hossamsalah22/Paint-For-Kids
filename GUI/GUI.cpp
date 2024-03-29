#include "GUI.h"

//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1200;
	UI.height = 600;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 50;
	
	UI.IsFilled = false; //Filling status
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = WHITE;		//Messages color
	UI.BkGrndColor = WHITE;	//Background color
	UI.HighlightColor = KHAKI;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = LIGHTSLATEGRAY;
	UI.PenWidth = 5;	//width of the figures frames

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - ITI_OS43");
	
	CreateDrawToolBar();
	CreateStatusBar();
	
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//


bool GUI::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
	
	int MenuItemsCount;
	switch (UI.InterfaceMode) {
	case MODE_DRAW:
		MenuItemsCount = 19;
		break;
	case MODE_PLAY:
		MenuItemsCount = 5;
		break;
	}
	
	if (y > 0 && y < UI.ToolBarHeight && x > 0 && x < MenuItemsCount * UI.MenuItemWidth)
		return false;
	return true;
}

bool GUI::IsButtonUp(int& x, int& y) const
{
	return (pWind->GetButtonState(LEFT_BUTTON , x, y) == BUTTON_UP);	//Return true if left mouse button is up
}

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType(int _x, int _y) const
{	
	//GUI::PrintExitAction();

	int x = _x;
	int y = _y;

	if (x == -1 && y == -1)
		pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SLCT: return SELECT;
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HEX:	return DRAW_HEX;
			case ITM_CLR: return CHNG_DRAW_CLR;
			case ITM_FILL: return CHNG_FILL_CLR;
			case ITM_BG: return CHNG_BG_CLR;
			case ITM_SAVE: return SAVE;
			case ITM_DEL: return DEL;
			case ITM_LOAD: return LOAD;
			case ITM_BACK: return SEND_BACK;
			case ITM_FRNT: return BRNG_FRNT;
			case ITM_MOV: return MOVE;
			case ITM_PLAY: return TO_PLAY;
			case ITM_RSZ_QRT: return QUARTERED_RESIZE;
			case ITM_RSZ_HALF: return HALFED_RESIZE;
			case ITM_RSZ_DOUBLE: return DOUBLED_RESIZE;
			case ITM_RSZ_QUADRUPLE: return QUADRUPLE_RESIZED;
			case ITM_EXIT_DRAW: return EXIT;	
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		if (y >= 0 && y < UI.ToolBarHeight) {
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)

			{
			case ITM_P_H_TYPE:return P_H_TYPE;
			case ITM_P_H_FILL:return P_H_FILL;
			case ITM_TO_DRAW:return TO_DRAW;
			case ITM_P_H_BOTH: return P_H_BOTH;
			case ITM_EXIT_PLAY: return EXIT;
			default: return EMPTY;

			}

		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return PLAYING_AREA;
		}
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}	

}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SLCT] = "images\\MenuItems\\MenuSelect.jpg";
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\MenuSquare.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\MenuEllipse.jpg";
	MenuItemImages[ITM_HEX] = "images\\MenuItems\\MenuHexagon.jpg";
	MenuItemImages[ITM_CLR] = "images\\MenuItems\\MenuColor.jpg";
	MenuItemImages[ITM_FILL] = "images\\MenuItems\\MenuFill.jpg";
	MenuItemImages[ITM_BG] = "images\\MenuItems\\MenuBackground.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\MenuDelete.jpg";
	MenuItemImages[ITM_MOV] = "images\\MenuItems\\MenuMove.jpg";
	MenuItemImages[ITM_RSZ_QRT] = "images\\MenuItems\\MenuResize0.25.jpg";
	MenuItemImages[ITM_RSZ_HALF] = "images\\MenuItems\\MenuResize0.5.jpg";
	MenuItemImages[ITM_RSZ_DOUBLE] = "images\\MenuItems\\MenuResize2.jpg";
	MenuItemImages[ITM_RSZ_QUADRUPLE] = "images\\MenuItems\\MenuResize4.jpg";
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\MenuSendBack.jpg";
	MenuItemImages[ITM_FRNT] = "images\\MenuItems\\MenuBringFront.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\MenuSave.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\MenuLoad.jpg";
	//MenuItemImages[ITM_UNDO] = "images\\MenuItems\\MenuUndo.jpg";
	//MenuItemImages[ITM_REDO] = "images\\MenuItems\\MenuRedo.jpg";
	MenuItemImages[ITM_PLAY] = "images\\MenuItems\\MenuSwitchMode.jpg";
	MenuItemImages[ITM_EXIT_DRAW] = "images\\MenuItems\\MenuExit.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(GREY, 1);
	pWind->DrawLine(0, UI.ToolBarHeight - 1, UI.width, UI.ToolBarHeight - 1);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu

	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.height - UI.ToolBarHeight);

	string MenuItemImages2[PLAY_ITM_COUNT];
	MenuItemImages2[ITM_P_H_TYPE] = "images\\PlayModeButtons\\MenuPlayMode1.jpg";
	MenuItemImages2[ITM_P_H_FILL] = "images\\PlayModeButtons\\MenuPlayMode2.jpg";
	MenuItemImages2[ITM_P_H_BOTH] = "images\\PlayModeButtons\\MenuPlayMode3.jpg";
	MenuItemImages2[ITM_TO_DRAW] = "images\\PlayModeButtons\\MenuSwitchMode.jpg";
	MenuItemImages2[ITM_EXIT_PLAY] = "images\\MenuItems\\MenuExit.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages2[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);	
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.2), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
/*
void GUI::PrintExitAction() const //Print a string inside a button on top left to exit current action
{
	pWind->SetPen(RED, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(1080, UI.ToolBarHeight - (int)(UI.ToolBarHeight) * 2 / 3, "Exit Action");
}
*/
bool GUI::getCrntFillStatus() const	//get current fill status
{
	return UI.IsFilled;
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::setCrntDrawColor(color _color) const	//set current drwawing color
{
	UI.DrawColor = _color;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::setCrntFillColor(color _color, bool isFilled) const	//set current fill color
{
		UI.IsFilled = isFilled;
		UI.FillColor = _color;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::setCrntBackgroundColor(color _color) const	//set current background color
{
	UI.BkGrndColor = _color;
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	drawstyle style;
	if (selected)
	{
		style = INVERTED;
		if (P1.x < P2.x && P1.y < P2.y)
		{
			pWind->DrawRectangle(P1.x - 5, P1.y - 5, P2.x + 5, P2.y + 5, style);
			pWind->DrawRectangle(P1.x - 4, P1.y - 4, P2.x + 4, P2.y + 4, style);
		}
		else if (P1.x > P2.x && P1.y < P2.y)
		{
			pWind->DrawRectangle(P1.x + 5, P1.y - 5, P2.x - 5, P2.y + 5, style);
			pWind->DrawRectangle(P1.x + 4, P1.y - 4, P2.x - 4, P2.y + 4, style);
		}
		else if (P1.x < P2.x && P1.y > P2.y)
		{
			pWind->DrawRectangle(P1.x - 5, P1.y + 5, P2.x + 5, P2.y - 5, style);
			pWind->DrawRectangle(P1.x - 4, P1.y + 4, P2.x + 4, P2.y - 4, style);
		}
		else
		{
			pWind->DrawRectangle(P1.x + 5, P1.y + 5, P2.x - 5, P2.y - 5, style);
			pWind->DrawRectangle(P1.x + 4, P1.y + 4, P2.x - 4, P2.y - 4, style);
		}
	}
	DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::DrawEllipse(Point P1, Point P2, GfxInfo EllpsGfxInfo, bool selected) const
{
	color DrawingClr;
	drawstyle style;
	if (selected)
	{
		style = INVERTED;
		if (P1.x < P2.x && P1.y < P2.y)
		{
			pWind->DrawRectangle(P1.x - 5, P1.y - 5, P2.x + 5, P2.y + 5, style);
			pWind->DrawRectangle(P1.x - 4, P1.y - 4, P2.x + 4, P2.y + 4, style);
		}
		else if (P1.x > P2.x && P1.y < P2.y)
		{
			pWind->DrawRectangle(P1.x + 5, P1.y - 5, P2.x - 5, P2.y + 5, style);
			pWind->DrawRectangle(P1.x + 4, P1.y - 4, P2.x - 4, P2.y + 4, style);
		}
		else if (P1.x < P2.x && P1.y > P2.y)
		{
			pWind->DrawRectangle(P1.x - 5, P1.y + 5, P2.x + 5, P2.y - 5, style);
			pWind->DrawRectangle(P1.x - 4, P1.y + 4, P2.x + 4, P2.y - 4, style);
		}
		else
		{
			pWind->DrawRectangle(P1.x + 5, P1.y + 5, P2.x - 5, P2.y - 5, style);
			pWind->DrawRectangle(P1.x + 4, P1.y + 4, P2.x - 4, P2.y - 4, style);
		}
	}
	DrawingClr = EllpsGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, EllpsGfxInfo.BorderWdth);	//Set Drawing color & width

	if (EllpsGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(EllpsGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::DrawHexagon(Point P1, Point P2, GfxInfo HexGfxInfo, bool selected) const
{
	color DrawingClr;
	drawstyle style;
	if (selected)
	{
		style = INVERTED;
		if (P1.x < P2.x && P1.y < P2.y)
		{
			pWind->DrawRectangle(P1.x - 8, P1.y - 8, P2.x + 8, P2.y + 8, style);
			pWind->DrawRectangle(P1.x - 7, P1.y - 7, P2.x + 7, P2.y + 7, style);
		}
		else if (P1.x > P2.x && P1.y < P2.y)
		{
			pWind->DrawRectangle(P1.x + 8, P1.y - 8, P2.x - 8, P2.y + 8, style);
			pWind->DrawRectangle(P1.x + 7, P1.y - 7, P2.x - 7, P2.y + 7, style);
		}
		else if (P1.x < P2.x && P1.y > P2.y)
		{
			pWind->DrawRectangle(P1.x - 8, P1.y + 8, P2.x + 8, P2.y - 8, style);
			pWind->DrawRectangle(P1.x - 7, P1.y + 7, P2.x + 7, P2.y - 7, style);
		}
		else
		{
			pWind->DrawRectangle(P1.x + 8, P1.y + 8, P2.x - 8, P2.y - 8, style);
			pWind->DrawRectangle(P1.x + 7, P1.y + 7, P2.x - 7, P2.y - 7, style);
		}
	}
	DrawingClr = HexGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, HexGfxInfo.BorderWdth);	//Set Drawing color & width

	if (HexGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexGfxInfo.FillClr);
	}
	else
		style = FRAME;
	
	const int numVertices = 6;
	int xArray[numVertices];
	int yArray[numVertices];

	xArray[0] = P1.x;
	xArray[1] = xArray[5] = P1.x + (P2.x - P1.x) / 4;
	xArray[2] = xArray[4] = P1.x + (P2.x - P1.x) * 3 / 4;
	xArray[3] = P2.x;

	yArray[1] = yArray[2] = P1.y;
	yArray[0] = yArray[3] = P1.y + (P2.y - P1.y) / 2;
	yArray[4] = yArray[5] = P2.y;

	pWind->DrawPolygon(xArray, yArray, numVertices, style);
}
//////////////////////////////////////////////////////////////////////////////////////////

GUI::~GUI()
{
	delete pWind;
}

