#include "Player1.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"

//コンストラクタ
Player1::Player1(GameObject* parent)
    :GameObject(parent, "Player1"),
    hModel_(-1)
{

}

//デストラクタ
Player1::~Player1()
{

}

//初期化
void Player1::Initialize()
{
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    //trans.position_ = XMFLOAT3(0, 0, -3);
    transform_.position_ = XMFLOAT3(START_POS_X, 0, START_POS_Z);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1, 0), HIT_SIZE);
    AddCollider(collision);

    y_ = 10.0f; //Y座標
    moveLimit = 0.0f;
    rightHand = false;
    leftHand = false;
    damage = false;
}

//更新
void Player1::Update()
{
    moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    if (moveLimit > CIRCLE_RANGE)
    {
        if (transform_.position_.x < 0)
        {
            a[0] = true;
            //transform_.position_.x += RETURN_MOVE;
        }
        else if(transform_.position_.x > 0)
        {
            a[1] = true;
            //transform_.position_.x -= RETURN_MOVE;
        }

        if (transform_.position_.z < 0)
        {
            a[2] = true;
            //transform_.position_.z += RETURN_MOVE;
        }
        else if(transform_.position_.z > 0)
        {
            a[3] = true;
            //transform_.position_.z -= RETURN_MOVE;
        }
        
    }
    else
    {
        a[0] = false;
        a[1] = false;
        a[2] = false;
        a[3] = false;
    }
    //else
    {
        //W押したら前進
        if (Input::IsKey(DIK_W)&& a[3] == false)
        {
            //transform_.position_.z += 0.5;
            XMFLOAT3 move = { 0,0,PLAYER_MOVE }; //移動量
            XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

            vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

            XMStoreFloat3(&transform_.position_, vPos);
        }
        //S押したら後退
        if (Input::IsKey(DIK_S) && a[2] == false)
        {
            XMFLOAT3 move = { 0,0,-PLAYER_MOVE }; 
            XMVECTOR vMove = XMLoadFloat3(&move); 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸で90°回転させる行列

            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); 

            vPos += vMove; 

            XMStoreFloat3(&transform_.position_, vPos); 
        }
        //D押したら右
        if (Input::IsKey(DIK_D) && a[1] == false)
        {
            XMFLOAT3 move = { PLAYER_MOVE,0,0 }; //移動量
            XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

            vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

            XMStoreFloat3(&transform_.position_, vPos);
        }
        //A押したら
        if (Input::IsKey(DIK_A) && a[0] == false)
        {
            XMFLOAT3 move = { -PLAYER_MOVE,0,0 }; //
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
    XMVECTOR vCam = XMVectorSet(0.0f, y_, -CAMERA_Z, 0.0f);
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);//カメラの座標

    Direct3D::SetViewPort(0);
    Camera::SetPosition(camPos);
    Camera::SetTarget(transform_.position_);



    //デバッグ用
    if (Input::IsKeyDown(DIK_B))
    {
        int a = 0;
    }
}

//描画
void Player1::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player1::Release()
{
  
}

//何かに当たった
void Player1::OnCollision(GameObject* pTarget)
{
    //当たったときの処理
}

//角度取得
float Player1::GetAngle()
{
    return 0;
}

//ボールを持つ
void Player1::SetHand(bool rightHand_,bool leftHand_)
{
    rightHand = rightHand_;
    leftHand = leftHand_;
}

//ボールを持っているか
std::pair<bool, bool> Player1::GetHand()
{
    return std::make_pair(rightHand, leftHand);
}

void Player1::SetDamage(bool damage_)
{
    damage = damage_;
}

bool Player1::GetDamage()
{
    return damage;
}

XMFLOAT3 Player1::GetPlayerPosition(float x_)
{
    Transform trans = transform_;

    /*trans.position_.x += x_;
    trans.position_.y += 2.5f;*/
    if (x_ > 0)
    {
        trans.position_ = Model::GetBonePosition(hModel_, "joint1");
    }
    else
    {
        trans.position_ = Model::GetBonePosition(hModel_, "joint2");
    }
   

    return trans.position_;
}

XMFLOAT3 Player1::GetPlayerRotate()
{
    Transform trans = transform_;
    trans.rotate_.y += 120;
    return trans.rotate_;
}