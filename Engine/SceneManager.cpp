#include "sceneManager.h"

#include "../TestScene.h"
#include "../titleScene.h"
#include "../ModeScene.h"
#include "../SetumeiScene.h"
#include "../PlayScene.h"
#include "../GameoverScene.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "../ClearScene.h"

//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//初期化
void SceneManager::Initialize()
{
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_PLAY;
	nextSceneID_ = currentSceneID_;
	Instantiate<PlayScene>(this);//タイトルからスタートになおす
}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//ロードしたデータを全削除
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<titleScene>(this); break;
		case SCENE_ID_Mode: Instantiate<ModeScene>(this); break;
		case SCENE_ID_Setumei: Instantiate<SetumeiScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_Clear: Instantiate<ClearScene>(this); break;
		case SCENE_ID_Gameover: Instantiate<GameoverScene>(this); break;
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
}

//描画
void SceneManager::Draw()
{
}

//開放
void SceneManager::Release()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}