#include "SceneManager.h"

void CManager::Init()
{
	// 音の読み込み
	sound.titleBgm = LoadSoundMem("data/se/TITLEBGM.mp3");
	gameSound.bgm = LoadSoundMem("data/se/GAMEBGM.mp3");
	gameSound.fight = LoadSoundMem("data/se/Fight.mp3");
	gameSound.ko = LoadSoundMem("data/se/KO.mp3");
	gameSound.voice.attack = LoadSoundMem("data/se/attack.mp3");
	gameSound.voice.hit = LoadSoundMem("data/se/hit.mp3");
	gameSound.voice.uwa = LoadSoundMem("data/se/uwa.mp3");
	sound.endBgm = LoadSoundMem("data/se/ENDBGM.mp3");

	// 音量調整
	ChangeVolumeSoundMem(100, sound.titleBgm);
	ChangeVolumeSoundMem(100, gameSound.bgm);
	ChangeVolumeSoundMem(230, gameSound.fight);
	ChangeVolumeSoundMem(150, gameSound.ko);
	ChangeVolumeSoundMem(150, sound.endBgm);

	// キャラ画像の読み込み
	imageType[RYU][IDLE] = LoadGraph("data/ryu/Idle.png");
	imageType[RYU][CROUCH] = LoadGraph("data/ryu/crouching.png");
	imageType[RYU][WALK] = LoadGraph("data/ryu/Walk.png");
	imageType[RYU][JUMP] = LoadGraph("data/ryu/Jump.png");
	imageType[RYU][FRONTJUMP] = LoadGraph("data/ryu/MoveJump.png");
	imageType[RYU][BACKJUMP] = imageType[RYU][FRONTJUMP];
	imageType[RYU][BLOCK] = LoadGraph("data/ryu/Block.png");
	imageType[RYU][CROUCH_BLOCK] = LoadGraph("data/ryu/CrouchBlock.png");
	imageType[RYU][PUNCH] = LoadGraph("data/ryu/Punch.png");
	imageType[RYU][KICK] = LoadGraph("data/ryu/Kick.png");
	imageType[RYU][HADOU] = LoadGraph("data/ryu/Hadou.png");
	imageType[RYU][SYORYU] = LoadGraph("data/ryu/Syoryu.png");
	imageType[RYU][RECOIL_PUNCH] = LoadGraph("data/ryu/PunchHit.png");
	imageType[RYU][RECOIL_HADOU] = LoadGraph("data/ryu/ShotHit.png");
	imageType[RYU][RECOIL_SYORYU] = LoadGraph("data/ryu/SyoryuHit.png");
	imageType[RYU][KO] = LoadGraph("data/ryu/Ko.png");

	// ガイド画像の読み込み
	playGuideImage[KEY_W] = LoadGraph("data/guide/W.png");
	playGuideImage[KEY_A] = LoadGraph("data/guide/A.png");
	playGuideImage[KEY_S] = LoadGraph("data/guide/S.png");
	playGuideImage[KEY_D] = LoadGraph("data/guide/D.png");
	playGuideImage[KEY_T] = LoadGraph("data/guide/T.png");
	playGuideImage[KEY_Y] = LoadGraph("data/guide/Y.png");
	playGuideImage[KEY_U] = LoadGraph("data/guide/U.png");
	playGuideImage[KEY_ARROW] = LoadGraph("data/guide/ARROW.png");
	playGuideImage[KEY_NUMPAD1] = LoadGraph("data/guide/1.png");
	playGuideImage[KEY_NUMPAD2] = LoadGraph("data/guide/2.png");
	playGuideImage[KEY_NUMPAD3] = LoadGraph("data/guide/3.png");
}

void CManager::Exit() const
{
	// 音データの削除
	DeleteSoundMem(sound.titleBgm);
	DeleteSoundMem(gameSound.bgm);
	DeleteSoundMem(gameSound.fight);
	DeleteSoundMem(gameSound.ko);
	DeleteSoundMem(gameSound.voice.attack);
	DeleteSoundMem(gameSound.voice.hit);
	DeleteSoundMem(gameSound.voice.uwa);
	DeleteSoundMem(sound.endBgm);

	// キャラの数
	for (int c = 0; c < CHARA_MAX; ++c)
	{
		// 画像の数
		for (int i = 0; i < IMAGE_MAX; ++i)
		{
			DeleteGraph(imageType[c][i]);
		}
	}
	for (int i = 0; i < KEY_MAX; ++i)
	{
		DeleteGraph(playGuideImage[i]);
	}
}
