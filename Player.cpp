#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),
    hModel_(-1)
{

}

//デストラクタ
Player::~Player()
{

}

//初期化
void Player::Initialize()
{
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    //trans.position_ = XMFLOAT3(0, 0, -3);
    transform_.position_ = XMFLOAT3(0, -0.5, -3);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1, 0), 1.2f);
    AddCollider(collision);

    y_ = 10.0f; //Y座標
    moveLimit = 0.0f;
    rightHand = false;
    leftHand = false;
}

//更新
void Player::Update()
{
    moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    if (moveLimit > 360)
    {
        if (transform_.position_.x < 0)
        {
            transform_.position_.x += 0.01f;
        }
        else if(transform_.position_.x > 0)
        {
            transform_.position_.x -= 0.01f;
        }

        if (transform_.position_.z < 0)
        {
            transform_.position_.z += 0.1f;
        }
        else if(transform_.position_.z > 0)
        {
            transform_.position_.z -= 0.1f;
        }
    }
    else
    {
        //W押したら前進
        if (Input::IsKey(DIK_W))
        {
            //transform_.position_.z += 0.5;
            XMFLOAT3 move = { 0,0,MOVE }; //移動量
            XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

            vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

            XMStoreFloat3(&transform_.position_, vPos);
        }
        //S押したら後退
        if (Input::IsKey(DIK_S))
        {
            XMFLOAT3 move = { 0,0,-MOVE }; 
            XMVECTOR vMove = XMLoadFloat3(&move); 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸で90°回転させる行列

            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); 

            vPos += vMove; 

            XMStoreFloat3(&transform_.position_, vPos); 
        }
        //D押したら右
        if (Input::IsKey(DIK_D))
        {
            XMFLOAT3 move = { MOVE,0,0 }; //移動量
            XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

            vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

            XMStoreFloat3(&transform_.position_, vPos);
        }
        //S押したら後退
        if (Input::IsKey(DIK_A))
        {
            XMFLOAT3 move = { -MOVE,0,0 }; //
            XMVECTOR vMove = XMLoadFloat3(&move); //
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸で90°回転させる行列
            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //

            vPos += vMove; 

            XMStoreFloat3(&transform_.position_, vPos); 
        }
    }
    //カメラ移動
    //右押したら右回転
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y++;
    }
    //左押したら左回転
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y--;
    }
    //右押したら右回転
    if (Input::IsKey(DIK_UP))
    {
        y_++;
    }
    //左押したら左回転
    if (Input::IsKey(DIK_DOWN))
    {
        y_--;
    }
    

    //カメラ
    XMVECTOR vCam = XMVectorSet(0.0f, y_, -Z_, 0.0f);
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);//カメラの座標

    Camera::SetPosition(camPos);
    Camera::SetTarget(transform_.position_);

    //デバッグ用
    if (Input::IsKeyDown(DIK_B))
    {
        int a = 0;
    }
}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
  
}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
    //当たったときの処理
}

//角度取得
float Player::GetAngle()
{
    return 0;
}

//ボールを持つ
void Player::SetHand(bool rightHand_,bool leftHand_)
{
    rightHand = rightHand_;
    leftHand = leftHand_;
}

//ボールを持っているか
std::pair<bool, bool> Player::GetHand()
{
    return std::make_pair(rightHand, leftHand);
}

