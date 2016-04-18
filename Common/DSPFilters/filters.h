#pragma once

struct ChebyshevI
{
static void Do(
	double *data,
	int N,
	int order,
	double sampleRate,
	double cutoffFrequency,
	double centerFrequency,
	double widthFrequency,
	double rippleDb,
	int type
	);
};

struct Butterworth
{
void Do(
	double *data,
	int    N,
	int    order,
	double sampleRate,
	double cutoffFrequency,
	double centerFrequency,
	double widthFrequency,
	int    type
	);
};

struct Elliptic
{
static void Do(
	double *data,
	int    N,
	int    order,
	double sampleRate,
	double cutoffFrequency,
	double centerFrequency,
	double widthFrequency,
	double rippleDb,
	double rolloff,
	int    type
	);
};
