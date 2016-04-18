#pragma once

class App;
class CountingTube
{
public:
	wchar_t fileName[1024];
	App &app;
	CountingTube();
	void AddCommon();
	void AddBrak();
	void Update();
	void Clear();
};