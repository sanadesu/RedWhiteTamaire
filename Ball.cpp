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
////    std::string fileName[] = { "RedBall.fbx","WhiteBall.fbx" };
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