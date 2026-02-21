#include "CheckInput.h"

void CheckInputKey::Update()
{
	// 全てのキーの入力状態を得る
	GetHitKeyStateAll(Key_buffer);
	for (int i = 0; i < KEY_NUM; i++)
	{
		if (Key_buffer[i] != 0)
		{
			// コードに対応するキーが押されていたら増やす
			key_push_fream[i]++;
		}
		else
		{
			if (key_push_fream[i] > 0)
			{
				// 離された瞬間だけ-1にする
				key_push_fream[i] = -1;
			}
			else
			{
				// 押されていなければ0にする
				key_push_fream[i] = 0;
			}
		}
	}
}

bool CheckInputKey::PushHitKey(int key) const
{
	if (key_push_fream[key] == 1)
	{
		return true;
	}
	return false;
}

bool CheckInputKey::ReleaseHitKey(int key) const
{
	if (key_push_fream[key] == -1)
	{
		return true;
	}
	return false;
}
