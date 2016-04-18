#pragma once
//#include "uspc7100_exports.h"
class MainWindow;

struct Long{};
struct Cross{};
struct Thickness{};

class App
{
public:
	static const int distance_between_sensors = 2850;//базовое расстояние для пересчёта импульсов на зону
	static const int MAX_VAL_791 = int((double)0x1fff / 100);
	static const int zonesCount = 60;
	static const int cross_count_sensors = 12;
	static const int long_count_sensors = 4;
	static const int total_count_sensors = cross_count_sensors + long_count_sensors;
	static const int zone_length = 200;
	//static const int count_frames = 512 * 1024 * 1024 / sizeof(double);
	//static const int count_frames_per_channel = count_frames / (total_count_sensors);
	static const int count_frames = 64 * 1024 * 1024 / total_count_sensors;
	static const int status_number_tube = 0;
	static const int status_tablo = 1;
	static const int status_lir = 2;
	static const int status_typesize = 3;
	static HANDLE ProgrammExitEvent;
	static HANDLE ProgrammContinueEvent;
	static HANDLE ProgrammStopEvent;
	static HANDLE WaitThicknessEvent;
	static bool measurementOfRunning;
public:
	MainWindow &mainWindow;
public:
	App();
	void Init();
	void Destroy();
	void MainWindowTopLabel(wchar_t *);
	void MainWindowBottomLabel(int, wchar_t *);  
	void MainWindowUpdate();

	bool StopAfterCycle();
};

extern App app;

template<class T>struct Singleton
{
	static T& Instance(){static T x; return x;}
};




