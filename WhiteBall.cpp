#include "WhiteBall.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Basket.h"

//�R���X�g���N�^
WhiteBall::WhiteBall(GameObject* parent)
    :GameObject(parent, "WhiteBall")
{
    hModel_ = -1;
}

//�f�X�g���N�^
WhiteBall::~WhiteBall()
{
}

//������
void WhiteBall::Initialize()
{
    //const int WhiteConstParam::DIAMETER = 3800;

    radius = 0;
    height = 1;
    powerZ = 0;
    powerY = 0;
    throwBall = false;
    rightHaving = false;
    leftHaving = false;

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("WhiteBall.fbx");
    assert(hModel_ >= 0);

    transform_.position_ = XMFLOAT3(0, 0, 0);

    do
    {
        transform_.position_.x = (float)(rand() % DIAMETER - (DIAMETER / HALF)) / CHANGE_DECIMAL;
        transform_.position_.z = (float)(rand() % DIAMETER - (DIAMETER / HALF)) / CHANGE_DECIMAL;
       
        radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    } while (radius >= CIRCLE_RANGE || radius < NEAR_GOAL);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), BALLSIZE);
    AddCollider(collision);
}

//�X�V
void WhiteBall::Update()
{
    //�X�y�[�X�L�[����������
    if ((Input::IsKeyDown(DIK_SPACE) || throwBall == true))
    {
        //�X�y�[�X�������Ă�Ƃ�
        if (Input::IsKey(DIK_SPACE)&& (rightHaving == true || leftHaving == true))
        {
            if (rightHaving == true)
            {
                powerZ += POWER;
                //���ƂŌ����Ă�p�x�ɂ���
                powerY -= POWER;
                throwBall = true;
            }
        }
        else if (Input::IsKeyUp(DIK_SPACE))
        {
            //�{�[����2�����Ă���
            if (pPlayer1->GetHand().second == true)
            {
                pPlayer1->SetHand(false, true);
            }
            else
            {
                pPlayer1->SetHand(false, false);
            }
            //powerY + Player1�̌����Ă�p�x
        }
        else
        {
            rightHaving = false;
            leftHaving = false;
            // �����x�̉��Z
            powerY += GRAVITY;

            // �X�s�[�h�̉��Z
            transform_.position_.z += powerZ;
            transform_.position_.y -= powerY;
            powerZ *= RESISTANCE;//��R

            // �o�E���h�̔���
            if (transform_.position_.y <= 0.0f)
            {  // �{�[�������ɓ���������
                transform_.position_.y = 0.0;
                powerY = -powerY * BOUND;  // y���̃X�s�[�h�𔽓]���ċʓ�����ۂ����܂蒵�˂Ȃ�����
                height = powerY; //�����ۑ�
                powerZ *= RESISTANCE;//��R
            }
            
            //�ړ����I���
            if (powerZ <= END_MOVE)
            {
                powerZ = 0;
                powerY = 0;
                throwBall = false;
            }
        }
    }

    //�E��Ŏ����Ă���
    if (rightHaving == true)
    {
        transform_.position_ = pPlayer1->GetPosition();
        transform_.position_.x += RIGHT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;
    }

    //����Ŏ����Ă���
    if (leftHaving == true)
    {
        transform_.position_ = pPlayer1->GetPosition();
        transform_.position_.x += LEFT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;
    }

    //�{�[�����E��Ɏ���������
    if (pPlayer1->GetHand().first == false && leftHaving == true)
    {
        rightHaving = true;
        leftHaving = false;
        pPlayer1->SetHand(true, false);
    }

    //�ʂ�������
    //�^�񒆂̏Ə�����͈͌��߂ĂȂ񂩔�΂��ăN���b�N
    if (Input::IsMouseButtonDown(0))
    {

    }

    //�f�o�b�O�p
    if (Input::IsKey(DIK_B))
    {
       int a = 0;
    }

    
    ////�~�͈̔͊O�Ȃ������
    radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    if (radius > CIRCLE_OUTSIDE)
    {
        KillMe();
    }
}

//�`��
void WhiteBall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void WhiteBall::Release()
{
}

//�����蔻��
void WhiteBall::OnCollision(GameObject* pTarget)
{
    //�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Basket")
    {
        //�S�[���ɓ������瓾�_�{������
        pBasket->WhiteCount();
        KillMe();
        
        //�S�[������Ȃ������痎����

    }
    else if (pTarget->GetObjectName() == "Player1" && pPlayer1->GetHand().second == false && throwBall == false)
    {
        //�{�[���������Ă��Ȃ��Ƃ�
        if (pPlayer1->GetHand().first == false)
        {
            //�E��Ń{�[������
            pPlayer1->SetHand(true,false);
            rightHaving = true;
        }
        else
        {
            //����Ń{�[������
            pPlayer1->SetHand(true, true);
            leftHaving = true;
        }
    }
}

