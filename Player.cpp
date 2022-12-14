#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),
    hModel_(-1), pLine(nullptr)
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
    transform_.position_ = XMFLOAT3(START_POS_X, 0, START_POS_Z);
    transform_.position_.x = rand() % 20;
    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1, 0), HIT_SIZE);
    AddCollider(collision);

    playerID = 0;
    key = 0;
    processID = 0;
    powerY = 0.0f;
    powerZ = 0.0f;
    trajectoryY = 0.0f;
    trajectoryZ = 0.0f;
    y_ = 10.0f; //Y座標
    moveLimit = 0.0f;
    rightHand = false;
    leftHand = false;
    damage = false;
    chargePower = false;

    pLine = new PoryLine;
    pLine->Load("tex.png");

    trans = transform_;
}

//更新
void Player::Update()
{
    moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    if (moveLimit > CIRCLE_RANGE)
    {
        //後で変える
        if (transform_.position_.x < 0)
        {
            transform_.position_.x += RETURN_MOVE;
        }
        else if (transform_.position_.x > 0)
        {
            transform_.position_.x -= RETURN_MOVE;
        }

        if (transform_.position_.z < 0)
        {
            transform_.position_.z += RETURN_MOVE;
        }
        else if (transform_.position_.z > 0)
        {
            transform_.position_.z -= RETURN_MOVE;
        }
    }


    for (int i = 0; i < Max; i++)
    {
        //XMFLOAT3
        //なげる
        if (Input::IsPadButton(XINPUT_GAMEPAD_A, i) && playerID == i)
        {
            //transform_.position_ = XMFLOAT3(0, 0, 0);


            //if (rightHand == true)
            {
                //力ためるやつ
                powerY -= POWER;
                powerZ += POWER;
                trajectoryY = powerY;
                trajectoryZ = powerZ;
                //右手の位置
                trans.position_ = Model::GetBonePosition(hModel_, "joint1");
                //trans.position_ = transform_.position_;

                for (int j = 0; j < 30; j++)
                {
                    // 加速度の演算
                    trajectoryY += GRAVITY;


                    trans.rotate_ = transform_.rotate_;
                    XMFLOAT3 move = { 0,-trajectoryY,trajectoryZ }; //移動量
                    XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
                    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(trans.rotate_.y));   //Y軸でｙ°回転させる行列

                    vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
                    XMVECTOR vPos = XMLoadFloat3(&trans.position_); //現在地をベクトルに変換

                    vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

                    XMStoreFloat3(&trans.position_, vPos);

                    pLine->AddPosition(trans.position_);
                    trajectoryZ *= RESISTANCE;//抵抗
                }
                chargePower = true;
            }
        }
        else if (Input::IsPadButtonUp(XINPUT_GAMEPAD_A, i) && playerID == i)
        {
            pBall->SetPower(powerY, powerZ,transform_.rotate_.y);
            chargePower = false;
            powerY = 0;
            powerZ = 0;
        }

        //拾う
        if (Input::IsPadButton(XINPUT_GAMEPAD_B, i))
        {

        }//移動
        if(playerID == i)
        {
            XMFLOAT3 a = Input::GetPadStickL(i);
            a.x /= 10;
            a.y /= 10;
            transform_.position_.x += a.x;
            transform_.position_.z += a.y;
        }
    }

    ////W押したら前進
    //if (Input::IsKey(DIK_W))
    //{
    //    //transform_.position_.z += 0.5;
    //    XMFLOAT3 move = { 0,0,PLAYER_MOVE }; //移動量
    //    XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
    //    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

    //    vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
    //    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

    //    vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

    //    XMStoreFloat3(&transform_.position_, vPos);
    //}
    ////S押したら後退
    //if (Input::IsKey(DIK_S))
    //{
    //    XMFLOAT3 move = { 0,0,-PLAYER_MOVE };
    //    XMVECTOR vMove = XMLoadFloat3(&move);
    //    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸で90°回転させる行列

    //    vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
    //    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //    vPos += vMove;

    //    XMStoreFloat3(&transform_.position_, vPos);
    //}
    ////D押したら右
    //if (Input::IsKey(DIK_D))
    //{
    //    XMFLOAT3 move = { PLAYER_MOVE,0,0 }; //移動量
    //    XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
    //    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

    //    vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
    //    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

    //    vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

    //    XMStoreFloat3(&transform_.position_, vPos);
    //}
    ////A押したら
    //if (Input::IsKey(DIK_A))
    //{
    //    XMFLOAT3 move = { -PLAYER_MOVE,0,0 }; //
    //    XMVECTOR vMove = XMLoadFloat3(&move); //
    //    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸で90°回転させる行列
    //    vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
    //    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //

    //    vPos += vMove;

    //    XMStoreFloat3(&transform_.position_, vPos);
    //}


        //pLine->AddPosition(transform_.position_);


    

    ////カメラ移動
    ////右押したら右回転
    //if (Input::IsKey(key))
    //{
    //    transform_.rotate_.y++;
    //}
    ////左押したら左回転
    //if (Input::IsKey(key))
    //{
    //    transform_.rotate_.y--;
    //}
    ////右押したら右回転
    //if (Input::IsKey(key))
    //{
    //    y_++;
    //}
    ////左押したら左回転
    //if (Input::IsKey(key))
    //{
    //    y_--;
    //}


    ////カメラ
    //XMVECTOR vCam = XMVectorSet(0.0f, y_, -CAMERA_Z, 0.0f);
    //XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //vCam = XMVector3TransformCoord(vCam, mRotate);
    //XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //XMFLOAT3 camPos;
    //XMStoreFloat3(&camPos, vPos + vCam);//カメラの座標

    //Camera::SetPosition(camPos);
    //Camera::SetTarget(transform_.position_);

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

    if (chargePower == true)
    {
        //ポリラインを描画
        pLine->Draw();
    }
}

//開放
void Player::Release()
{
    //ポリライン解放
    pLine->Release();
}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
    for (int i = 0; i < Max; i++)
    {
        if (pTarget->GetObjectName() == "Ball" && playerID == i)
        {
            //落ちてるボールか投げてるボールか転がってるボールか
            //↑ボールの状態取得して判別
            //ここには投げてるボールだけになる（あとで）

            //落ちてるボール
            //processID = i;
            //pWhiteBall->
            pTarget->SetPosition(Model::GetBonePosition(hModel_, "joint1"));
            //pBall->SetPlayerModel(hModel_);
            XMFLOAT3 a = Model::GetBonePosition(hModel_, "joint1");
            //a = XMFLOAT3(1, 1, 1);
            //pBall->HandPos(i,true);
            //pBall->PlayerBone(a);

            //投げてるボール
            //持ってるボールを消す
            //一定時間拾えない
            //点滅
        }
    }
}

//角度取得
float Player::GetAngle()
{
    return 0;
}

//ボールを持つ
void Player::SetHand(bool rightHand_, bool leftHand_)
{
    rightHand = rightHand_;
    leftHand = leftHand_;
}

//ボールを持っているか
std::pair<bool, bool> Player::GetHand()
{
    return std::make_pair(rightHand, leftHand);
}

void Player::SetDamage(bool damage_)
{
    damage = damage_;
}

bool Player::GetDamage()
{
    return damage;
}

Transform Player::GetPlayerPosition(bool right)
{
    Transform trans_ = transform_;

    //trans.rotate_.y += 120;
    //trans.position_.x += x_;
    //trans.position_.y += HAND_HEIGHT;

    if (right == true)
    {
        trans_.position_ = Model::GetBonePosition(hModel_, "joint1");
    }
    else
    {
        trans_.position_ = Model::GetBonePosition(hModel_, "joint2");
    }

    return trans_;
}

