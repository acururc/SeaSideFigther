#pragma once
#include "SceneManager.h"

const int TITLE_BG_MAX = 8;
const int TITLE_STR_MAX = 2;
//タイトル全体の管理
class CTitle : public CScene
{
	void Init();
	// 背景
	int bgImage[TITLE_BG_MAX]{ 0 };
	char bgImageStr[30]{ 0 };
	int bgCount = 0;
	int bgIndex = 0;

	// 描画する文字列
	const char* str[TITLE_STR_MAX]{ "シーサイドファイター", "PRESS ENTER" };
	Sound* sound;
	int strWidth[TITLE_STR_MAX]{ 0 };

public:
	CTitle(std::shared_ptr<CManager> pManager, Sound* argSound) :CScene(pManager)
	{
		sound = argSound;
		this->Init();
	};
	~CTitle()
	{
		for (int i = 0; i < TITLE_BG_MAX; ++i)
		{
			DeleteGraph(bgImage[i]);
		}
	};
	void Update();
	void Render();
};