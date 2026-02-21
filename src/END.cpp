#include "END.h"
#include "InGame.h"

void CEnd::Init()
{
	SetFontSize(60);
	// 画像を読み込む
	for (int i = 0; i < (int)PlayerNum::MAX; ++i)
	{
		switch (playerChara[i])
		{
		case RYU:
			charaImage[i] = LoadGraph("data/ryu/Icon.png");
			break;
		default:
			break;
		}
	}
}

void CEnd::Update()
{
	// 音流す
	if (CheckSoundMem(sound->endBgm) == false)
	{
		PlaySoundMem(sound->endBgm, DX_PLAYTYPE_BACK);
	}

	// 文字列を動かす
	++strMoveCount;
	if (strMoveCount == STR_MOVE_TIME)
	{
		strMoveCount = 0;
	}

	// 次のシーンを切り替え
	if (manager->checkInputKey.PushHitKey(KEY_INPUT_A) || manager->checkInputKey.PushHitKey(KEY_INPUT_LEFT))
	{
		nextScene = GAME_SCENE;
	}
	if (manager->checkInputKey.PushHitKey(KEY_INPUT_D) || manager->checkInputKey.PushHitKey(KEY_INPUT_RIGHT))
	{
		nextScene = TITLE_SCENE;
	}

	// そのシーンに移動
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		// 音止める
		if (CheckSoundMem(sound->endBgm))
		{
			StopSoundMem(sound->endBgm);
		}
		if (nextScene == GAME_SCENE)
		{
			manager->scene = std::make_shared<CInGame>(manager, RYU, RYU, &manager->gameSound);
		}
		else if (nextScene == TITLE_SCENE)
		{
			manager->scene = std::make_shared<CTitle>(manager, &manager->sound);
		}
	}
}

void CEnd::Render()
{
	int strWidth = 0;	// 文字列のサイズ

	// 背景黒く
	DrawFillBox(0, 0, WINDOW_W, WINDOW_H, GetColor(0, 0, 0));
	
	// アイコン
	DrawRotaGraph(WINDOW_W / 4 * 1, WINDOW_H / 2, 3, 0, charaImage[(int)PlayerNum::PLAYER_1], true);
	SetDrawBright(255, 0, 0);
	DrawRotaGraph(WINDOW_W / 4 * 3, WINDOW_H / 2, 3, 0, charaImage[(int)PlayerNum::PLAYER_2], true, true);
	SetDrawBright(255, 255, 255);

	// 何対何か
	strWidth = GetDrawFormatStringWidth("%d  -  %d", manager->winNum1P, manager->winNum2P);
	DrawFormatString(WINDOW_W / 2 - strWidth / 2, WINDOW_H / 2 + 100, GetColor(255, 255, 255), "%d  -  %d", manager->winNum1P, manager->winNum2P);

	// 文字列(再試合, タイトル)
	strWidth = GetDrawStringWidth(str[0], (int)strlen(str[0]));
	DrawString(WINDOW_W / 4 * 1 - strWidth / 2, 20, str[0], GetColor(255, 255, 255));

	// 再試合にカーソルを合わせる
	if (nextScene == GAME_SCENE)
		DrawLineBox(WINDOW_W / 4 * 1 - strWidth / 2, 20, WINDOW_W / 4 * 1 - strWidth / 2 + strWidth, 100, GetColor(255, 255, 0));
	strWidth = GetDrawStringWidth(str[1], (int)strlen(str[1]));
	DrawString(WINDOW_W / 4 * 3 - strWidth / 2, 20, str[1], GetColor(255, 255, 255));

	// タイトルにカーソルを合わせる
	if (nextScene == TITLE_SCENE)
		DrawLineBox(WINDOW_W / 4 * 3 - strWidth / 2, 20, WINDOW_W / 4 * 3 - strWidth / 2 + strWidth, 100, GetColor(255, 255, 0));

	// 文字列を点滅させる
	SetFontSize(35);
	if (strMoveCount < STR_MOVE_TIME / 2)
	{
		strWidth = GetDrawStringWidth(str[2], (int)strlen(str[2]));
		DrawString(WINDOW_W / 2 - strWidth / 2, WINDOW_H - 100, str[2], GetColor(255, 255, 255));
	}
	SetFontSize(60);

	// 勝ったプレイヤーの下にWIN
	if (whichWin == (int)PlayerNum::PLAYER_1)
	{
		strWidth = GetDrawStringWidth("WIN", (int)strlen("WIN"));
		DrawString(WINDOW_W / 4 * 1 - strWidth / 2, WINDOW_H / 2 + 150, "WIN", GetColor(255, 255, 0));
	}
	else if (whichWin == (int)PlayerNum::PLAYER_2)
	{
		strWidth = GetDrawStringWidth("WIN", (int)strlen("WIN"));
		DrawString(WINDOW_W / 4 * 3 - strWidth / 2, WINDOW_H / 2 + 150, "WIN", GetColor(255, 255, 0));
	}
	// どろー
	else
	{
		strWidth = GetDrawStringWidth("DRAW", (int)strlen("DRAW"));
		DrawString(WINDOW_W / 2 - strWidth / 2, WINDOW_H / 2, "DRAW", GetColor(255, 255, 0));
	}
}
