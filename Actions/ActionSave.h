#ifndef ACTION_SAVE_H
#define ACTION_SAVE_H

#include "Action.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class ActionSave : public Action
{
private:
	string FileName;
	int FigCnt;
	bool fireExit;
public:
	ActionSave(ApplicationManager*, int, bool);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif