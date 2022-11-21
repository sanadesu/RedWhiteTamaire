#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),
    hModel_(-1)
{

}

//�f�X�g���N�^
Player::~Player()
{

}

//������
void Player::Initialize()
{
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    //trans.position_ = XMFLOAT3(0, 0, -3);
    transform_.position_ = XMFLOAT3(0, -0.5, -3);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1, 0), 1.2f);
    AddCollider(collision);

    y_ = 10.0f; //Y���W
    moveLimit = 0.0f;
    rightHand = false;
    leftHand = false;
}

//�X�V
void Player::Update()
{
    moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    if (moveLimit > 360)
    {
        if (transform_.position_.x < 0)
        {
            transform_.position_.x += 0.01f;
        }
        else if(transform_.position_.x > 0)
        {
            transform_.position_.x -= 0.01f;
        }

        if (transform_.position_.z < 0)
        {
            transform_.position_.z += 0.1f;
        }
        else if(transform_.position_.z > 0)
        {
            transform_.position_.z -= 0.1f;
        }
    }
    else
    {
        //W��������O�i
        if (Input::IsKey(DIK_W))
        {
            //transform_.position_.z += 0.5;
            XMFLOAT3 move = { 0,0,MOVE }; //�ړ���
            XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

            vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

            XMStoreFloat3(&transform_.position_, vPos);
        }
        //S����������
        if (Input::IsKey(DIK_S))
        {
            XMFLOAT3 move = { 0,0,-MOVE }; 
            XMVECTOR vMove = XMLoadFloat3(&move); 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y����90����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); 

            vPos += vMove; 

            XMStoreFloat3(&transform_.position_, vPos); 
        }
        //D��������E
        if (Input::IsKey(DIK_D))
        {
            XMFLOAT3 move = { MOVE,0,0 }; //�ړ���
            XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

            vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

            XMStoreFloat3(&transform_.position_, vPos);
        }
        //S����������
        if (Input::IsKey(DIK_A))
        {
            XMFLOAT3 move = { -MOVE,0,0 }; //
            XMVECTOR vMove = XMLoadFloat3(&move); //
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y����90����]������s��
            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //

            vPos += vMove; 

            XMStoreFloat3(&transform_.position_, vPos); 
        }
    }
    //�J�����ړ�
    //�E��������E��]
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y++;
    }
    //���������獶��]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y--;
    }
    //�E��������E��]
    if (Input::IsKey(DIK_UP))
    {
        y_++;
    }
    //���������獶��]
    if (Input::IsKey(DIK_DOWN))
    {
        y_--;
    }
    

    //�J����
    XMVECTOR vCam = XMVectorSet(0.0f, y_, -Z_, 0.0f);
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);//�J�����̍��W

    Camera::SetPosition(camPos);
    Camera::SetTarget(transform_.position_);

    //�f�o�b�O�p
    if (Input::IsKeyDown(DIK_B))
    {
        int a = 0;
    }
}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
  
}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    //���������Ƃ��̏���
}

//�p�x�擾
float Player::GetAngle()
{
    return 0;
}

//�{�[��������
void Player::SetHand(bool rightHand_,bool leftHand_)
{
    rightHand = rightHand_;
    leftHand = leftHand_;
}

//�{�[���������Ă��邩
std::pair<bool, bool> Player::GetHand()
{
    return std::make_pair(rightHand, leftHand);
}

