#pragma once
class Stopwatch
{

private:
	long long int startTime;
	long long int endTime;

public:
	Stopwatch();
	~Stopwatch();

	long long int getStartTime() { return startTime; }
	long long int getEndTime() { return endTime; }

	void start();
	void stop();
	long long int getEleapsedTime();

};
