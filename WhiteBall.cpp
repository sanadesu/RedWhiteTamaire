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
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("WhiteBall.fbx");
    assert(hModel_ >= 0);

    transform_.position_ = XMFLOAT3(0, 0, 0);

    do
    {
        transform_.position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
        transform_.position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
        radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    } while (radius > 360 || radius < 15);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.18f);
    AddCollider(collision);

    radius = 0;
    whiteCount = 0;
    height = 1;
    powerX = 0;
    powerY = 0;
    playerAngleY = 0;
    throwBall = false;
    down = false;
    rightHaving = false;
    leftHaving = false;
}

//�X�V
void WhiteBall::Update()
{
    //�X�y�[�X�L�[����������
    if ((Input::IsKeyDown(DIK_SPACE) || throwBall == true))
    {
        
        //�X�y�[�X�������Ă�Ƃ�
        if (Input::IsKey(DIK_SPACE) && (rightHaving == true || leftHaving == true))
        {
            if (rightHaving == true)
            {
                powerX += 0.01;
                //���ƂŌ����Ă�p�x�ɂ���
                powerY -= 0.01;
                throwBall = true;
            }
        }
        else if (Input::IsKeyUp(DIK_SPACE))
        {
            //powerY -= playerAngleY;//�v���C���[�̊p�x
            if (pPlayer->GetHand().second == true)
            {
                pPlayer->SetHand(false, true);
                //leftHaving = false;
                //rightHaving = true;
            }
            else
            {
                pPlayer->SetHand(false, false);
               
            }
            
        }
        else
        {
            rightHaving = false;
            leftHaving = false;
            // �����x�̉��Z
            powerY += GRAVITY;

            // �X�s�[�h�̉��Z
            transform_.position_.z += powerX;
            transform_.position_.y -= powerY;
            powerX *= 0.97;

            // �o�E���h�̔���
            if (transform_.position_.y <= 0.0f)
            {  // �{�[������ʉ��ɓ���������
                transform_.position_.y = 0.0;
                powerY = -powerY * BOUND;  // y���̃X�s�[�h�𔽓]���ċʓ�����ۂ����܂蒵�˂Ȃ�����
                height = powerY; //�����ۑ�
                powerX *= 0.98;
            }
        }

        //�������ړ����I���
        if (powerX <= 0.001 && abs(height) <= 0.021)
        {
            powerX = 0;
            powerY = 0;
            throwBall = false;
        }
        
    }

    if (rightHaving == true)
    {
        transform_.position_ = pPlayer->GetPosition();
        transform_.position_.x += 1;
        transform_.position_.y += 2.5;
    }

    if (leftHaving == true)
    {
        transform_.position_ = pPlayer->GetPosition();
        transform_.position_.x += -1;
        transform_.position_.y += 2.5;
    }

    if (pPlayer->GetHand().first == false && leftHaving == true)
    {
        rightHaving = true;
        leftHaving = false;
        pPlayer->SetHand(true, false);

    }

    /*if (pPlayer->GetHand().first == false && rightHaving == true)
    {
        rightHaving = false;
        leftHaving = false;
        pPlayer->SetHand(false, false);
    }*/

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

    //���V�t�g�������猳�ɖ߂��A��ŏ���
    if (Input::IsKeyDown(DIK_LSHIFT))
    {
        throwBall = false;
        transform_.position_ = XMFLOAT3(3, 3, 3);
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
    else if (pTarget->GetObjectName() == "Player" && pPlayer->GetHand().second == false)
    {
        //�{�[���������Ă��Ȃ��Ƃ�
        if (pPlayer->GetHand().first == false)
        {
            //�E��Ń{�[������
            pPlayer->SetHand(true,false);
            rightHaving = true;
        }
        else
        {
            //����Ń{�[������
            pPlayer->SetHand(true, true);
            leftHaving = true;
        }
    }
}