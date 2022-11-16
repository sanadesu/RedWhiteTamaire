#pragma once
#include "Engine/GameObject.h"


//■■シーンを管理するクラス
class ModeScene : public GameObject
{
	int hPict_;    //画像番号
	int hPict_2;    //画像番号
	int hModel_;    //モデル番号

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ModeScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	
};