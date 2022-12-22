#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//■■シーンを管理するクラス
class PlayScene : public GameObject
{
	int hPict_;    //画像番号

	const int ALL_BALL = 80;
	const int END_TIME = 7200;
	int time;
	int playerNumber;	
	Text* pText;
	Player* p1;
	Player* p2;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};