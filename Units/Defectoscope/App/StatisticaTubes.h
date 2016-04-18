#pragma once
class App;
class Statistica
{
	App &app;
public:
	Statistica(App &app);
	void AddTube();
	void AddBrakTube();
	void Clear();
};