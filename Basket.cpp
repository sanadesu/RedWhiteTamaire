#include "Basket.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
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

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 5, 0), 0.8f);
    AddCollider(collision);

    whiteSum = 0;
    redSum = 0;
}

//更新
void Basket::Update()
{
    //デバッグ用
    if (Input::IsKeyDown(DIK_B))
    {
        int a = 0;
    }
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

//何かに当たった
void Basket::OnCollision(GameObject* pTarget)
{
    //当たったときの処理
}

//白いボールの合計
void Basket::WhiteCount()
{
    whiteSum++;
}

//赤いボールの合計
void Basket::RedCount()
{
    redSum++;
}