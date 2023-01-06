#ifndef CHEXAGON_H
#define CHEXAGON_H

#include "CFigure.h"

class CHexagon : public CFigure
{
private:
	static int count;

public:
	CHexagon(Point, Point, GfxInfo FigureGfxInfo);
	CHexagon();
	virtual void DrawMe(GUI* pOut) const;
	void Save(ofstream&);
	void Load(ifstream&);
	bool Resize(float factor, GUI* pGUI);
};

#endif