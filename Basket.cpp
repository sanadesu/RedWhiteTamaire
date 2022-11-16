#include "Basket.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"

//�R���X�g���N�^
Basket::Basket(GameObject* parent)
    :GameObject(parent, "Basket"),hModel_(-1)
{

}

//�f�X�g���N�^
Basket::~Basket()
{
}

//������
void Basket::Initialize()
{
    hModel_ = Model::Load("Goal.fbx");
    assert(hModel_ >= 0);

    
    transform_.position_ = XMFLOAT3(0, 0, 0);
}

//�X�V
void Basket::Update()
{
}

//�`��
void Basket::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Basket::Release()
{
}

