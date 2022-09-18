#pragma once

namespace KeyInput
{
	enum Key
	{
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_0,
		KEY_Q,
		KEY_W,
		KEY_E,
		KEY_R,
		KEY_T,
		KEY_Y,
		KEY_U,
		KEY_I,
		KEY_O,
		KEY_P,
		KEY_A,
		KEY_S,
		KEY_D,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_Z,
		KEY_X,
		KEY_C,
		KEY_V,
		KEY_B,
		KEY_N,
		KEY_M,

		KEY_SPACE,
		KEY_TAB,

		// Mouse butts
		KEY_MB_1,
		KEY_MB_2,
		KEY_MB_3,
		KEY_MB_4,
		KEY_MB_5,
		KEY_MB_6,
		KEY_MB_7,
		KEY_MB_8,

		MOUSE_POS_X,
		MOUSE_POS_Y,
		MOUSE_SCROLL_X,
		MOUSE_SCROLL_Y,
		MOUSE_ENTER,
		MOUSE_LEAVE,

		//default
		KEY_UNKNOWN
	};

	enum Mod
	{	
		CTRL = 1 << 0,
		SHIFT = 1 << 1,
		ALT = 1 << 2,
		MOD_UNKNOWN = 1 << 8
	};


	enum Action
	{
		PRESS,
		REPEAT,
		RELEASE,
		UNKNOWN
	};
}

enum ActionEnum
{
	ACTION,
	RANGE
};