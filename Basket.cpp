#include "Basket.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include"Ball.h"

//コンストラクタ
Basket::Basket(GameObject* parent)
    :GameObject(parent, "Basket"),hModel_(-1), pText(nullptr)
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

    pText = new Text;
    pText->Initialize();

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
    pText->Draw(30, 30, (whiteSum));
    pText->Draw(30, 60, (redSum));
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
    //ベクター計算して上から当たったのだけ得点
    whiteSum++;
}

//赤いボールの合計
void Basket::RedCount()
{
    redSum++;
}