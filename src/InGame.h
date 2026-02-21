#pragma once

#include "SceneManager.h"
#include "Chara.h"
#include "Ryu.h"
#include "END.h"

const int GAME_BG_MAX = 8;

enum
{
	GAME_START,
	GAME_PLAY,
};

class CInGame :public CScene
{
	CChara* playerChara[(int)PlayerNum::MAX]{ nullptr }; // 操作キャラ
	CharaType charaType[(int)PlayerNum::MAX]{ RYU,RYU };	// キャラタイプ

	const int INGAME_STR_OFFSET = 150;	// ゲーム中文字列の画面外からの距離

	int koTime = 0;	// KOしてから移動するまでの時間
	// 背景関連
	int bgImage[GAME_BG_MAX]{ 0 };
	int bgCount = 0;
	int bgIndex = 0;
	char bgImageStr[50];

	int gameState = GAME_START;	// ゲームの状態
	int time = 60 * 4 - 1;	// 時間 初期値　2.59から始める
	GameSound* gameSound = 0;	// 音
	void Init();
public:

	// コンストラクター
	CInGame(std::shared_ptr<CManager>  pManager, CharaType p1, CharaType p2, GameSound* argSound) :CScene(pManager)
	{
		charaType[(int)PlayerNum::PLAYER_1] = p1;
		charaType[(int)PlayerNum::PLAYER_2] = p2;
		gameSound = argSound;
		this->Init();
	};
	~CInGame()
	{
		for (int i = 0; i < GAME_BG_MAX; ++i)
		{
			DeleteGraph(bgImage[i]);
		}
		delete* playerChara;
	};


	void Start();	// ゲームが始まる前のカウントダウンなど
	void Update();
	void Render();
	// 矩形同士の当たり判定
	bool GetHitDetection(HitBox box1, HitBox box2);
	void PlayerCollision(CChara& argChara1, CChara& argChara2);
};