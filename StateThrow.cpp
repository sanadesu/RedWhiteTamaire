#include "StateThrow.h"
class StateWalk;

void StateThrow::Action()
{
}

StateBase* StateThrow::NextState()
{
	return(new StateWalk);
}
