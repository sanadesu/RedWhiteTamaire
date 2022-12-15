#include "StateWalk.h"
class StateThrow;

void StateWalk::Action()
{
    pos.x += 0.1;
}

StateBase* StateWalk::NextState()
{
    return(new StateThrow);
}
