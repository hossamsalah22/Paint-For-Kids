#ifndef PICK_BY_FILL_H
#define PICK_BY_FILL_H

#include "./Action.h"

class PickByFill : public Action
{
public:
	PickByFill(ApplicationManager* pApp);
	void Execute();

};

#endif