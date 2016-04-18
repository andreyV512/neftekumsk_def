#pragma once

class Automat
{
public:
	Automat();
	void Init();
	static void RotationOn();
	static void RotationOff();
};

extern Automat automat;