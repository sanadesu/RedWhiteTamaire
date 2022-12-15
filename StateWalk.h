#pragma once
#include "StateBase.h"
#include "StateThrow.h"

class StateWalk : 
	public StateBase
{
	void Action() override;

	StateBase* NextState() override;
};

