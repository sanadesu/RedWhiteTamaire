#pragma once
#include "Engine/Direct3D.h"

class StateBase
{
public:
	//static StandingState standing;
	//virtual ~StateBase() {};
	//virtual void Update() {};
	//------------------------歩く------------------------
	//敵が見えていてボールを1個持ってたら→近いボールまで
	//違ったら自分のボールまで


	virtual void Action() = 0;

	virtual StateBase* NextState() = 0;

	XMFLOAT3 pos;
	//------------------------拾う------------------------
	//見えてる敵が1個ボール持ってない時→もう一個自分ボール拾いに行ったり行かなかったり

	//-----------------------投げる-----------------------
	//見えてる敵が1個ボール持ってる＆投げようとしてない→敵に向かって投げる
	//違う↓ 
	//自分ボールの時→ゴールへ
	//敵ボール→すぐ離す？外に出す？




};

