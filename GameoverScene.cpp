#include "GameoverScene.h"
#include "Engine/Image.h"
#include"Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//�R���X�g���N�^
GameoverScene::GameoverScene(GameObject* parent)
	: GameObject(parent, "GameoverScene"), hPict_(-1)
{
}

//������
void GameoverScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Gameover.jpg");
	assert(hPict_ >= 0);
}

//�X�V
void GameoverScene::Update()
{
    //�^�C�g����
    if (Input::IsKeyDown(DIK_1))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TITLE);
    }

    //���[�h�I����
    if (Input::IsKeyDown(DIK_2))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_Mode);
    }

    //������x
    if (Input::IsKeyDown(DIK_3))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_PLAY);
    }
}

//�`��
void GameoverScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void GameoverScene::Release()
{
}