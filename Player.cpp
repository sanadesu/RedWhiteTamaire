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
    transform_.position_ = XMFLOAT3(START_POS_X, 0, START_POS_Z);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1, 0), HIT_SIZE);
    AddCollider(collision);

    key = 0;
    y_ = 10.0f; //Y���W
    moveLimit = 0.0f;
    rightHand = false;
    leftHand = false;
    damage = false;
}

//�X�V
void Player::Update()
{
    moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    if (moveLimit > CIRCLE_RANGE)
    {
        if (transform_.position_.x < 0)
        {
            transform_.position_.x += RETURN_MOVE;
        }
        else if (transform_.position_.x > 0)
        {
            transform_.position_.x -= RETURN_MOVE;
        }

        if (transform_.position_.z < 0)
        {
            transform_.position_.z += RETURN_MOVE;
        }
        else if (transform_.position_.z > 0)
        {
            transform_.position_.z -= RETURN_MOVE;
        }
    }
    else
    {
        for (int i = 0; i < Max; i++)
        {
            if (Input::IsPadButton(XINPUT_GAMEPAD_A, i))
            {

            }
            if(Input::IsPadButton(XINPUT_GAMEPAD_LEFT_THUMB, i))
            {
                Input::GetPadStickL();
            }
        }
        






        //W��������O�i
        if (Input::IsKey(key))
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
        if (Input::IsKey(key))
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
        if (Input::IsKey(key))
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
        if (Input::IsKey(key))
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
    if (Input::IsKey(key))
    {
        transform_.rotate_.y++;
    }
    //���������獶��]
    if (Input::IsKey(key))
    {
        transform_.rotate_.y--;
    }
    //�E��������E��]
    if (Input::IsKey(key))
    {
        y_++;
    }
    //���������獶��]
    if (Input::IsKey(key))
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
void Player::SetHand(bool rightHand_, bool leftHand_)
{
    rightHand = rightHand_;
    leftHand = leftHand_;
}

//�{�[���������Ă��邩
std::pair<bool, bool> Player::GetHand()
{
    return std::make_pair(rightHand, leftHand);
}

void Player::SetDamage(bool damage_)
{
    damage = damage_;
}

bool Player::GetDamage()
{
    return damage;
}

Transform Player::GetPlayerPosition(float x_)
{
    Transform trans = transform_;

    //trans.rotate_.y += 120;
    trans.position_.x += x_;
    trans.position_.y += HAND_HEIGHT;
    return trans;
}
