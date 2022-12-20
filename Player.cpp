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

    nowState = WALK_STATE;
    playerID = 0;
    key = 0;
    processID = 0;
    rightHand = -1;
    leftHand = -1;
    powerY = 0.0f;
    powerZ = 0.0f;
    trajectoryY = 0.0f;
    trajectoryZ = 0.0f;
    y_ = 10.0f; //Y���W
    moveLimit = 0.0f;
    goalLength = 0.0f;
   /* rightHand = false;
    leftHand = false;*/
    damage = false;
    chargePower = false;
    prevPos = transform_;

    pLine = new PoryLine;
    pLine->Load("tex.png");

    trans = transform_;
}

//�X�V
void Player::Update()
{
    if (playerID == 0)
    {
        switch (nowState)
        {
        case WALK_STATE:
            if (moveLimit > CIRCLE_RANGE)
            transform_.rotate_.y += 137;


            XMFLOAT3 move = { 0,0,PLAYER_MOVE }; //�ړ���
            XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

            vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

            XMStoreFloat3(&transform_.position_, vPos);

            if (pBallRight != nullptr)
            {
                nowState = CHARGE_STATE;
            }
            break;
        case CHARGE_STATE:
            XMFLOAT3 origine = XMFLOAT3(0,0,0);
            XMVECTOR vOrigin = XMLoadFloat3(&origine);
            XMFLOAT3 HandPos = Model::GetBonePosition(hModel_, "joint1");
            XMVECTOR vPlayerPos = XMLoadFloat3(&HandPos);
            XMVECTOR vGoal = vOrigin - vPlayerPos; //�S�[���ւ̌���

            XMVECTOR vGoalLength = XMVector3Length(vGoal);
            goalLength = XMVectorGetX(vGoalLength);

            XMFLOAT3 vGoalRotate; 	

            XMStoreFloat3(&vGoalRotate, vGoal);

            transform_.rotate_.y = atan2(vGoalRotate.x, vGoalRotate.z) * 180.0 / 3.14;

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
            if (powerZ > powf(goalLength,0.5) * ((rand() % 30 / 1000) + 0.20))
            {
                nowState = THROW_STATE;
            }
            break;
        case THROW_STATE://�{�[��������
            if (rightHand == pBallRight->GetBallNum())
            {
                pBallRight->SetPower(powerY, powerZ, transform_.rotate_.y);
                chargePower = false;
                powerY = 0;
                powerZ = 0;
                rightHand = leftHand;
                leftHand = -1;
                pBallRight = pBallLeft;
                pBallLeft = nullptr;
                nowState = WALK_STATE;
            }
            break;
        default:
            break;
        }
    }
   


    if (pBallRight != nullptr)
    {
        pBallRight->PlayerBone(Model::GetBonePosition(hModel_, "joint1"));
    }
    if (pBallLeft != nullptr)
    {
        pBallLeft->PlayerBone(Model::GetBonePosition(hModel_, "joint2"));
    }

    moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);

    if (moveLimit > CIRCLE_RANGE)
    {
        //��ŕς���
        if (transform_.position_.x < 0)
        {
            transform_.position_.x = prevPos.position_.x;
        }
        else if (transform_.position_.x > 0)
        {
            transform_.position_.x = prevPos.position_.x;
        }

        if (transform_.position_.z < 0)
        {
            transform_.position_.z = prevPos.position_.z;
        }
        else if (transform_.position_.z > 0)
        {
            transform_.position_.z = prevPos.position_.z;
        }
    }

    prevPos = transform_;


    for (int i = 0; i < MAX; i++)
    {
        //XMFLOAT3
        //�Ȃ���
        if (Input::IsPadButton(XINPUT_GAMEPAD_A, i) && playerID == i && rightHand >= 0)
        {
            //transform_.position_ = XMFLOAT3(0, 0, 0);

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
        else if (Input::IsPadButtonUp(XINPUT_GAMEPAD_A, i) && playerID == i && rightHand >= 0)
        {
            if (rightHand == pBallRight->GetBallNum())
            {
                pBallRight->SetPower(powerY, powerZ, transform_.rotate_.y);
                chargePower = false;
                powerY = 0;
                powerZ = 0;
                rightHand = leftHand;
                leftHand = -1;
                pBallRight = pBallLeft;
                pBallLeft = nullptr;
            }
            
        }

        //�E��
        if (Input::IsPadButton(XINPUT_GAMEPAD_B, i))
        {

        }//�ړ�
        if(playerID == i)
        {
            XMFLOAT3 LeftStick = Input::GetPadStickL(i);
            LeftStick.x /= 10;
            LeftStick.y /= 10;
            /*transform_.position_.x += LeftStick.x;
            transform_.position_.z += LeftStick.y;*/

            XMFLOAT3 move = { LeftStick.x,0,LeftStick.y }; //�ړ���
            XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

            vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

            XMStoreFloat3(&transform_.position_, vPos);

            XMFLOAT3 RightSrick = Input::GetPadStickR(i);
            //RightSrick.x /= 2;
            RightSrick.y /= 4;
            transform_.rotate_.y += RightSrick.x;
            y_ += RightSrick.y;
            //hdri
            //�|���w�u��
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
    for (int i = 0; i < MAX; i++)
    {
        //�{�[���ɂ����違�ǂ̃v���C���[�����{�[�������ĂȂ���
        if (pTarget->GetObjectName() == "Ball" && playerID == i)
        {
           

            //�����Ă�{�[���������Ă�{�[�����]�����Ă�{�[����
            //���{�[���̏�Ԏ擾���Ĕ���
            //�����ɂ͓����Ă�{�[�������ɂȂ�i���ƂŁj
            pBallThrow = (Ball*)pTarget;
            if (pBallThrow->GetIsThrow() == true)
            {
                rightHand = -1;
                leftHand = -1;
                if (pBallRight != nullptr)
                {
                    pBallRight->KillMe();
                    pBallRight = nullptr;
                }
                if (pBallLeft != nullptr)
                {
                    pBallLeft->KillMe();
                    pBallLeft = nullptr;
                }
               

            } //�݂��Ă����Ă�
            else if (rightHand < 0)
            {
                //�����Ă�{�[��
                //processID = i;
                //pWhiteBall->
                pBallRight = (Ball*)pTarget;
                //pBall->SetPosition(Model::GetBonePosition(hModel_, "joint1"));
                //pBallRight->PlayerBone(Model::GetBonePosition(hModel_, "joint1"));
                //���������{�[���̔ԍ��m�肽��
                rightHand = pBallRight->GetBallNum();
                
                //pBall->SetPlayerModel(hModel_);
                //XMFLOAT3 a = Model::GetBonePosition(hModel_, "joint1");
                //a = XMFLOAT3(1, 1, 1);
                //pBall->HandPos(i,true);
                //pBall->PlayerBone(a);
            }//����
            else if(leftHand < 0)
            {
                pBallLeft = (Ball*)pTarget;
                leftHand = pBallLeft->GetBallNum();
            }
           

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

