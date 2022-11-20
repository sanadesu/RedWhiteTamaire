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
    //モデルデータのロード
    hModel_ = Model::Load("WhiteBall.fbx");
    assert(hModel_ >= 0);

    transform_.position_ = XMFLOAT3(0, 0, 0);

    do
    {
        transform_.position_.x = (float)(((float)(rand() % 4000) - 2000) / 100);
        transform_.position_.z = (float)(((float)(rand() % 4000) - 2000) / 100);
        radius = (transform_.position_.x * transform_.position_.x) + (transform_.position_.z * transform_.position_.z);
    } while (radius > 360 || radius < 15);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.18f);
    AddCollider(collision);

    radius = 0;
    whiteCount = 0;
    height = 1;
    powerX = 0;
    powerY = 0;
    playerAngleY = 0;
    throwBall = false;
    down = false;
    rightHaving = false;
    leftHaving = false;
}

//更新
void WhiteBall::Update()
{
    //スペースキーを押したら
    if ((Input::IsKeyDown(DIK_SPACE) || throwBall == true))
    {
        
        //スペースを押してるとき
        if (Input::IsKey(DIK_SPACE) && (rightHaving == true || leftHaving == true))
        {
            if (rightHaving == true)
            {
                powerX += 0.01;
                //あとで向いてる角度にする
                powerY -= 0.01;
                throwBall = true;
            }
        }
        else if (Input::IsKeyUp(DIK_SPACE))
        {
            //powerY -= playerAngleY;//プレイヤーの角度
            if (pPlayer->GetHand().second == true)
            {
                pPlayer->SetHand(false, true);
                //leftHaving = false;
                //rightHaving = true;
            }
            else
            {
                pPlayer->SetHand(false, false);
               
            }
            
        }
        else
        {
            rightHaving = false;
            leftHaving = false;
            // 加速度の演算
            powerY += GRAVITY;

            // スピードの演算
            transform_.position_.z += powerX;
            transform_.position_.y -= powerY;
            powerX *= 0.97;

            // バウンドの判定
            if (transform_.position_.y <= 0.0f)
            {  // ボールが画面下に当たったら
                transform_.position_.y = 0.0;
                powerY = -powerY * BOUND;  // y軸のスピードを反転して玉入れっぽくあまり跳ねなくする
                height = powerY; //高さ保存
                powerX *= 0.98;
            }
        }

        //高さ＆移動が終わる
        if (powerX <= 0.001 && abs(height) <= 0.021)
        {
            powerX = 0;
            powerY = 0;
            throwBall = false;
        }
        
    }

    if (rightHaving == true)
    {
        transform_.position_ = pPlayer->GetPosition();
        transform_.position_.x += 1;
        transform_.position_.y += 2.5;
    }

    if (leftHaving == true)
    {
        transform_.position_ = pPlayer->GetPosition();
        transform_.position_.x += -1;
        transform_.position_.y += 2.5;
    }

    if (pPlayer->GetHand().first == false && leftHaving == true)
    {
        rightHaving = true;
        leftHaving = false;
        pPlayer->SetHand(true, false);

    }

    /*if (pPlayer->GetHand().first == false && rightHaving == true)
    {
        rightHaving = false;
        leftHaving = false;
        pPlayer->SetHand(false, false);
    }*/

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

    //左シフト押したら元に戻す、後で消す
    if (Input::IsKeyDown(DIK_LSHIFT))
    {
        throwBall = false;
        transform_.position_ = XMFLOAT3(3, 3, 3);
    }
}

//描画
void WhiteBall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void WhiteBall::Release()
{
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
    else if (pTarget->GetObjectName() == "Player" && pPlayer->GetHand().second == false)
    {
        //ボールを持っていないとき
        if (pPlayer->GetHand().first == false)
        {
            //右手でボール持つ
            pPlayer->SetHand(true,false);
            rightHaving = true;
        }
        else
        {
            //左手でボール持つ
            pPlayer->SetHand(true, true);
            leftHaving = true;
        }
    }
}