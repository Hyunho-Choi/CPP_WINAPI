#include <ctime>
#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
	startTime = clock();
}

Stopwatch::~Stopwatch()
{
}

void Stopwatch::start()
{
	startTime = clock();
}

void Stopwatch::stop()
{
	endTime = clock();
}

long long int Stopwatch::getEleapsedTime()
{

	if (startTime < endTime)
		return (endTime - startTime);
	else
	{
		return (clock() - startTime);
	}
}
