#ifndef PICK_BY_BOTH_H
#define PICK_BY_BOTH_H

#include "./Action.h"

class PickByBoth : public Action
{
public:
	PickByBoth(ApplicationManager* pApp);
	void Execute();

};

#endif