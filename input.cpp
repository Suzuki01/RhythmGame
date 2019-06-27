#include "main.h"
#include "input.h"

BYTE	Input::key[NUM_KEY_MAX] = {};
BYTE	Input::triggerKey[NUM_KEY_MAX] = {};
BYTE	Input::releaseKey[NUM_KEY_MAX] = {};

void Input::Init() {
}


void Input::Update() {
	BYTE aKeyState[NUM_KEY_MAX];

	if (GetKeyboardState(aKeyState))
	for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
	{
		// �L�[�g���K�[�E�����[�X���𐶐�
		triggerKey[nCnKey] = (key[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
		releaseKey[nCnKey] = (key[nCnKey] ^ aKeyState[nCnKey]) & key[nCnKey];
		// �L�[�v���X����ۑ�
		key[nCnKey] = aKeyState[nCnKey];

	}
}


bool Input::Keyboard_IsPress(int nKey) {
	return (key[nKey] & 0x80) ? true : false;
}

bool Input::Keyboard_IsTrigger(int nKey) {
	return (triggerKey[nKey] & 0x80) ? true : false;
}

bool Input::Keyboard_IsRelease(int nKey) {
	return (releaseKey[nKey] & 0x80) ? true : false;
}