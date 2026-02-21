#pragma once

#include "SceneManager.h"
#include "Chara.h"
#include "Ryu.h"

const int TRAINING_STR_MAX = 6;	// トレーニングにある文字列のサイズ
class CTraining :public CScene
{
	CChara* playerChara[(int)PlayerNum::MAX]{ nullptr }; // 操作キャラ
	CharaType charaType[(int)PlayerNum::MAX]{ RYU,RYU };	// キャラタイプ
	const char* str[TRAINING_STR_MAX]{ "1P", "2P", "移動", "ジャンプ", "しゃがみ", "攻撃" };
	int bgImage = 0;	// 背景画像
	GameSound* gameSound = 0;	// 音
	int guideImage[KEY_MAX];	// トレーニングの説明画像
	const int imageSize = 40;	// 画像のサイズ
	void Init();
public:

	// コンストラクタ
	CTraining(std::shared_ptr<CManager>  pManager, CharaType p1, CharaType p2, GameSound* argSound, int* argImage) :CScene(pManager)
	{
		charaType[(int)PlayerNum::PLAYER_1] = p1;
		charaType[(int)PlayerNum::PLAYER_2] = p2;
		gameSound = argSound;
		for (int i = 0; i < KEY_MAX; ++i)
		{
			guideImage[i] = argImage[i];
		}
		this->Init();
	};
	~CTraining()
	{
		delete* playerChara;
	};

	void Update();
	void Render();

	// 矩形同士の当たり判定
	bool GetHitDetection(HitBox box1, HitBox box2);
	void PlayerCollision(CChara& argChara1, CChara& argChara2);
};

const int PLAY_GUIDE_BOX_X = 50;	// ガイド文字列が書いてあるBOXのX座標
const int PLAY_GUIDE_BOX_Y = 100;	// Y座標
const int PLAY_GUIDE_BOX_W = 250;	// 幅
const int PLAY_GUIDE_BOX_H = 200;	// 高さ

const int GUIDE_STR_OFFSET = 130;	// ↑のBOXのX座標からの距離

const int RETURN_STR_OFFSET = 50;	// ENTERで戻るっていう文字列の画面下からの距離