#include "Basket.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"

//コンストラクタ
Basket::Basket(GameObject* parent)
    :GameObject(parent, "Basket"),hModel_(-1)
{

}

//デストラクタ
Basket::~Basket()
{
}

//初期化
void Basket::Initialize()
{
    hModel_ = Model::Load("Goal.fbx");
    assert(hModel_ >= 0);

    
    transform_.position_ = XMFLOAT3(0, 0, 0);
}

//更新
void Basket::Update()
{
}

//描画
void Basket::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Basket::Release()
{
}

