#ifndef INPUT_H_
#define INPUT_H_

#include "model.h"
#include "camera.h"
#define NUM_KEY_MAX (256)

class Input {

public:
	static BYTE key[256];
	static BYTE releaseKey[256];
	static BYTE triggerKey[256];
	static bool Keyboard_IsPress(int nKey);
	static bool Keyboard_IsTrigger(int nKey);
	static bool Keyboard_IsRelease(int nKey);
	static void Init();
	static void Update();
};
#endif