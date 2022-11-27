#include "RedBall.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Basket.h"

//�R���X�g���N�^
RedBall::RedBall(GameObject* parent)
    :GameObject(parent, "RedBall")
{
    hModel_ = -1;
}

//�f�X�g���N�^
RedBall::~RedBall()
{
}

//������
void RedBall::Initialize()
{
    //const int RedConstParam::DIAMETER = 3800;

    key = 0;
    radius = 0;

    for (int i = 0; i < Max; i++)
    {
        height[i] = 1;
        powerZ[i] = 0;
        powerY[i] = 0;
        ballDrop[i] = 0;
        throwBall[i] = false;
        rightHaving[i] = false;
        leftHaving[i] = false;
    }

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("RedBall.fbx");
    assert(hModel_ >= 0);

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
void RedBall::Update()
{
    //��ŃL�[��ς�����悤�ɂ���for��


    for (int i = 0; i < Max; i++)
    {
        if (i == First)
        {
            key = DIK_SPACE;
        }
        else if (i == Second)
        {
            key = DIK_RETURN;
        }
        else
        {
            key = 0;
        }


        //�X�y�[�X�L�[����������
        if ((Input::IsKeyDown(key) || throwBall[i] == true))
        {
            //�X�y�[�X�������Ă�Ƃ�
            if (Input::IsKey(key) && (rightHaving[i] == true || leftHaving[i] == true))
            {
                if (rightHaving[i] == true)
                {
                    powerZ[i] += POWER;
                    //���ƂŌ����Ă�p�x�ɂ���
                    powerY[i] -= POWER;
                    throwBall[i] = true;
                }
            }
            else if (Input::IsKeyUp(key))
            {
                if (i == First)
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
                }
                else if (i == Second)
                {
                    //�{�[����2�����Ă���
                    if (pPlayer2->GetHand().second == true)
                    {
                        pPlayer2->SetHand(false, true);
                    }
                    else
                    {
                        pPlayer2->SetHand(false, false);
                    }
                }

                //powerY + Player�̌����Ă�p�x
            }
            else
            {
                rightHaving[i] = false;
                leftHaving[i] = false;
                // �����x�̉��Z
                powerY[i] += GRAVITY;

                // �X�s�[�h�̉��Z
                transform_.position_.z += powerZ[i];
                transform_.position_.y -= powerY[i];
                powerZ[i] *= RESISTANCE;//��R

                // �o�E���h�̔���
                if (transform_.position_.y <= 0.0f)
                {  // �{�[�������ɓ���������
                    transform_.position_.y = 0.0;
                    powerY[i] = -powerY[i] * BOUND;  // y���̃X�s�[�h�𔽓]���ċʓ�����ۂ����܂蒵�˂Ȃ�����
                    height[i] = powerY[i]; //�����ۑ�
                    powerZ[i] *= RESISTANCE;//��R
                }

                //�ړ����I���
                if (powerZ[i] <= END_MOVE)
                {
                    powerZ[i] = 0;
                    powerY[i] = 0;
                    throwBall[i] = false;
                }
            }
        }
    }

    //�E��Ŏ����Ă���
    if (rightHaving[First] == true)
    {
        transform_.position_ = pPlayer1->GetPosition();
        transform_.position_.x += RIGHT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;
    }
    else if (rightHaving[Second] == true)
    {
        transform_.position_ = pPlayer2->GetPosition();
        transform_.position_.x += RIGHT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;
    }

    //����Ŏ����Ă���
    if (leftHaving[First] == true)
    {
        transform_.position_ = pPlayer1->GetPosition();
        transform_.position_.x += LEFT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;
    }
    else if (leftHaving[Second] == true)
    {
        transform_.position_ = pPlayer2->GetPosition();
        transform_.position_.x += LEFT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;
    }
    //�{�[�����E��Ɏ���������
    if (pPlayer1->GetHand().first == false && leftHaving[First] == true)
    {
        rightHaving[First] = true;
        leftHaving[First] = false;
        pPlayer1->SetHand(true, false);
    }
    else if (pPlayer2->GetHand().first == false && leftHaving[Second] == true)
    {
        rightHaving[Second] = true;
        leftHaving[Second] = false;
        pPlayer2->SetHand(true, false);
    }

    if (pPlayer1->GetDamage() == true)
    {

        if (leftHaving[First] == true)
        {
            KillMe();
            leftHaving[First] = false;
        }
        else if (rightHaving[First] == true && leftHaving[First] == false)
        {
            KillMe();
            rightHaving[First] = false;

        }

        pPlayer1->SetHand(false, false);

        ballDrop[First]++;
        if (ballDrop[First] < DROP_TIME)
        {
            ballDrop[First]++;
        }
        else
        {
            pPlayer1->SetDamage(false);
            ballDrop[First] = 0;
        }
    }

    if (pPlayer2->GetDamage() == true)
    {

        if (leftHaving[Second] == true)
        {
            KillMe();
            leftHaving[Second] = false;
        }
        else if (rightHaving[Second] == true && leftHaving[Second] == false)
        {
            KillMe();
            rightHaving[Second] = false;

        }

        pPlayer2->SetHand(false, false);

        ballDrop[Second]++;
        if (ballDrop[Second] < DROP_TIME)
        {
            ballDrop[Second]++;
        }
        else
        {
            pPlayer2->SetDamage(false);
            ballDrop[Second] = 0;
        }
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
void RedBall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void RedBall::Release()
{
}

//�����蔻��
void RedBall::OnCollision(GameObject* pTarget)
{
    //�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Basket")
    {
        //�S�[���ɓ������瓾�_�{������
        pBasket->RedCount();
        KillMe();

        //�S�[������Ȃ������痎����

    }
    else if (pTarget->GetObjectName() == "Player1" && throwBall[First] == false && pPlayer1->GetDamage() == false)
    {
        //�{�[���𓖂Ă�ꂽ��
        if (throwBall[Second] == true)
        {
            pPlayer1->SetDamage(true);
        }
        //���Ń{�[���������Ă��Ȃ��Ƃ�
        else if (pPlayer1->GetHand().second == false)
        {
            if (pPlayer1->GetHand().first == false)
            {
                //�E��Ń{�[������
                pPlayer1->SetHand(true, false);
                rightHaving[First] = true;
            }
            else
            {
                //����Ń{�[������
                pPlayer1->SetHand(true, true);
                leftHaving[First] = true;
            }
        }

    }
    else if (pTarget->GetObjectName() == "Player2" && throwBall[Second] == false && pPlayer2->GetDamage() == false)
    {
        //�{�[���𓖂Ă�ꂽ��
        if (throwBall[First] == true)
        {
            pPlayer2->SetDamage(true);
        }
        //���Ń{�[���������Ă��Ȃ��Ƃ�
        else if (pPlayer2->GetHand().second == false)
        {
            //�{�[���������Ă��Ȃ��Ƃ�
            if (pPlayer2->GetHand().first == false)
            {
                //�E��Ń{�[������
                pPlayer2->SetHand(true, false);
                rightHaving[Second] = true;
            }
            else
            {
                //����Ń{�[������
                pPlayer2->SetHand(true, true);
                leftHaving[Second] = true;
            }
        }
    }
}

