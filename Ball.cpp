//#include "Ball.h"
//#include "Engine/Model.h"
//#include "Engine/Input.h"
//
////コンストラクタ
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
//    //当たり判定
//    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.18f);
//    AddCollider(collision);
//
//    
//    //memset(hModel_, -1, sizeof(hModel_));
//}
//
////デストラクタ
//Ball::~Ball()
//{
//}
//
//void Ball::ThrowBall(int buttonCode_, float angle_, float powerX_, float powerY_)
//{
//    //// 加速度の演算
//    //powerY_ += GRAVITY;
//    //// スピードの演算
//    //transform_.position_.z += powerX_;
//    //transform_.position_.y -= powerY_;
//    //powerX_ *= 0.97;
//
//    //// バウンドの判定
//    //if (transform_.position_.y <= 0.0f)
//    //{  // ボールが画面下に当たったら
//    //    transform_.position_.y = 0.0;
//    //    powerY_ = -powerY_ * BOUND;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
//    //    height = powerY_; //高さ保存
//    //}
//
//    if (Input::IsKeyDown(buttonCode_) || throwBall == true)
//    {
//        throwBall = true;
//        //スペースを押したとき
//        if (Input::IsKey(buttonCode_))
//        {
//            powerX_ += 0.01;
//            //あとで向いてる角度にする
//            powerY_ -= 0.01;
//
//            //ボールを持ってたら
//            //if ()
//            //{
//            //throwBall = true;
//            //}
//        }
//        else if (Input::IsKeyUp(buttonCode_))
//        {
//            //powerY -= playerAngleY;//プレイヤーの角度
//        }
//        else
//        {
//            // 加速度の演算
//            powerY_ += GRAVITY;
//
//            // スピードの演算
//            transform_.position_.z += powerX_;
//            transform_.position_.y -= powerY_;
//            powerX_ *= 0.97;
//
//            // バウンドの判定
//            if (transform_.position_.y <= 0.0f)
//            {  // ボールが画面下に当たったら
//                transform_.position_.y = 0.0;
//                powerY_ = -powerY_ * 0.6;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
//                height = powerY_; //高さ保存
//            }
//        }
//
//        //高さ＆移動が終わる
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
//////初期化
////void Ball::Initialize()
////{
////    std::string fileName[] = { "RedBall.fbx","Ball.fbx" };
////    //モデルデータのロード
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
////    //当たり判定
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
//////更新
////void Ball::Update()
////{
////    if (Input::IsKeyDown(DIK_SPACE) || throwBall == true)
////    {
////        throwBall = true;
////        //スペースを押したとき
////        if (Input::IsKey(DIK_SPACE))
////        {
////            //子クラス
////            powerX += 0.01;
////            //あとで向いてる角度にする
////            powerY -= 0.01;
////
////            //ボールを持ってたら
////            //if ()
////            //{
////            //throwBall = true;
////            //}
////        }
////        else if (Input::IsKeyUp(DIK_SPACE))
////        {
////            //子クラス
////            //powerY -= playerAngleY;//プレイヤーの角度
////        }
////        else
////        {
////            // 加速度の演算
////            powerY += gravity;
////
////            // スピードの演算
////            transform_.position_.z += powerX;
////            transform_.position_.y -= powerY;
////            powerX *= 0.97;
////
////            // バウンドの判定
////            if (transform_.position_.y <= 0.0f)
////            {  // ボールが画面下に当たったら
////                transform_.position_.y = 0.0;
////                powerY = -powerY * 0.6;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
////                height = powerY; //高さ保存
////            }
////        }
////
////        //高さ＆移動が終わる
////        if (powerX <= 0.001 && abs(height) <= 0.021)
////        {
////            powerX = 0;
////            powerY = 0;
////            throwBall = false;
////        }
////    }
////
////    //玉を持つ処理
////    //真ん中の照準から範囲決めてなんか飛ばしてクリック
////    if (Input::IsMouseButtonDown(0))
////    {
////
////    }
////
////    //デバッグ用
////    if (Input::IsKeyDown(DIK_A))
////    {
////        int a = 0;
////    }
////
////    //左シフト押したら元に戻す、後で消す
////    if (Input::IsKeyDown(DIK_LSHIFT))
////    {
////        throwBall = false;
////        transform_.position_ = XMFLOAT3(3, 3, 3);
////    }
////}
////
//////描画
////void Ball::Draw()
////{
////    //for (int i = 0; i < ballCount; i++)
////    //{
////    //    if (i < ballCount / 2)
////    //    {
////    //        radius = (trans[i].position_.x * trans[i].position_.x) + (trans[i].position_.z * trans[i].position_.z);
////    //        //transform_.position_ = XMFLOAT3(i, 3, i);
////    //        //transform_.position_.x = rand() % 20 - 10;
////    //        //円の範囲だけ表示
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
//////開放
////void Ball::Release()
////{
////}
////
//////当たり判定
////void Ball::OnCollision(GameObject* pTarget)
////{
////    //powerX *= 0.98;
////}



#include "Ball.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Basket.h"

//コンストラクタ
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball")
{
    hModel_ = -1;
}

//デストラクタ
Ball::~Ball()
{
}

//初期化
void Ball::Initialize()
{
    //const int WhiteConstParam::DIAMETER = 3800;
    ballID = 0;

    key = 0;
    radius = 0;

   
        height = 1;
        powerZ = 0;
        powerY = 0;
        ballDrop = 0;
        throwBall = false;
        rightHaving = false;
        leftHaving = false;
        chargePower = false;
        assist = false;
    

    //モデルデータのロード
    hModel_ = Model::Load("WhiteBall.fbx");
    assert(hModel_ >= 0);

    do
    {
        transform_.position_.x = (float)(rand() % DIAMETER - (DIAMETER / HALF)) / CHANGE_DECIMAL;
        transform_.position_.z = (float)(rand() % DIAMETER - (DIAMETER / HALF)) / CHANGE_DECIMAL;

        radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    } while (radius >= CIRCLE_RANGE || radius < NEAR_GOAL);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), BALLSIZE);
    AddCollider(collision);

   

    trans.position_ = XMFLOAT3(0, 0, 0);
}

//更新
void Ball::Update()
{
    //後でキーを変えられるようにしてfor文
    
    //投げるときのボールの動き
    if (throwBall == true)
    {
        //加速度の演算
        powerY += GRAVITY;

        // スピードの演算

        transform_.rotate_.y = playerRotateY;

        XMFLOAT3 move = { 0,-powerY,powerZ }; //移動量
        XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
        XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

        vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

        vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

        XMStoreFloat3(&transform_.position_, vPos);


        /*transform_.position_.z += powerZ[i];
        transform_.position_.y -= powerY[i];*/
        powerZ *= RESISTANCE;//抵抗

        // バウンドの判定
        if (transform_.position_.y <= 0.0f)
        {  // ボールが下に当たったら
            transform_.position_.y = 0.0;
            powerY = -powerY * BOUND;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
            height = powerY; //高さ保存
            powerZ *= RESISTANCE;//抵抗

            //当たり判定終わりにする　あとで
        }

        //移動が終わる
        if (powerZ <= END_MOVE)
        {
            powerZ = 0;
            powerY = 0;
            throwBall = false;
        }
    }

    ////パワー渡す
    //if (Input::IsPadButtonUp(XINPUT_GAMEPAD_A) && throwBall == false)
    //{
    //    throwBall = true;
    //    /* powerY = -0.5;
    //     powerZ = 0.5;*/
    //}


    for (int i = 0; i < Max; i++)
    {
        if (i == First)
        {
            key = DIK_SPACE;
            assistKey = DIK_F1;
        }
        else if (i == Second)
        {
            key = DIK_RETURN;
            assistKey = DIK_F2;
        }
        else
        {
            key = 0;
        }

        ////スペースキーを押したら
        //if (Input::IsKeyDown(key) || throwBall[i] == true)
        //{
        //    //スペースを押してるとき
        //    if (Input::IsKey(key) && (rightHaving[i] == true || leftHaving[i] == true))
        //    {
        //        if (rightHaving[i] == true)
        //        {
        //            powerZ[i] += POWER;
        //            //あとで向いてる角度にする
        //            powerY[i] -= POWER;
        //            throwBall[i] = true;

        //            float trajectoryY[Max], trajectoryZ[Max];
        //            trajectoryY[i] = powerY[i];
        //            trajectoryZ[i] = powerZ[i];
        //            trans.position_ = transform_.position_;

        //            for (int j = 0; j < 30; j++)
        //            {
        //                // 加速度の演算
        //                trajectoryY[i] += GRAVITY;


        //                trans.rotate_ = pPlayer1->GetRotate();
        //                XMFLOAT3 move = { 0,-trajectoryY[i],trajectoryZ[i] }; //移動量
        //                XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
        //                XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(trans.rotate_.y));   //Y軸でｙ°回転させる行列

        //                vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
        //                XMVECTOR vPos = XMLoadFloat3(&trans.position_); //現在地をベクトルに変換

        //                vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

        //                XMStoreFloat3(&trans.position_, vPos);


        //                /* trans.position_.z += trajectoryZ[i];
        //                 trans.position_.y -= trajectoryY[i];*/

        //                 //// スピードの演算
        //                 /*trans->position_.z += powerZ[i];
        //                 trans->position_.y -= powerY[i];*/
        //                pLine->AddPosition(trans.position_);
        //                trajectoryZ[i] *= RESISTANCE;//抵抗
        //            }
        //            chargePower[i] = true;
        //        }
            ////}//離したとき
            //else if (Input::IsKeyUp(key))
            //{
            //    //pLine->AddPosition(transform_.position_);
            //    chargePower[i] = false;
            //    //
            //    if (i == First)
            //    {
            //        //ボールを2個もってたら
            //        if (pPlayer1->GetHand().second == true)
            //        {
            //            pPlayer1->SetHand(false, true);
            //        }
            //        else//1個なら
            //        {
            //            pPlayer1->SetHand(false, false);
            //        }
            //    }
            //    else if (i == Second)
            //    {
            //        //ボールを2個もってたら
            //        if (pPlayer2->GetHand().second == true)
            //        {
            //            pPlayer2->SetHand(false, true);
            //        }
            //        else
            //        {
            //            pPlayer2->SetHand(false, false);
            //        }
            //    }

            //    //powerY + Playerの向いてる角度
            //}
            //else
            //{
            //    rightHaving[i] = false;
            //    leftHaving[i] = false;
            //    // 加速度の演算
            //    powerY[i] += GRAVITY;

            //    // スピードの演算

            //    transform_.rotate_ = pPlayer1->GetRotate();

            //    XMFLOAT3 move = { 0,-powerY[i],powerZ[i] }; //移動量
            //    XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
            //    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

            //    vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            //    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

            //    vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

            //    XMStoreFloat3(&transform_.position_, vPos);


            //    /*transform_.position_.z += powerZ[i];
            //    transform_.position_.y -= powerY[i];*/
            //    powerZ[i] *= RESISTANCE;//抵抗

            //    // バウンドの判定
            //    if (transform_.position_.y <= 0.0f)
            //    {  // ボールが下に当たったら
            //        transform_.position_.y = 0.0;
            //        powerY[i] = -powerY[i] * BOUND;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
            //        height[i] = powerY[i]; //高さ保存
            //        powerZ[i] *= RESISTANCE;//抵抗

            //        //当たり判定終わりにする　あとで
            //    }

            //    //移動が終わる
            //    if (powerZ[i] <= END_MOVE)
            //    {
            //        powerZ[i] = 0;
            //        powerY[i] = 0;
            //        throwBall[i] = false;
            //    }
            //}
        //}

       

    }

    ////ポリラインに現在の位置を伝える
    //pLine->AddPosition(transform_.position_);

    //右手で持ってたら
    //if (rightHaving[First] == true)
    //{
    //    /*transform_.position_ = pPlayer1->GetPosition();
    //    transform_.position_.x += RIGHT_HAND_LENGTH;
    //    transform_.position_.y += HAND_HEIGHT;*/

    //    /*transform_.position_ = pPlayer1->GetPosition();
    //    transform_.rotate_ = pPlayer1->GetRotate();
    //    transform_.position_ = pPlayer1->GetPlayerPosition(RIGHT_HAND_LENGTH);
    //    transform_.rotate_;*/

    //    //transform_.position_ = Model::GetBonePosition(hModel_,"joint1");
    //    transform_.position_ = pPlayer1->GetPlayerPosition(RIGHT_HAND_LENGTH);
    //}
    //else if (rightHaving[Second] == true)
    //{
    //    /*transform_.position_ = pPlayer2->GetPosition();
    //    transform_.position_.x += RIGHT_HAND_LENGTH;
    //    transform_.position_.y += HAND_HEIGHT;*/

    //    transform_.position_ = pPlayer2->GetPlayerPosition(RIGHT_HAND_LENGTH);
    //}

    ////左手で持ってたら
    //if (leftHaving[First] == true)
    //{
    //    /*transform_.position_ = pPlayer1->GetPosition();
    //    transform_.position_.x += LEFT_HAND_LENGTH;
    //    transform_.position_.y += HAND_HEIGHT;*/

    //    transform_.position_ = pPlayer1->GetPlayerPosition(LEFT_HAND_LENGTH);
    //}
    //else if (leftHaving[Second] == true)
    //{
    //    /* transform_.position_ = pPlayer2->GetPosition();
    //     transform_.position_.x += LEFT_HAND_LENGTH;
    //     transform_.position_.y += HAND_HEIGHT;*/

    //    transform_.position_ = pPlayer2->GetPlayerPosition(LEFT_HAND_LENGTH);
    //}

    ////ボールを右手に持ちかえる
    //if (pPlayer1->GetHand().first == false && leftHaving[First] == true)
    //{
    //    rightHaving[First] = true;
    //    leftHaving[First] = false;
    //    pPlayer1->SetHand(true, false);

    //}
    //else if (pPlayer2->GetHand().first == false && leftHaving[Second] == true)
    //{
    //    rightHaving[Second] = true;
    //    leftHaving[Second] = false;
    //    pPlayer2->SetHand(true, false);

    //}

    //if (pPlayer1->GetDamage() == true)
    //{

    //    if (leftHaving[First] == true)
    //    {
    //        KillMe();
    //        leftHaving[First] = false;
    //    }
    //    else if (rightHaving[First] == true && leftHaving[First] == false)
    //    {
    //        KillMe();
    //        rightHaving[First] = false;

    //    }

    //    pPlayer1->SetHand(false, false);

    //    ballDrop[First]++;
    //    if (ballDrop[First] < DROP_TIME)
    //    {
    //        ballDrop[First]++;
    //    }
    //    else
    //    {
    //        pPlayer1->SetDamage(false);
    //        ballDrop[First] = 0;
    //    }
    //}

    //if (pPlayer2->GetDamage() == true)
    //{

    //    if (leftHaving[Second] == true)
    //    {
    //        KillMe();
    //        leftHaving[Second] = false;
    //    }
    //    else if (rightHaving[Second] == true && leftHaving[Second] == false)
    //    {
    //        KillMe();
    //        rightHaving[Second] = false;

    //    }

    //    pPlayer2->SetHand(false, false);

    //    ballDrop[Second]++;
    //    if (ballDrop[Second] < DROP_TIME)
    //    {
    //        ballDrop[Second]++;
    //    }
    //    else
    //    {
    //        pPlayer2->SetDamage(false);
    //        ballDrop[Second] = 0;
    //    }
    //}


    //玉を持つ処理
    //真ん中の照準から範囲決めてなんか飛ばしてクリック
    if (Input::IsMouseButtonDown(0))
    {

    }

    //デバッグ用
    if (Input::IsKey(DIK_B))
    {
        int a = 0;
    }


    ////円の範囲外なら消える
    radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    if (radius > CIRCLE_OUTSIDE)
    {
        KillMe();
    }

}

//描画
void Ball::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    

}

//開放
void Ball::Release()
{
    
}

//当たり判定
void Ball::OnCollision(GameObject* pTarget)
{
    //弾に当たったとき
    if (pTarget->GetObjectName() == "Basket")
    {
        //ゴールに入ったら得点＋消える
        pBasket->WhiteCount();
        KillMe();

        //ゴールじゃなかったら落ちる

    }
}






void Ball::HandPos(int playerID_, bool rightHand_)
{
    //transform_.position_ = bonePos;
    //a = true;
    //もってるあいだの変数true
}

void Ball::PlayerBone(XMFLOAT3 bone)
{
    //わからん
    //transform_.position_ = bone;
}

void Ball::SetPower(float powerY_, float powerZ_, float playerRotateY_)
{
    powerY = powerY_;
    powerZ = powerZ_;
    playerRotateY = playerRotateY_;
    throwBall = true;
}

void Ball::SetPlayerModel(int model_, int ballID_)
{
    //できない
    playerModel = model_;
    transform_.position_ = Model::GetBonePosition(playerModel, "joint1");

}

