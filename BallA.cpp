//#include "Ball.h"
//#include "Engine/Model.h"
//
////�R���X�g���N�^
//Ball::Ball(GameObject* parent)
//	: GameObject(parent, "Ball")
//{
//}
//
////�f�X�g���N�^
//Ball::~Ball()
//{
//}
//
////������
//void Ball::Initialize()
//{
//    std::string fileName[] = { "BoxDefault","WhiteBall"};
//    //���f���f�[�^�̃��[�h
//    for (int i = 0; i < /*sizeof(fileName)*/2; i++)
//    {
//        std::string fn = "Assets/" + fileName[i] + ".fbx";
//        hModel_[i] = Model::Load(fn);
//        assert(hModel_[i] >= 0);
//    }
//
//    transform_.scale_ = XMFLOAT3(5.0f, 5.0f, 5.0f);
//}
//
////�X�V
//void Ball::Update()
//{
//	//GameObject* Title = FindObject("SceneManager");
//    //transform_.position_.y += 0.1f;
//}
//
////�`��
//void Ball::Draw()
//{
//    Transform trans;
//   
//
//    Model::SetTransform(hModel_[RED], trans);
//    Model::Draw(hModel_[RED]);
//
//    trans.position_.x = 3;
//    //trans.position_.y = 3;
//    trans.position_.z = 3;
//    Model::SetTransform(hModel_[WHITE], trans);
//    Model::Draw(hModel_[WHITE]);
//}
//
////�J��
//void Ball::Release()
//{
//}