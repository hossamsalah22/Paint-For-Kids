#ifndef PICK_BY_TYPE_H
#define PICK_BY_TYPE_H

#include "./Action.h"

class PickByType : public Action
{
public:
	PickByType(ApplicationManager* pApp);
	void Execute();

};

#endif