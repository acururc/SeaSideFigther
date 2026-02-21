#pragma once

// Y座標
#define IDLE_POS WINDOW_H - 170
#define KICK_POS WINDOW_H - 135
#define CROUCH_POS WINDOW_H - 140
#define SYORYU_POS WINDOW_H - 250


// モーションの種類
enum Motion
{
	IDLE,		// アイドル
	CROUCH,		// しゃがむ
	WALK,		// 歩く
	JUMP,		// ジャンプ
	FRONTJUMP,	// 前ジャンプ
	BACKJUMP,	// 後ろジャンプ
	BLOCK,		// ガード
	CROUCH_BLOCK, // しゃがみガード
	PUNCH,		// パンチ
	KICK,		// キック
	HADOU,		// 波動
	SYORYU,		// 昇竜
	RECOIL,		// 攻撃食らうモーション
	RECOIL_PUNCH,
	RECOIL_HADOU,
	RECOIL_SYORYU,
	KO,		// 負けたモーション
	IMAGE_MAX,	// 数
};

// キャラの種類
enum CharaType
{
	RYU,	// リュウ
	CHARA_MAX
};

// プレイヤーの識別
enum class PlayerNum
{
	PLAYER_1,
	PLAYER_2,
	MAX,
};

// 空中ぐらいか地上ぐらいか
enum
{
	RECOIL_GROUND = 8,
	RECOIL_AIR = 10,
};

// キャラボイスの種類
enum
{
	ATTACK_SE,
	HIT_SE,
	KO_SE,
};

// 操作説明の画像
enum PlayGuideImage
{
	// 1P側
	KEY_A,	// 移動
	KEY_D,	// 移動
	KEY_S,	// しゃがみ
	KEY_W,	// ジャンプ
	KEY_T,	// 攻撃
	KEY_Y,	// 攻撃
	KEY_U,	// 攻撃
	// 2P側
	KEY_ARROW, // 移動, しゃがみ, ジャンプ
	KEY_NUMPAD1,// 攻撃
	KEY_NUMPAD2,// 攻撃 
	KEY_NUMPAD3,// 攻撃
	KEY_MAX,
};

struct Sound
{
	int titleBgm;
	int endBgm;
	int clickSe;
	int selectSe;
};

// キャラの音声
struct CharaVoice
{
	int attack = 0;
	int hit = 0;
	int uwa = 0;
};
// ゲーム中の音
struct GameSound
{
	int bgm = 0;
	int fight = 0;
	int ko = 0;
	CharaVoice voice;
};

const int HP_BOX_OFFSET_X = 70;	// HPを描画するBOXの0からの距離
const int HP_BOX_OFFSET_Y = 10;	// HPを描画するBOXの0からの距離
const int HP_BOX_OFFSET_H = 50;	// HPを描画するBOXのYからの高さ
const int HP_DIV_NUM = 20;		// HPの分割する数

const int GAME_TIME_OFFSET = 5;	// ゲーム中の時間文字列の画面外からの距離