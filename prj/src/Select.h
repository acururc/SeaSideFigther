#pragma once
#include "SceneManager.h"

const int SELECT_BG_MAX = 2;		// 背景画像の数
const int SELECT_STR_MAX = 2;		// 文字列の数
const int SELECT_GUIDEBG_MAX = 4;	// ガイド用背景画像の数
const int SELECT_GUIDESTR_MAX = 2;	// ガイド用文字列の数
const float STR_LIMIT = 5;			// 文字列の制限
const float STR_MOVE_ACCS = 0.5f;	// 文字列の加速度

enum SELECT_TYPE
{
	SELECT_TRAINING,
	SELECT_FIGHT,
	SELECT_MAX,
};

enum StrMove
{
	STR_UP,
	STR_DOWN,
};

//タイトル全体の管理
class CSelect : public CScene
{
	// 背景
	int bgImage[SELECT_BG_MAX]{ 0 };
	
	// 描画する文字列
	const char* str[SELECT_STR_MAX]{ "トレーニング", "対戦" };
	// 文字列の大きさ
	int strWidth[SELECT_STR_MAX]{ 0 };
	// 文字列のY座標
	float strY[SELECT_STR_MAX]{ 0 };
	float diffY = 1;
	// 文字列どっちに動いてるか
	StrMove strWitchMove = STR_DOWN;

	// ガイド用の文字列
	const char* guideStr[SELECT_STR_MAX]{ "選択", "決定" };
	int guideBgImage[SELECT_GUIDEBG_MAX]{ 0 };

	// 音
	Sound* sound;
	// 今どっちを選んでるか
	SELECT_TYPE nowSelect = SELECT_TRAINING;

	void Init();

public:
	CSelect(std::shared_ptr<CManager> pManager, Sound* argSound) :CScene(pManager)
	{
		sound = argSound;
		this->Init();
	};
	~CSelect()
	{
		for (int i = 0; i < SELECT_STR_MAX; ++i)
		{
			DeleteGraph(bgImage[i]);
		}
		for (int i = 0; i < SELECT_GUIDEBG_MAX; ++i)
		{
			DeleteGraph(guideBgImage[i]);
		}
	};
	void Update();
	void Render();
};