#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "CFigure.h"

class CEllipse : public CFigure
{
private:
	static int count;

public:
	CEllipse(Point, Point, GfxInfo FigureGfxInfo); 
	CEllipse();
	virtual void DrawMe(GUI* pOut) const;
	void Save(ofstream& OutFile);
	void Load(ifstream&);
	bool Resize(GUI* pGUI, float factor);
};

#endif