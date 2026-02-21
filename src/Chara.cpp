#include "Chara.h"

void CChara::HpReg(int *argVoice)
{
	if (charaStatus.hp <= 0 && charaStatus.nowMotion != KO)
	{
		PlaySoundMem(*argVoice, DX_PLAYTYPE_BACK);
		charaStatus.hp = 0;
		charaStatus.nowImage = charaStatus.imageType[KO];
		charaStatus.nowMotion = KO;
		charaStatus.imageCount = 0;
		charaStatus.gX = 0;
		charaStatus.imageChengeNum = 0;
		hitBox[(int)judge::DEFEAT].x = -100;
		hitBox[(int)judge::DEFEAT].y = -100;
		hitBox[(int)judge::DEFEAT].w = -100;
		hitBox[(int)judge::DEFEAT].h = -100;
		hitBox[(int)judge::ATTACK].x = -100;
		hitBox[(int)judge::ATTACK].y = -100;
		hitBox[(int)judge::ATTACK].w = -100;
		hitBox[(int)judge::ATTACK].h = -100;
	}
}