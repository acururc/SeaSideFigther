#include "DxLib.h"
#include "SceneManager.h"
#include "Title.h"
#include "Select.h"

void CTitle::Init()
{
	SetFontSize(60);
	ChangeFontType(DX_FONTTYPE_EDGE);
	for (int i = 0; i < TITLE_BG_MAX; ++i)
	{
		sprintf_s(bgImageStr, "data/background/Title%d.png", i);
		bgImage[i] = LoadGraph(bgImageStr);
	}
	for (int i = 0; i < TITLE_STR_MAX; ++i)
	{
		strWidth[i] = GetDrawStringWidth(str[i], (int)strlen(str[i]));
	}
}

void CTitle::Update()
{
	// ‰¹‚ð–Â‚ç‚·
	// “ñd‚É‚È‚ç‚È‚¢‚æ‚¤‚É‚È‚Á‚Ä‚¢‚é‚©Šm”F
	if (CheckSoundMem(sound->titleBgm) == FALSE)
	{
		PlaySoundMem(sound->titleBgm, DX_PLAYTYPE_BACK, TRUE);
	}
	// ”wŒi‚ð“®‚©‚·
	++bgCount;
	if (bgCount % 10 == 0)
	{
		bgIndex++;
		if (bgIndex == TITLE_BG_MAX)
		{
			bgIndex = 0;
		}
	}

	// ƒ^ƒCƒgƒ‹‚©‚ç‚ÌˆÚ“®
	if (manager->checkInputKey.PushHitKey(KEY_INPUT_RETURN))
	{
		manager->scene = std::make_shared<CSelect>(manager, &manager->sound);
	}
}

void CTitle::Render()
{
	// ”wŒi•`‰æ
	DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 2, 0, bgImage[bgIndex], true);

	DrawString(WINDOW_W / 2 - strWidth[0] / 2, 150, str[0], GetColor(0, 0, 255));
	DrawString(WINDOW_W / 2 - strWidth[1] / 2, 300, str[1], GetColor(255, 255,0));
}
