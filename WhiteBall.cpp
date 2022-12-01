#include "WhiteBall.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Basket.h"

//コンストラクタ
WhiteBall::WhiteBall(GameObject* parent)
    :GameObject(parent, "WhiteBall")
{
    hModel_ = -1;
}

//デストラクタ
WhiteBall::~WhiteBall()
{
}

//初期化
void WhiteBall::Initialize()
{
    //const int WhiteConstParam::DIAMETER = 3800;

    key = 0;
    radius = 0;
    
    for (int i = 0; i < Max; i++)
    {
        height[i] = 1;
        powerZ[i] = 0;
        powerY[i] = 0;
        ballDrop[i] = 0;
        throwBall[i] = false;
        rightHaving[i] = false;
        leftHaving[i] = false;
        chargePower[i] = false;
        assist[i] = false;
    }

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

    //ポリライン初期化
    pLine = new PoryLine;
    pLine->Load("tex.png");

    trans.position_ = XMFLOAT3(0, 0, 0);
}

//更新
void WhiteBall::Update()
{
    //後でキーを変えられるようにしてfor文


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

        //スペースキーを押したら
        if (Input::IsKeyDown(key) || throwBall[i] == true)
        {
            //スペースを押してるとき
            if (Input::IsKey(key) && (rightHaving[i] == true || leftHaving[i] == true))
            {
                if (rightHaving[i] == true)
                {
                    powerZ[i] += POWER;
                    //あとで向いてる角度にする
                    powerY[i] -= POWER;
                    throwBall[i] = true;

                    float trajectoryY[Max], trajectoryZ[Max];
                    trajectoryY[i] = powerY[i];
                    trajectoryZ[i] = powerZ[i];
                    trans.position_ = transform_.position_;

                    for (int j = 0; j < 30; j++)
                    {
                        // 加速度の演算
                        trajectoryY[i] += GRAVITY;

                        trans.position_.z += trajectoryZ[i];
                        trans.position_.y -= trajectoryY[i];

                        //// スピードの演算
                        /*trans->position_.z += powerZ[i];
                        trans->position_.y -= powerY[i];*/
                        pLine->AddPosition(trans.position_);
                        trajectoryZ[i] *= RESISTANCE;//抵抗
                    }
                    chargePower[i] = true;
                }
            }//離したとき
            else if (Input::IsKeyUp(key))
            {
                //pLine->AddPosition(transform_.position_);
                chargePower[i] = false;
                //
                if (i == First)
                {
                    //ボールを2個もってたら
                    if (pPlayer1->GetHand().second == true)
                    {
                        pPlayer1->SetHand(false, true);
                    }
                    else//1個なら
                    {
                        pPlayer1->SetHand(false, false);
                    }
                }
                else if (i == Second)
                {
                    //ボールを2個もってたら
                    if (pPlayer2->GetHand().second == true)
                    {
                        pPlayer2->SetHand(false, true);
                    }
                    else
                    {
                        pPlayer2->SetHand(false, false);
                    }
                }

                //powerY + Playerの向いてる角度
            }
            else
            {
                

                rightHaving[i] = false;
                leftHaving[i] = false;
                // 加速度の演算
                powerY[i] += GRAVITY;

                // スピードの演算
                transform_.position_.z += powerZ[i];
                transform_.position_.y -= powerY[i];
                powerZ[i] *= RESISTANCE;//抵抗

                // バウンドの判定
                if (transform_.position_.y <= 0.0f)
                {  // ボールが下に当たったら
                    transform_.position_.y = 0.0;
                    powerY[i] = -powerY[i] * BOUND;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
                    height[i] = powerY[i]; //高さ保存
                    powerZ[i] *= RESISTANCE;//抵抗

                    //当たり判定終わりにする　あとで
                }

                //移動が終わる
                if (powerZ[i] <= END_MOVE)
                {
                    powerZ[i] = 0;
                    powerY[i] = 0;
                    throwBall[i] = false;
                }
            }
        }
        
        if (Input::IsKeyDown(assistKey))
        {
            assist[i] = true;
        }

    }

    ////ポリラインに現在の位置を伝える
    //pLine->AddPosition(transform_.position_);
    
    //右手で持ってたら
    if (rightHaving[First] == true)
    {
        /*transform_.position_ = pPlayer1->GetPosition();
        transform_.position_.x += RIGHT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;*/

        /*transform_.position_ = pPlayer1->GetPosition();
        transform_.rotate_ = pPlayer1->GetRotate();
        transform_.position_ = pPlayer1->GetPlayerPosition(RIGHT_HAND_LENGTH);
        transform_.rotate_;*/

        //transform_.position_ = Model::GetBonePosition(hModel_,"joint1");
        transform_.position_ = pPlayer1->GetPlayerPosition(RIGHT_HAND_LENGTH);
    }
    else if(rightHaving[Second] == true)
    {
        transform_.position_ = pPlayer2->GetPosition();
        transform_.position_.x += RIGHT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;
    }

    //左手で持ってたら
    if (leftHaving[First] == true)
    {
        transform_.position_ = pPlayer1->GetPosition();
        transform_.position_.x += LEFT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;

        //transform_.position_ = pPlayer1->GetPlayerPosition(LEFT_HAND_LENGTH);
    }
    else if (leftHaving[Second] == true)
    {
        transform_.position_ = pPlayer2->GetPosition();
        transform_.position_.x += LEFT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;

        //transform_.position_ = pPlayer1->GetPlayerPosition(LEFT_HAND_LENGTH);
    }

    //ボールを右手に持ちかえる
    if (pPlayer1->GetHand().first == false && leftHaving[First] == true)
    {
        rightHaving[First] = true;
        leftHaving[First] = false;
        pPlayer1->SetHand(true, false);

    }
    else if (pPlayer2->GetHand().first == false && leftHaving[Second] == true)
    {
        rightHaving[Second] = true;
        leftHaving[Second] = false;
        pPlayer2->SetHand(true, false);

    }

    if (pPlayer1->GetDamage() == true)
    {
        
        if (leftHaving[First] == true)
        {
            KillMe();
            leftHaving[First] = false;
        }
        else if (rightHaving[First] == true && leftHaving[First] == false)
        {
            KillMe();
            rightHaving[First] = false;

        }

        pPlayer1->SetHand(false, false);

        ballDrop[First]++;
        if (ballDrop[First] < DROP_TIME)
        {
            ballDrop[First]++;
        }
        else
        {
            pPlayer1->SetDamage(false);
            ballDrop[First] = 0;
        }
    }
    
    if (pPlayer2->GetDamage() == true)
    {

        if (leftHaving[Second] == true)
        {
            KillMe();
            leftHaving[Second] = false;
        }
        else if (rightHaving[Second] == true && leftHaving[Second] == false)
        {
            KillMe();
            rightHaving[Second] = false;

        }

        pPlayer2->SetHand(false, false);

        ballDrop[Second]++;
        if (ballDrop[Second] < DROP_TIME)
        {
            ballDrop[Second]++;
        }
        else
        {
            pPlayer2->SetDamage(false);
            ballDrop[Second] = 0;
        }
    }


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





    //右押したら右回転
    if (Input::IsKey(DIK_X))
    {
        transform_.rotate_.y++;
    }
    //左押したら左回転
    if (Input::IsKey(DIK_Z))
    {
        transform_.rotate_.y--;
    }
    //右押したら右回転
    if (Input::IsKey(DIK_C))
    {
        transform_.position_.z++;
    }
    //左押したら左回転
    if (Input::IsKey(DIK_V))
    {
        transform_.position_.z--;
    }
}

//描画
void WhiteBall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    for (int i = 0; i < Max; i++)
    {
        if (chargePower[i] == true && assist[i] == true)
        {
            //ポリラインを描画
            pLine->Draw();
        }
    }
    
}

//開放
void WhiteBall::Release()
{
    //ポリライン解放
    pLine->Release();
}

//当たり判定
void WhiteBall::OnCollision(GameObject* pTarget)
{
    //弾に当たったとき
    if (pTarget->GetObjectName() == "Basket")
    {
        //ゴールに入ったら得点＋消える
        pBasket->WhiteCount();
        KillMe();
        
        //ゴールじゃなかったら落ちる

    }
    else if (pTarget->GetObjectName() == "Player1" && throwBall[First] == false && pPlayer1->GetDamage() == false)
    {
        //ボールを当てられたら
        if (throwBall[Second] == true)
        {
            pPlayer1->SetDamage(true);
        }
        //左でボールを持っていないとき
        else if (pPlayer1->GetHand().second == false)
        {
            if (pPlayer1->GetHand().first == false)
            {
                //右手でボール持つ
                pPlayer1->SetHand(true, false);
                rightHaving[First] = true;
            }
            else
            {
                //左手でボール持つ
                pPlayer1->SetHand(true, true);
                leftHaving[First] = true;
            }
        }
        
    }
    else if (pTarget->GetObjectName() == "Player2" && throwBall[Second] == false && pPlayer2->GetDamage() == false)
    {
        //ボールを当てられたら
        if (throwBall[First] == true)
        {
            pPlayer2->SetDamage(true);
        }
        //左でボールを持っていないとき
        else if (pPlayer2->GetHand().second == false)
        {
            //ボールを持っていないとき
            if (pPlayer2->GetHand().first == false)
            {
                //右手でボール持つ
                pPlayer2->SetHand(true, false);
                rightHaving[Second] = true;
            }
            else
            {
                //左手でボール持つ
                pPlayer2->SetHand(true, true);
                leftHaving[Second] = true;
            }
        }
    }
}

