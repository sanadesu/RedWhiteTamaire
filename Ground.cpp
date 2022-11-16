#include "Ground.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"

//コンストラクタ
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground"), hModel_(-1)
{

}

//デストラクタ
Ground::~Ground()
{
}

//初期化
void Ground::Initialize()
{
    hModel_ = Model::Load("Field.fbx");
    assert(hModel_ >= 0);


    transform_.position_ = XMFLOAT3(0, -0.27, 0);
}

//更新
void Ground::Update()
{
}

//描画
void Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Ground::Release()
{
}

