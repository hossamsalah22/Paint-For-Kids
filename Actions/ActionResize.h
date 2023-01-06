#ifndef ACTION_RESIZE_H
#define ACTION_RESIZE_H
#include "Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#pragma once

class ActionResize : public Action
{
private:
	float resizeFactor;
public:
	ActionResize(ApplicationManager* pApp, float factor);
	virtual void Execute();
};
#endif
