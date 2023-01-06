#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	static int count;
	
public:
	CSquare(Point , Point, GfxInfo FigureGfxInfo );
	CSquare();
	virtual void DrawMe(GUI* pOut) const;
	void Save(ofstream&);
	void Load(ifstream&);
	bool Resize(GUI* pGUI, float factor);
};

#endif