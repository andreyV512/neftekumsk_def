#include "stdafx.h"
#include "CuttingTube.h"

static int Cutting(char (&status)[60], int &cutting0, int &cutting1, int count, bool(*Test)(char))
{
	int length = 0;
	int i = cutting1;
	for(; i < count && 0 == status[i]; ++i);
	cutting0 = cutting1 = i;
	for(; i < count; ++i)
	{
		if((*Test)(status[i]) || i == count - 1)
		{		
			cutting1 = i;
			length = cutting1 - cutting0;
			int x0 = 1 + i;
			int x1 = 1 + i;
			int len = Cutting(status, x0, x1, count, Test);
			if(len > length)
			{
				cutting0 = x0;
				cutting1 = x1;
				return len;
			}
			else
			{
				return length;
			}
		}
	}
	return length;
}

int CuttingTube(char (&status)[60], int &cutting0, int &cutting1, int count, bool(*Test)(char))
{
	Cutting(status, cutting0, cutting1, 1 + count, Test);
	if(0 != cutting0) ++cutting0;
	int res = cutting1 - cutting0;
	if(count == cutting1) cutting1 = 0;
	return res;
}