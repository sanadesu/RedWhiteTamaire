#include "ResultScene.h"
#include"Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

int ResultScene::mode;

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), hPict_(-1)
{
}
//������
void ResultScene::Initialize()
{
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load("Result.png");
    assert(hPict_ >= 0);
}

//�X�V
void ResultScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//�`��
void ResultScene::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
}

//�J��
void ResultScene::Release()
{
}

