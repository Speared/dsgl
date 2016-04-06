#pragma once
//https://social.msdn.microsoft.com/Forums/vstudio/en-US/e1d979c0-270f-4369-b84c-87c7c6a4d0c8/cc-about-getkeystate?forum=vcgeneral
#include "Component.h"
class FirstPersonControl :
	public Component
{
public:
	void Update();
	FirstPersonControl();
	~FirstPersonControl();
};

