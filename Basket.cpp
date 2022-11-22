#include "Basket.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include"Ball.h"

//�R���X�g���N�^
Basket::Basket(GameObject* parent)
    :GameObject(parent, "Basket"),hModel_(-1), pText(nullptr)
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

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 5, 0), 0.8f);
    AddCollider(collision);

    pText = new Text;
    pText->Initialize();

    whiteSum = 0;
    redSum = 0;
}

//�X�V
void Basket::Update()
{
    //�f�o�b�O�p
    if (Input::IsKeyDown(DIK_B))
    {
        int a = 0;
    }
}

//�`��
void Basket::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
    pText->Draw(30, 30, (whiteSum));
    pText->Draw(30, 60, (redSum));
}

//�J��
void Basket::Release()
{
}

//�����ɓ�������
void Basket::OnCollision(GameObject* pTarget)
{
    //���������Ƃ��̏���
}

//�����{�[���̍��v
void Basket::WhiteCount()
{
    //�x�N�^�[�v�Z���ďォ�瓖�������̂������_
    whiteSum++;
}

//�Ԃ��{�[���̍��v
void Basket::RedCount()
{
    redSum++;
}