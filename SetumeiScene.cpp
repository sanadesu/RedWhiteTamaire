#include "SetumeiScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//コンストラクタ
SetumeiScene::SetumeiScene(GameObject* parent)
	: GameObject(parent, "SetumeiScene"), hPict_(-1)
{
}

//初期化
void SetumeiScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Setumei.jpg");
	assert(hPict_ >= 0);
}

//更新
void SetumeiScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void SetumeiScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void SetumeiScene::Release()
{
}
