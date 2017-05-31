#pragma once
#include "App.h"

class ResultViewerData
{
public:
	double tresholdKlass1;
	double tresholdKlass2;
	double tresholdKlass3;
	unsigned klass;
	char numberTube[5];
	int cutting0, cutting1, lengthTube;
    int currentOffset;
	char commonStatus[App::zonesCount];
	unsigned char zonesAsu[65];
	bool brak;
	bool sendData;
	bool counting;
	ResultViewerData();
};