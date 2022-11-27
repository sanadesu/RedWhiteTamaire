#include "RedBall.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Basket.h"

//コンストラクタ
RedBall::RedBall(GameObject* parent)
    :GameObject(parent, "RedBall")
{
    hModel_ = -1;
}

//デストラクタ
RedBall::~RedBall()
{
}

//初期化
void RedBall::Initialize()
{
    //const int RedConstParam::DIAMETER = 3800;

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
    }

    //モデルデータのロード
    hModel_ = Model::Load("RedBall.fbx");
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
}

//更新
void RedBall::Update()
{
    //後でキーを変えられるようにしてfor文


    for (int i = 0; i < Max; i++)
    {
        if (i == First)
        {
            key = DIK_SPACE;
        }
        else if (i == Second)
        {
            key = DIK_RETURN;
        }
        else
        {
            key = 0;
        }


        //スペースキーを押したら
        if ((Input::IsKeyDown(key) || throwBall[i] == true))
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
                }
            }
            else if (Input::IsKeyUp(key))
            {
                if (i == First)
                {
                    //ボールを2個もってたら
                    if (pPlayer1->GetHand().second == true)
                    {
                        pPlayer1->SetHand(false, true);
                    }
                    else
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
    }

    //右手で持ってたら
    if (rightHaving[First] == true)
    {
        transform_.position_ = pPlayer1->GetPosition();
        transform_.position_.x += RIGHT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;
    }
    else if (rightHaving[Second] == true)
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
    }
    else if (leftHaving[Second] == true)
    {
        transform_.position_ = pPlayer2->GetPosition();
        transform_.position_.x += LEFT_HAND_LENGTH;
        transform_.position_.y += HAND_HEIGHT;
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
}

//描画
void RedBall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void RedBall::Release()
{
}

//当たり判定
void RedBall::OnCollision(GameObject* pTarget)
{
    //弾に当たったとき
    if (pTarget->GetObjectName() == "Basket")
    {
        //ゴールに入ったら得点＋消える
        pBasket->RedCount();
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

