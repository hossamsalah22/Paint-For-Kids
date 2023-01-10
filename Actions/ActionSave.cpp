
#include "ActionSave.h"

ActionSave::ActionSave(ApplicationManager* pApp, int FigCount, bool exit = false) : Action(pApp)
{
	FileName = "temp_name";
	FigCnt = FigCount;
	fireExit = exit;
}

void ActionSave::ReadActionParameters()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->ClearStatusBar();
	pGUI->PrintMessage("Enter File Name");
	FileName = pGUI->GetSrting(); 
}

void ActionSave::Execute()
{
	pManager->ResetPoint();
	ReadActionParameters();
	GUI* pGUI = pManager->GetGUI();

	ofstream OutFile;   //object of ofstream to write on the disk
	OutFile.open("SavedFiles\\" + FileName + ".txt");  // create a text file to save each figure details

	//adding UI info to the output
	OutFile << pManager->colorString(UI.DrawColor)
		<< "\t" << pManager->colorString(UI.FillColor)
		<< "\t" << pManager->colorString(UI.BkGrndColor) << "\n";
	OutFile << FigCnt << "\n";

	pManager->SaveAll(OutFile);  //Saving each figure details
	OutFile.close();
	pGUI->PrintMessage("File Saved!");

	if (fireExit) {
		exit(0);
	}
}
