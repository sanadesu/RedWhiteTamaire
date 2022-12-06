#pragma once
#include "StateBase.h"
#include"Engine/GameObject.h"
#include"WhiteBall.h"

class State :
	public StateBase, GameObject
{
	WhiteBall* pWhiteBall = (WhiteBall*)FindObject("WhiteBall");
public:
	virtual void Action();
	void NextState(StateBase* state_);
	void Walk();

};

