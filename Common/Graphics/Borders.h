#pragma once
#include "Chart.h"
class VBorder
{
public:
	double value;
	int color;
public:
  int penWidth;
  Chart &chart;
  VBorder(Chart &chart);
  void Draw();
  void SetCoordinate(POINTS &);
};

class HBorder
{
public:
	double value;
	int color;
	int widthPen;
public:
  Chart &chart;
  HBorder(Chart &chart);
  void Draw();
};