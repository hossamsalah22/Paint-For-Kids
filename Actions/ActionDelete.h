#ifndef ACTION_DELETE_H
#define ACTION_DELETE_H
#include "Action.h"
#pragma once

class ActionDelete : public Action
{
public:
	ActionDelete(ApplicationManager* pApp);

	//Add Square to the ApplicationManager
	virtual void Execute();
};
#endif
