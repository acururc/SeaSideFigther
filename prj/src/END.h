#pragma once

#include "SceneManager.h"
#include "Title.h"
#include "Chara.h"

const int END_STR_MAX = 3;
const int STR_MOVE_TIME = 40;	// 文字列の動かす時間

enum Next
{
	GAME_SCENE,
	TITLE_SCENE,
};


class CEnd :public CScene
{
	CharaType playerChara[(int)PlayerNum::MAX]{ RYU };	// 何のキャラか
	int charaImage[(int)PlayerNum::MAX]{ 0 };				// キャラのアイコン画像
	int whichWin = 0;										// どっちが勝ったのか
	Next nextScene = GAME_SCENE;							// 次のシーン
	int strMoveCount = 0;									// 文字列を動かす用の時間
	Sound* sound;										// 音
	const char* str[END_STR_MAX] = {"再試合", "タイトル", "PRESS ENTER"};
	void Init();
public:

	CEnd(std::shared_ptr<CManager>  pManager, CharaType argPlayer1, CharaType argPlayer2, int argWhichWin, Sound* argSound) :CScene(pManager)
	{
		// 使っていたキャラを受けとる
		playerChara[(int)PlayerNum::PLAYER_1] = argPlayer1;
		playerChara[(int)PlayerNum::PLAYER_2] = argPlayer2;

		// どっちが勝ったのか
		whichWin = argWhichWin;

		sound = argSound;
		this->Init();
	};

	~CEnd()
	{
	}

	void Update();
	void Render();
};