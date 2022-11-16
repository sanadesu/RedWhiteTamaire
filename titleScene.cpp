#include "titleScene.h"
#include"Engine/Camera.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//�R���X�g���N�^
titleScene::titleScene(GameObject* parent)
	: GameObject(parent, "titleScene"), hPict_(-1)
{
}

//������
void titleScene::Initialize()
{

}

//�X�V
void titleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_Mode);
	}
}

//�`��
void titleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void titleScene::Release()
{
}
