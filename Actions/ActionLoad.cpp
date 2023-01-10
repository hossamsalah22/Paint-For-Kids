#include "ActionLoad.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CEllipse.h"
#include "..\Figures\CHexagon.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include "String.h"
#include<iostream>
#include <direct.h>

ActionLoad::ActionLoad(ApplicationManager* pApp, int FigCount) : Action(pApp)
{
	FileName = "temp";
	FigCnt = FigCount;    //We need the figure number to write it on the file
}


bool ActionLoad::ReadFileLocation(char szFileName[])
{
	OPENFILENAME openedFile;
	const char* FilterSpec = "txt\0";
	const char* Title = "Choose File To Load ...";

	char szFileTitle[MAX_PATH] = "";

	*szFileName = 0;

	/* fill in non-variant fields of OPENFILENAME struct. */
	openedFile.lStructSize = sizeof(OPENFILENAME);
	openedFile.hwndOwner = GetFocus();
	openedFile.lpstrFilter = FilterSpec;
	openedFile.lpstrCustomFilter = NULL;
	openedFile.nMaxCustFilter = 0;
	openedFile.nFilterIndex = 0;
	openedFile.lpstrFile = szFileName;
	openedFile.nMaxFile = MAX_PATH;
	openedFile.lpstrInitialDir = "."; // Initial directory.
	openedFile.lpstrFileTitle = szFileTitle;
	openedFile.nMaxFileTitle = MAX_PATH;
	openedFile.lpstrTitle = Title;
	openedFile.lpstrDefExt = 0; // I've set to null for demonstration
	openedFile.Flags = OFN_FILEMUSTEXIST;

	// false if failed or cancelled
	return GetOpenFileName(&openedFile);
}

void ActionLoad::Execute()
{
	pManager->ResetPoint();

	char* homePath = _getcwd(NULL, 1024);

	char openedFileName[MAX_PATH];

	GUI* pGUI = pManager->GetGUI();
	ifstream InputFile;   //object of ifstream to write on the disk
	if (ReadFileLocation(openedFileName))
	{
		InputFile.open(openedFileName);  // openedFileName holds the path of the loaded file
		pGUI->ClearDrawArea();

		if (InputFile.is_open())
		{
			//read Data From The File
			CFigure* pFig = NULL;
			int numberOfFiguers;
			string DrawClr, FillClr, BgClr;
			InputFile >> DrawClr;
			UI.DrawColor = pManager->ColorObject(DrawClr);

			InputFile >> FillClr;
			UI.FillColor = pManager->ColorObject(FillClr);

			InputFile >> BgClr;
			UI.BkGrndColor = pManager->ColorObject(BgClr);

			InputFile >> numberOfFiguers;

			pManager->ClearFigList();

			for (int i = 0; i < numberOfFiguers; i++)
			{
				string figureName;
				InputFile >> figureName;
				if (figureName == "CSquare") {
					pFig = new CSquare;
				}
				else if (figureName == "CEllipse") {
					pFig = new CEllipse;
				}
				else if (figureName == "CHexagon") {
					pFig = new CHexagon;
				}
				//loading the parameters of each figure 
				pFig->Load(InputFile);
				if (pFig != NULL)
				{
					pManager->AddFigure(pFig);
				}
			};
			pManager->UpdateInterface();
			pGUI->PrintMessage("Graph Loaded Successfully");
			Sleep(1000);
			pGUI->ClearStatusBar();
			InputFile.close(); //close the file after looping 
		}
	}
	else
	{
		pGUI->PrintMessage("User cancelled the operation");
	}
	_chdir(homePath); // Go back one step to the main directory
}