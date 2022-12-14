#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),
    hModel_(-1), pLine(nullptr)
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
    transform_.position_.x = rand() % 20;
    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1, 0), HIT_SIZE);
    AddCollider(collision);

    playerID = 0;
    key = 0;
    processID = 0;
    powerY = 0.0f;
    powerZ = 0.0f;
    trajectoryY = 0.0f;
    trajectoryZ = 0.0f;
    y_ = 10.0f; //Y���W
    moveLimit = 0.0f;
    rightHand = false;
    leftHand = false;
    damage = false;
    chargePower = false;

    pLine = new PoryLine;
    pLine->Load("tex.png");

    trans = transform_;
}

//�X�V
void Player::Update()
{
    moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    if (moveLimit > CIRCLE_RANGE)
    {
        //��ŕς���
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


    for (int i = 0; i < Max; i++)
    {
        //XMFLOAT3
        //�Ȃ���
        if (Input::IsPadButton(XINPUT_GAMEPAD_A, i) && playerID == i)
        {
            //transform_.position_ = XMFLOAT3(0, 0, 0);


            //if (rightHand == true)
            {
                //�͂��߂���
                powerY -= POWER;
                powerZ += POWER;
                trajectoryY = powerY;
                trajectoryZ = powerZ;
                //�E��̈ʒu
                trans.position_ = Model::GetBonePosition(hModel_, "joint1");
                //trans.position_ = transform_.position_;

                for (int j = 0; j < 30; j++)
                {
                    // �����x�̉��Z
                    trajectoryY += GRAVITY;


                    trans.rotate_ = transform_.rotate_;
                    XMFLOAT3 move = { 0,-trajectoryY,trajectoryZ }; //�ړ���
                    XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
                    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(trans.rotate_.y));   //Y���ł�����]������s��

                    vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
                    XMVECTOR vPos = XMLoadFloat3(&trans.position_); //���ݒn���x�N�g���ɕϊ�

                    vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

                    XMStoreFloat3(&trans.position_, vPos);

                    pLine->AddPosition(trans.position_);
                    trajectoryZ *= RESISTANCE;//��R
                }
                chargePower = true;
            }
        }
        else if (Input::IsPadButtonUp(XINPUT_GAMEPAD_A, i) && playerID == i)
        {
            pBall->SetPower(powerY, powerZ,transform_.rotate_.y);
            chargePower = false;
            powerY = 0;
            powerZ = 0;
        }

        //�E��
        if (Input::IsPadButton(XINPUT_GAMEPAD_B, i))
        {

        }//�ړ�
        if(playerID == i)
        {
            XMFLOAT3 a = Input::GetPadStickL(i);
            a.x /= 10;
            a.y /= 10;
            transform_.position_.x += a.x;
            transform_.position_.z += a.y;
        }
    }

    ////W��������O�i
    //if (Input::IsKey(DIK_W))
    //{
    //    //transform_.position_.z += 0.5;
    //    XMFLOAT3 move = { 0,0,PLAYER_MOVE }; //�ړ���
    //    XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
    //    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

    //    vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
    //    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

    //    vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

    //    XMStoreFloat3(&transform_.position_, vPos);
    //}
    ////S����������
    //if (Input::IsKey(DIK_S))
    //{
    //    XMFLOAT3 move = { 0,0,-PLAYER_MOVE };
    //    XMVECTOR vMove = XMLoadFloat3(&move);
    //    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y����90����]������s��

    //    vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
    //    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //    vPos += vMove;

    //    XMStoreFloat3(&transform_.position_, vPos);
    //}
    ////D��������E
    //if (Input::IsKey(DIK_D))
    //{
    //    XMFLOAT3 move = { PLAYER_MOVE,0,0 }; //�ړ���
    //    XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
    //    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

    //    vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
    //    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

    //    vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

    //    XMStoreFloat3(&transform_.position_, vPos);
    //}
    ////A��������
    //if (Input::IsKey(DIK_A))
    //{
    //    XMFLOAT3 move = { -PLAYER_MOVE,0,0 }; //
    //    XMVECTOR vMove = XMLoadFloat3(&move); //
    //    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y����90����]������s��
    //    vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
    //    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //

    //    vPos += vMove;

    //    XMStoreFloat3(&transform_.position_, vPos);
    //}


        //pLine->AddPosition(transform_.position_);


    

    ////�J�����ړ�
    ////�E��������E��]
    //if (Input::IsKey(key))
    //{
    //    transform_.rotate_.y++;
    //}
    ////���������獶��]
    //if (Input::IsKey(key))
    //{
    //    transform_.rotate_.y--;
    //}
    ////�E��������E��]
    //if (Input::IsKey(key))
    //{
    //    y_++;
    //}
    ////���������獶��]
    //if (Input::IsKey(key))
    //{
    //    y_--;
    //}


    ////�J����
    //XMVECTOR vCam = XMVectorSet(0.0f, y_, -CAMERA_Z, 0.0f);
    //XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //vCam = XMVector3TransformCoord(vCam, mRotate);
    //XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //XMFLOAT3 camPos;
    //XMStoreFloat3(&camPos, vPos + vCam);//�J�����̍��W

    //Camera::SetPosition(camPos);
    //Camera::SetTarget(transform_.position_);

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

    if (chargePower == true)
    {
        //�|�����C����`��
        pLine->Draw();
    }
}

//�J��
void Player::Release()
{
    //�|�����C�����
    pLine->Release();
}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    for (int i = 0; i < Max; i++)
    {
        if (pTarget->GetObjectName() == "Ball" && playerID == i)
        {
            //�����Ă�{�[���������Ă�{�[�����]�����Ă�{�[����
            //���{�[���̏�Ԏ擾���Ĕ���
            //�����ɂ͓����Ă�{�[�������ɂȂ�i���ƂŁj

            //�����Ă�{�[��
            //processID = i;
            //pWhiteBall->
            pTarget->SetPosition(Model::GetBonePosition(hModel_, "joint1"));
            //pBall->SetPlayerModel(hModel_);
            XMFLOAT3 a = Model::GetBonePosition(hModel_, "joint1");
            //a = XMFLOAT3(1, 1, 1);
            //pBall->HandPos(i,true);
            //pBall->PlayerBone(a);

            //�����Ă�{�[��
            //�����Ă�{�[��������
            //��莞�ԏE���Ȃ�
            //�_��
        }
    }
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

Transform Player::GetPlayerPosition(bool right)
{
    Transform trans_ = transform_;

    //trans.rotate_.y += 120;
    //trans.position_.x += x_;
    //trans.position_.y += HAND_HEIGHT;

    if (right == true)
    {
        trans_.position_ = Model::GetBonePosition(hModel_, "joint1");
    }
    else
    {
        trans_.position_ = Model::GetBonePosition(hModel_, "joint2");
    }

    return trans_;
}

