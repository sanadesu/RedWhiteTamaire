#include "Player1.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"

//�R���X�g���N�^
Player1::Player1(GameObject* parent)
    :GameObject(parent, "Player1"),
    hModel_(-1)
{

}

//�f�X�g���N�^
Player1::~Player1()
{

}

//������
void Player1::Initialize()
{
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    //trans.position_ = XMFLOAT3(0, 0, -3);
    transform_.position_ = XMFLOAT3(START_POS_X, 0, START_POS_Z);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1, 0), HIT_SIZE);
    AddCollider(collision);

    y_ = 10.0f; //Y���W
    moveLimit = 0.0f;
    rightHand = false;
    leftHand = false;
    damage = false;
}

//�X�V
void Player1::Update()
{
    moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    if (moveLimit > CIRCLE_RANGE)
    {
        if (transform_.position_.x < 0)
        {
            a[0] = true;
            //transform_.position_.x += RETURN_MOVE;
        }
        else if(transform_.position_.x > 0)
        {
            a[1] = true;
            //transform_.position_.x -= RETURN_MOVE;
        }

        if (transform_.position_.z < 0)
        {
            a[2] = true;
            //transform_.position_.z += RETURN_MOVE;
        }
        else if(transform_.position_.z > 0)
        {
            a[3] = true;
            //transform_.position_.z -= RETURN_MOVE;
        }
        
    }
    else
    {
        a[0] = false;
        a[1] = false;
        a[2] = false;
        a[3] = false;
    }
    //else
    {
        //W��������O�i
        if (Input::IsKey(DIK_W)&& a[3] == false)
        {
            //transform_.position_.z += 0.5;
            XMFLOAT3 move = { 0,0,PLAYER_MOVE }; //�ړ���
            XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

            vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

            XMStoreFloat3(&transform_.position_, vPos);
        }
        //S����������
        if (Input::IsKey(DIK_S) && a[2] == false)
        {
            XMFLOAT3 move = { 0,0,-PLAYER_MOVE }; 
            XMVECTOR vMove = XMLoadFloat3(&move); 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y����90����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); 

            vPos += vMove; 

            XMStoreFloat3(&transform_.position_, vPos); 
        }
        //D��������E
        if (Input::IsKey(DIK_D) && a[1] == false)
        {
            XMFLOAT3 move = { PLAYER_MOVE,0,0 }; //�ړ���
            XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

            vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

            XMStoreFloat3(&transform_.position_, vPos);
        }
        //A��������
        if (Input::IsKey(DIK_A) && a[0] == false)
        {
            XMFLOAT3 move = { -PLAYER_MOVE,0,0 }; //
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
    XMVECTOR vCam = XMVectorSet(0.0f, y_, -CAMERA_Z, 0.0f);
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);//�J�����̍��W

    Direct3D::SetViewPort(0);
    Camera::SetPosition(camPos);
    Camera::SetTarget(transform_.position_);



    //�f�o�b�O�p
    if (Input::IsKeyDown(DIK_B))
    {
        int a = 0;
    }
}

//�`��
void Player1::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Player1::Release()
{
  
}

//�����ɓ�������
void Player1::OnCollision(GameObject* pTarget)
{
    //���������Ƃ��̏���
}

//�p�x�擾
float Player1::GetAngle()
{
    return 0;
}

//�{�[��������
void Player1::SetHand(bool rightHand_,bool leftHand_)
{
    rightHand = rightHand_;
    leftHand = leftHand_;
}

//�{�[���������Ă��邩
std::pair<bool, bool> Player1::GetHand()
{
    return std::make_pair(rightHand, leftHand);
}

void Player1::SetDamage(bool damage_)
{
    damage = damage_;
}

bool Player1::GetDamage()
{
    return damage;
}

XMFLOAT3 Player1::GetPlayerPosition(float x_)
{
    Transform trans = transform_;

    /*trans.position_.x += x_;
    trans.position_.y += 2.5f;*/
    if (x_ > 0)
    {
        trans.position_ = Model::GetBonePosition(hModel_, "joint1");
    }
    else
    {
        trans.position_ = Model::GetBonePosition(hModel_, "joint2");
    }
   

    return trans.position_;
}

XMFLOAT3 Player1::GetPlayerRotate()
{
    Transform trans = transform_;
    trans.rotate_.y += 120;
    return trans.rotate_;
}