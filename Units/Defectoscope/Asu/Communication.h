#pragma once

namespace Communication
{
	void Init();
	void Destroy();
	bool TestCommunication1();
	bool QueryNumberTube2(char(&numberTube)[5]);
	bool TransferControlResul3(
		char(&numberTube)[5]

		, int length

		, int cuttingArea1
		, int cuttingArea2

		, int resultControlCommon

		, unsigned char *zones
		);

	void AsuTestCommunication1();
	void AsuQueryResultControl2();
	void AsuTransferControlParameters4();

	struct FromASU
	{	
		static const unsigned char TUBE_OK = 0x31;
		static const unsigned char BRAK = 0x32;
		static const unsigned char CUTTING = 0x80;
		int cuttingArea2;
		bool tubeOk;
	};
}


