//#include "Ball.h"
//#include "Engine/Model.h"
//#include "Engine/Input.h"
//
////�R���X�g���N�^
//Ball::Ball(GameObject* parent)
//    :GameObject(parent, "Ball")
//{
//    transform_.position_.y = 0;
//    radius = 0.0f;
//    height = 0.0f;
//    throwBall = false;
//
//    do
//    {
//        transform_.position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
//        transform_.position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
//        radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
//    } while (radius > 360 || radius < 15);
//
//    //�����蔻��
//    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.18f);
//    AddCollider(collision);
//
//    
//    //memset(hModel_, -1, sizeof(hModel_));
//}
//
////�f�X�g���N�^
//Ball::~Ball()
//{
//}
//
//void Ball::ThrowBall(int buttonCode_, float angle_, float powerX_, float powerY_)
//{
//    //// �����x�̉��Z
//    //powerY_ += GRAVITY;
//    //// �X�s�[�h�̉��Z
//    //transform_.position_.z += powerX_;
//    //transform_.position_.y -= powerY_;
//    //powerX_ *= 0.97;
//
//    //// �o�E���h�̔���
//    //if (transform_.position_.y <= 0.0f)
//    //{  // �{�[������ʉ��ɓ���������
//    //    transform_.position_.y = 0.0;
//    //    powerY_ = -powerY_ * BOUND;  // y���̃X�s�[�h�𔽓]���ċʓ�����ۂ����܂蒵�˂Ȃ�����
//    //    height = powerY_; //�����ۑ�
//    //}
//
//    if (Input::IsKeyDown(buttonCode_) || throwBall == true)
//    {
//        throwBall = true;
//        //�X�y�[�X���������Ƃ�
//        if (Input::IsKey(buttonCode_))
//        {
//            powerX_ += 0.01;
//            //���ƂŌ����Ă�p�x�ɂ���
//            powerY_ -= 0.01;
//
//            //�{�[���������Ă���
//            //if ()
//            //{
//            //throwBall = true;
//            //}
//        }
//        else if (Input::IsKeyUp(buttonCode_))
//        {
//            //powerY -= playerAngleY;//�v���C���[�̊p�x
//        }
//        else
//        {
//            // �����x�̉��Z
//            powerY_ += GRAVITY;
//
//            // �X�s�[�h�̉��Z
//            transform_.position_.z += powerX_;
//            transform_.position_.y -= powerY_;
//            powerX_ *= 0.97;
//
//            // �o�E���h�̔���
//            if (transform_.position_.y <= 0.0f)
//            {  // �{�[������ʉ��ɓ���������
//                transform_.position_.y = 0.0;
//                powerY_ = -powerY_ * 0.6;  // y���̃X�s�[�h�𔽓]���ċʓ�����ۂ����܂蒵�˂Ȃ�����
//                height = powerY_; //�����ۑ�
//            }
//        }
//
//        //�������ړ����I���
//        if (powerX_ <= 0.001 && abs(height) <= 0.025)
//        {
//            powerX_ = 0;
//            powerY_ = 0;
//            throwBall = false;
//        }
//    }
//}
//
////
//////������
////void Ball::Initialize()
////{
////    std::string fileName[] = { "RedBall.fbx","Ball.fbx" };
////    //���f���f�[�^�̃��[�h
////    for (int i = 0; i < /*sizeof(fileName)*/2; i++)
////    {
////        hModel_[i] = Model::Load(fileName[i]);
////        assert(hModel_[i] >= 0);
////    }
////
////    transform_.position_ = XMFLOAT3(3, 0, 3);
////
////    ////for (int i = 0; i < 0; i++)
////    //{
////    //    transform_.position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //    transform_.position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //    /*if (radius > 360 || radius < 15)
////    //    {
////    //        transform_.position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //        transform_.position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //        i--;
////    //    }*/
////    //}
////
////    do
////    {
////        transform_.position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
////        transform_.position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
////        radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
////    } while (radius > 360 || radius < 15);
////
////    //�����蔻��
////    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.18f);
////    AddCollider(collision);
////
////
////    radius = 0;
////    height = 1;
////    powerX = 0;
////    powerY = 0;
////    playerAngleY = 0;
////    throwBall = false;
////    down = false;
////}
////
//////�X�V
////void Ball::Update()
////{
////    if (Input::IsKeyDown(DIK_SPACE) || throwBall == true)
////    {
////        throwBall = true;
////        //�X�y�[�X���������Ƃ�
////        if (Input::IsKey(DIK_SPACE))
////        {
////            //�q�N���X
////            powerX += 0.01;
////            //���ƂŌ����Ă�p�x�ɂ���
////            powerY -= 0.01;
////
////            //�{�[���������Ă���
////            //if ()
////            //{
////            //throwBall = true;
////            //}
////        }
////        else if (Input::IsKeyUp(DIK_SPACE))
////        {
////            //�q�N���X
////            //powerY -= playerAngleY;//�v���C���[�̊p�x
////        }
////        else
////        {
////            // �����x�̉��Z
////            powerY += gravity;
////
////            // �X�s�[�h�̉��Z
////            transform_.position_.z += powerX;
////            transform_.position_.y -= powerY;
////            powerX *= 0.97;
////
////            // �o�E���h�̔���
////            if (transform_.position_.y <= 0.0f)
////            {  // �{�[������ʉ��ɓ���������
////                transform_.position_.y = 0.0;
////                powerY = -powerY * 0.6;  // y���̃X�s�[�h�𔽓]���ċʓ�����ۂ����܂蒵�˂Ȃ�����
////                height = powerY; //�����ۑ�
////            }
////        }
////
////        //�������ړ����I���
////        if (powerX <= 0.001 && abs(height) <= 0.021)
////        {
////            powerX = 0;
////            powerY = 0;
////            throwBall = false;
////        }
////    }
////
////    //�ʂ�������
////    //�^�񒆂̏Ə�����͈͌��߂ĂȂ񂩔�΂��ăN���b�N
////    if (Input::IsMouseButtonDown(0))
////    {
////
////    }
////
////    //�f�o�b�O�p
////    if (Input::IsKeyDown(DIK_A))
////    {
////        int a = 0;
////    }
////
////    //���V�t�g�������猳�ɖ߂��A��ŏ���
////    if (Input::IsKeyDown(DIK_LSHIFT))
////    {
////        throwBall = false;
////        transform_.position_ = XMFLOAT3(3, 3, 3);
////    }
////}
////
//////�`��
////void Ball::Draw()
////{
////    //for (int i = 0; i < ballCount; i++)
////    //{
////    //    if (i < ballCount / 2)
////    //    {
////    //        radius = (trans[i].position_.x * trans[i].position_.x) + (trans[i].position_.z * trans[i].position_.z);
////    //        //transform_.position_ = XMFLOAT3(i, 3, i);
////    //        //transform_.position_.x = rand() % 20 - 10;
////    //        //�~�͈̔͂����\��
////    //        if (radius <= 360 && radius > 15)
////    //        {
////    //            Model::SetTransform(hModel_[0], trans[i]);
////    //            Model::Draw(hModel_[0]);
////    //        }
////    //        else
////    //        {
////    //            trans[i].position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //            trans[i].position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
////    //            i--;
////    //        }
////
////    //    }
////    //    else
////    //    {
////    //        radius = (trans[i].position_.x * trans[i].position_.x) + (trans[i].position_.z * trans[i].position_.z);
////    //        //transform_.position_ = XMFLOAT3(i-40, 3, i-40);
////    //        //transform_.position_.x = rand() % 20 - 10;
////    //        if (radius <= 360 && radius > 15)
////    //        {
////    //            Model::SetTransform(hModel_[1], trans[i]);
////    //            Model::Draw(hModel_[1]);
////    //        }
////    //        else
////    //        {
////    //            trans[i].position_.x = rand() % 30 - 15;
////    //            trans[i].position_.z = rand() % 30 - 15;
////    //            i--;
////    //        }
////
////    //    }
////    //}
////    Model::SetTransform(hModel_[1], transform_);
////    Model::Draw(hModel_[1]);
////}
////
//////�J��
////void Ball::Release()
////{
////}
////
//////�����蔻��
////void Ball::OnCollision(GameObject* pTarget)
////{
////    //powerX *= 0.98;
////}



#include "Ball.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Basket.h"

//�R���X�g���N�^
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball")
{
    hModel_ = -1;
}

//�f�X�g���N�^
Ball::~Ball()
{
}

//������
void Ball::Initialize()
{
    //const int WhiteConstParam::DIAMETER = 3800;
    ballID = 0;

    key = 0;
    radius = 0;

   
        height = 1;
        powerZ = 0;
        powerY = 0;
        ballDrop = 0;
        throwBall = false;
        rightHaving = false;
        leftHaving = false;
        chargePower = false;
        assist = false;
    

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("WhiteBall.fbx");
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

   

    trans.position_ = XMFLOAT3(0, 0, 0);
}

//�X�V
void Ball::Update()
{
    //��ŃL�[��ς�����悤�ɂ���for��
    
    //������Ƃ��̃{�[���̓���
    if (throwBall == true)
    {
        //�����x�̉��Z
        powerY += GRAVITY;

        // �X�s�[�h�̉��Z

        transform_.rotate_.y = playerRotateY;

        XMFLOAT3 move = { 0,-powerY,powerZ }; //�ړ���
        XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
        XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

        vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

        vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

        XMStoreFloat3(&transform_.position_, vPos);


        /*transform_.position_.z += powerZ[i];
        transform_.position_.y -= powerY[i];*/
        powerZ *= RESISTANCE;//��R

        // �o�E���h�̔���
        if (transform_.position_.y <= 0.0f)
        {  // �{�[�������ɓ���������
            transform_.position_.y = 0.0;
            powerY = -powerY * BOUND;  // y���̃X�s�[�h�𔽓]���ċʓ�����ۂ����܂蒵�˂Ȃ�����
            height = powerY; //�����ۑ�
            powerZ *= RESISTANCE;//��R

            //�����蔻��I���ɂ���@���Ƃ�
        }

        //�ړ����I���
        if (powerZ <= END_MOVE)
        {
            powerZ = 0;
            powerY = 0;
            throwBall = false;
        }
    }

    ////�p���[�n��
    //if (Input::IsPadButtonUp(XINPUT_GAMEPAD_A) && throwBall == false)
    //{
    //    throwBall = true;
    //    /* powerY = -0.5;
    //     powerZ = 0.5;*/
    //}


    for (int i = 0; i < Max; i++)
    {
        if (i == First)
        {
            key = DIK_SPACE;
            assistKey = DIK_F1;
        }
        else if (i == Second)
        {
            key = DIK_RETURN;
            assistKey = DIK_F2;
        }
        else
        {
            key = 0;
        }

        ////�X�y�[�X�L�[����������
        //if (Input::IsKeyDown(key) || throwBall[i] == true)
        //{
        //    //�X�y�[�X�������Ă�Ƃ�
        //    if (Input::IsKey(key) && (rightHaving[i] == true || leftHaving[i] == true))
        //    {
        //        if (rightHaving[i] == true)
        //        {
        //            powerZ[i] += POWER;
        //            //���ƂŌ����Ă�p�x�ɂ���
        //            powerY[i] -= POWER;
        //            throwBall[i] = true;

        //            float trajectoryY[Max], trajectoryZ[Max];
        //            trajectoryY[i] = powerY[i];
        //            trajectoryZ[i] = powerZ[i];
        //            trans.position_ = transform_.position_;

        //            for (int j = 0; j < 30; j++)
        //            {
        //                // �����x�̉��Z
        //                trajectoryY[i] += GRAVITY;


        //                trans.rotate_ = pPlayer1->GetRotate();
        //                XMFLOAT3 move = { 0,-trajectoryY[i],trajectoryZ[i] }; //�ړ���
        //                XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
        //                XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(trans.rotate_.y));   //Y���ł�����]������s��

        //                vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
        //                XMVECTOR vPos = XMLoadFloat3(&trans.position_); //���ݒn���x�N�g���ɕϊ�

        //                vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

        //                XMStoreFloat3(&trans.position_, vPos);


        //                /* trans.position_.z += trajectoryZ[i];
        //                 trans.position_.y -= trajectoryY[i];*/

        //                 //// �X�s�[�h�̉��Z
        //                 /*trans->position_.z += powerZ[i];
        //                 trans->position_.y -= powerY[i];*/
        //                pLine->AddPosition(trans.position_);
        //                trajectoryZ[i] *= RESISTANCE;//��R
        //            }
        //            chargePower[i] = true;
        //        }
            ////}//�������Ƃ�
            //else if (Input::IsKeyUp(key))
            //{
            //    //pLine->AddPosition(transform_.position_);
            //    chargePower[i] = false;
            //    //
            //    if (i == First)
            //    {
            //        //�{�[����2�����Ă���
            //        if (pPlayer1->GetHand().second == true)
            //        {
            //            pPlayer1->SetHand(false, true);
            //        }
            //        else//1�Ȃ�
            //        {
            //            pPlayer1->SetHand(false, false);
            //        }
            //    }
            //    else if (i == Second)
            //    {
            //        //�{�[����2�����Ă���
            //        if (pPlayer2->GetHand().second == true)
            //        {
            //            pPlayer2->SetHand(false, true);
            //        }
            //        else
            //        {
            //            pPlayer2->SetHand(false, false);
            //        }
            //    }

            //    //powerY + Player�̌����Ă�p�x
            //}
            //else
            //{
            //    rightHaving[i] = false;
            //    leftHaving[i] = false;
            //    // �����x�̉��Z
            //    powerY[i] += GRAVITY;

            //    // �X�s�[�h�̉��Z

            //    transform_.rotate_ = pPlayer1->GetRotate();

            //    XMFLOAT3 move = { 0,-powerY[i],powerZ[i] }; //�ړ���
            //    XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
            //    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

            //    vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            //    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

            //    vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

            //    XMStoreFloat3(&transform_.position_, vPos);


            //    /*transform_.position_.z += powerZ[i];
            //    transform_.position_.y -= powerY[i];*/
            //    powerZ[i] *= RESISTANCE;//��R

            //    // �o�E���h�̔���
            //    if (transform_.position_.y <= 0.0f)
            //    {  // �{�[�������ɓ���������
            //        transform_.position_.y = 0.0;
            //        powerY[i] = -powerY[i] * BOUND;  // y���̃X�s�[�h�𔽓]���ċʓ�����ۂ����܂蒵�˂Ȃ�����
            //        height[i] = powerY[i]; //�����ۑ�
            //        powerZ[i] *= RESISTANCE;//��R

            //        //�����蔻��I���ɂ���@���Ƃ�
            //    }

            //    //�ړ����I���
            //    if (powerZ[i] <= END_MOVE)
            //    {
            //        powerZ[i] = 0;
            //        powerY[i] = 0;
            //        throwBall[i] = false;
            //    }
            //}
        //}

       

    }

    ////�|�����C���Ɍ��݂̈ʒu��`����
    //pLine->AddPosition(transform_.position_);

    //�E��Ŏ����Ă���
    //if (rightHaving[First] == true)
    //{
    //    /*transform_.position_ = pPlayer1->GetPosition();
    //    transform_.position_.x += RIGHT_HAND_LENGTH;
    //    transform_.position_.y += HAND_HEIGHT;*/

    //    /*transform_.position_ = pPlayer1->GetPosition();
    //    transform_.rotate_ = pPlayer1->GetRotate();
    //    transform_.position_ = pPlayer1->GetPlayerPosition(RIGHT_HAND_LENGTH);
    //    transform_.rotate_;*/

    //    //transform_.position_ = Model::GetBonePosition(hModel_,"joint1");
    //    transform_.position_ = pPlayer1->GetPlayerPosition(RIGHT_HAND_LENGTH);
    //}
    //else if (rightHaving[Second] == true)
    //{
    //    /*transform_.position_ = pPlayer2->GetPosition();
    //    transform_.position_.x += RIGHT_HAND_LENGTH;
    //    transform_.position_.y += HAND_HEIGHT;*/

    //    transform_.position_ = pPlayer2->GetPlayerPosition(RIGHT_HAND_LENGTH);
    //}

    ////����Ŏ����Ă���
    //if (leftHaving[First] == true)
    //{
    //    /*transform_.position_ = pPlayer1->GetPosition();
    //    transform_.position_.x += LEFT_HAND_LENGTH;
    //    transform_.position_.y += HAND_HEIGHT;*/

    //    transform_.position_ = pPlayer1->GetPlayerPosition(LEFT_HAND_LENGTH);
    //}
    //else if (leftHaving[Second] == true)
    //{
    //    /* transform_.position_ = pPlayer2->GetPosition();
    //     transform_.position_.x += LEFT_HAND_LENGTH;
    //     transform_.position_.y += HAND_HEIGHT;*/

    //    transform_.position_ = pPlayer2->GetPlayerPosition(LEFT_HAND_LENGTH);
    //}

    ////�{�[�����E��Ɏ���������
    //if (pPlayer1->GetHand().first == false && leftHaving[First] == true)
    //{
    //    rightHaving[First] = true;
    //    leftHaving[First] = false;
    //    pPlayer1->SetHand(true, false);

    //}
    //else if (pPlayer2->GetHand().first == false && leftHaving[Second] == true)
    //{
    //    rightHaving[Second] = true;
    //    leftHaving[Second] = false;
    //    pPlayer2->SetHand(true, false);

    //}

    //if (pPlayer1->GetDamage() == true)
    //{

    //    if (leftHaving[First] == true)
    //    {
    //        KillMe();
    //        leftHaving[First] = false;
    //    }
    //    else if (rightHaving[First] == true && leftHaving[First] == false)
    //    {
    //        KillMe();
    //        rightHaving[First] = false;

    //    }

    //    pPlayer1->SetHand(false, false);

    //    ballDrop[First]++;
    //    if (ballDrop[First] < DROP_TIME)
    //    {
    //        ballDrop[First]++;
    //    }
    //    else
    //    {
    //        pPlayer1->SetDamage(false);
    //        ballDrop[First] = 0;
    //    }
    //}

    //if (pPlayer2->GetDamage() == true)
    //{

    //    if (leftHaving[Second] == true)
    //    {
    //        KillMe();
    //        leftHaving[Second] = false;
    //    }
    //    else if (rightHaving[Second] == true && leftHaving[Second] == false)
    //    {
    //        KillMe();
    //        rightHaving[Second] = false;

    //    }

    //    pPlayer2->SetHand(false, false);

    //    ballDrop[Second]++;
    //    if (ballDrop[Second] < DROP_TIME)
    //    {
    //        ballDrop[Second]++;
    //    }
    //    else
    //    {
    //        pPlayer2->SetDamage(false);
    //        ballDrop[Second] = 0;
    //    }
    //}


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
void Ball::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    

}

//�J��
void Ball::Release()
{
    
}

//�����蔻��
void Ball::OnCollision(GameObject* pTarget)
{
    //�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Basket")
    {
        //�S�[���ɓ������瓾�_�{������
        pBasket->WhiteCount();
        KillMe();

        //�S�[������Ȃ������痎����

    }
}






void Ball::HandPos(int playerID_, bool rightHand_)
{
    //transform_.position_ = bonePos;
    //a = true;
    //�����Ă邠�����̕ϐ�true
}

void Ball::PlayerBone(XMFLOAT3 bone)
{
    //�킩���
    //transform_.position_ = bone;
}

void Ball::SetPower(float powerY_, float powerZ_, float playerRotateY_)
{
    powerY = powerY_;
    powerZ = powerZ_;
    playerRotateY = playerRotateY_;
    throwBall = true;
}

void Ball::SetPlayerModel(int model_, int ballID_)
{
    //�ł��Ȃ�
    playerModel = model_;
    transform_.position_ = Model::GetBonePosition(playerModel, "joint1");

}

