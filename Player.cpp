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

    nowState = WALK_STATE;
    playerID = 0;
    key = 0;
    processID = 0;
    rightHand = -1;
    leftHand = -1;
    powerY = 0.0f;
    powerZ = 0.0f;
    trajectoryY = 0.0f;
    trajectoryZ = 0.0f;
    y_ = 10.0f; //Y座標
    moveLimit = 0.0f;
    goalLength = 0.0f;
   /* rightHand = false;
    leftHand = false;*/
    damage = false;
    chargePower = false;
    prevPos = transform_;

    pLine = new PoryLine;
    pLine->Load("tex.png");

    trans = transform_;
}

//更新
void Player::Update()
{
    if (playerID == 0)
    {
        switch (nowState)
        {
        case WALK_STATE:
            if (moveLimit > CIRCLE_RANGE)
            transform_.rotate_.y += 137;


            XMFLOAT3 move = { 0,0,PLAYER_MOVE }; //移動量
            XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

            vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

            XMStoreFloat3(&transform_.position_, vPos);

            if (pBallRight != nullptr)
            {
                nowState = CHARGE_STATE;
            }
            break;
        case CHARGE_STATE:
            XMFLOAT3 origine = XMFLOAT3(0,0,0);
            XMVECTOR vOrigin = XMLoadFloat3(&origine);
            XMFLOAT3 HandPos = Model::GetBonePosition(hModel_, "joint1");
            XMVECTOR vPlayerPos = XMLoadFloat3(&HandPos);
            XMVECTOR vGoal = vOrigin - vPlayerPos; //ゴールへの向き

            XMVECTOR vGoalLength = XMVector3Length(vGoal);
            goalLength = XMVectorGetX(vGoalLength);

            XMFLOAT3 vGoalRotate; 	

            XMStoreFloat3(&vGoalRotate, vGoal);

            transform_.rotate_.y = atan2(vGoalRotate.x, vGoalRotate.z) * 180.0 / 3.14;

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
            if (powerZ > powf(goalLength,0.5) * ((rand() % 30 / 1000) + 0.20))
            {
                nowState = THROW_STATE;
            }
            break;
        case THROW_STATE://ボール投げる
            if (rightHand == pBallRight->GetBallNum())
            {
                pBallRight->SetPower(powerY, powerZ, transform_.rotate_.y);
                chargePower = false;
                powerY = 0;
                powerZ = 0;
                rightHand = leftHand;
                leftHand = -1;
                pBallRight = pBallLeft;
                pBallLeft = nullptr;
                nowState = WALK_STATE;
            }
            break;
        default:
            break;
        }
    }
   


    if (pBallRight != nullptr)
    {
        pBallRight->PlayerBone(Model::GetBonePosition(hModel_, "joint1"));
    }
    if (pBallLeft != nullptr)
    {
        pBallLeft->PlayerBone(Model::GetBonePosition(hModel_, "joint2"));
    }

    moveLimit = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);

    if (moveLimit > CIRCLE_RANGE)
    {
        //後で変える
        if (transform_.position_.x < 0)
        {
            transform_.position_.x = prevPos.position_.x;
        }
        else if (transform_.position_.x > 0)
        {
            transform_.position_.x = prevPos.position_.x;
        }

        if (transform_.position_.z < 0)
        {
            transform_.position_.z = prevPos.position_.z;
        }
        else if (transform_.position_.z > 0)
        {
            transform_.position_.z = prevPos.position_.z;
        }
    }

    prevPos = transform_;


    for (int i = 0; i < MAX; i++)
    {
        //XMFLOAT3
        //なげる
        if (Input::IsPadButton(XINPUT_GAMEPAD_A, i) && playerID == i && rightHand >= 0)
        {
            //transform_.position_ = XMFLOAT3(0, 0, 0);

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
        else if (Input::IsPadButtonUp(XINPUT_GAMEPAD_A, i) && playerID == i && rightHand >= 0)
        {
            if (rightHand == pBallRight->GetBallNum())
            {
                pBallRight->SetPower(powerY, powerZ, transform_.rotate_.y);
                chargePower = false;
                powerY = 0;
                powerZ = 0;
                rightHand = leftHand;
                leftHand = -1;
                pBallRight = pBallLeft;
                pBallLeft = nullptr;
            }
            
        }

        //拾う
        if (Input::IsPadButton(XINPUT_GAMEPAD_B, i))
        {

        }//移動
        if(playerID == i)
        {
            XMFLOAT3 LeftStick = Input::GetPadStickL(i);
            LeftStick.x /= 10;
            LeftStick.y /= 10;
            /*transform_.position_.x += LeftStick.x;
            transform_.position_.z += LeftStick.y;*/

            XMFLOAT3 move = { LeftStick.x,0,LeftStick.y }; //移動量
            XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

            vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

            XMStoreFloat3(&transform_.position_, vPos);

            XMFLOAT3 RightSrick = Input::GetPadStickR(i);
            //RightSrick.x /= 2;
            RightSrick.y /= 4;
            transform_.rotate_.y += RightSrick.x;
            y_ += RightSrick.y;
            //hdri
            //ポリヘブン
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


    //カメラ
    XMVECTOR vCam = XMVectorSet(0.0f, y_, -CAMERA_Z, 0.0f);
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
    for (int i = 0; i < MAX; i++)
    {
        //ボールにあたる＆どのプレイヤーか＆ボール持ってないか
        if (pTarget->GetObjectName() == "Ball" && playerID == i)
        {
           

            //落ちてるボールか投げてるボールか転がってるボールか
            //↑ボールの状態取得して判別
            //ここには投げてるボールだけになる（あとで）
            pBallThrow = (Ball*)pTarget;
            if (pBallThrow->GetIsThrow() == true)
            {
                rightHand = -1;
                leftHand = -1;
                if (pBallRight != nullptr)
                {
                    pBallRight->KillMe();
                    pBallRight = nullptr;
                }
                if (pBallLeft != nullptr)
                {
                    pBallLeft->KillMe();
                    pBallLeft = nullptr;
                }
               

            } //みぎてあいてる
            else if (rightHand < 0)
            {
                //落ちてるボール
                //processID = i;
                //pWhiteBall->
                pBallRight = (Ball*)pTarget;
                //pBall->SetPosition(Model::GetBonePosition(hModel_, "joint1"));
                //pBallRight->PlayerBone(Model::GetBonePosition(hModel_, "joint1"));
                //当たったボールの番号知りたい
                rightHand = pBallRight->GetBallNum();
                
                //pBall->SetPlayerModel(hModel_);
                //XMFLOAT3 a = Model::GetBonePosition(hModel_, "joint1");
                //a = XMFLOAT3(1, 1, 1);
                //pBall->HandPos(i,true);
                //pBall->PlayerBone(a);
            }//左手
            else if(leftHand < 0)
            {
                pBallLeft = (Ball*)pTarget;
                leftHand = pBallLeft->GetBallNum();
            }
           

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

