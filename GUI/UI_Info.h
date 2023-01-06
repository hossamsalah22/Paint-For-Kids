#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SLCT,		//Select shapes
	ITM_SQUR,		//Draw square
	ITM_ELPS,		//Draw ellipse 
	ITM_HEX,		//Draw hexagon
	ITM_CLR,		//Change shape color
	ITM_FILL,		//Change shape filling
	ITM_BG,			//Change background color
	ITM_DEL,		//Delete shape
	ITM_MOV,		//Move shape
	ITM_RSZ_QRT,		//Resize shape
	ITM_RSZ_HALF,		//Resize shape
	ITM_RSZ_DOUBLE,		//Resize shape
	ITM_RSZ_QUADRUPLE,		//Resize shape
	ITM_BACK,		//Send shape to back
	ITM_FRNT,		//Bring shape to front
	ITM_SAVE,		//Save graph
	ITM_LOAD,		//Load graph
	ITM_UNDO,		//Undo action
	ITM_REDO,		//Redo action
	ITM_PLAY,		//Switch mode
	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here

	//TODO: Add more items names here
	ITM_P_H_TYPE,		//Play and hide by type item in menu
	ITM_P_H_FILL,
	ITM_P_H_BOTH,
	ITM_TO_DRAW,

	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};





__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	
	bool IsFilled;
	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif