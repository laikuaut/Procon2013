#include "Timer.h"

namespace pro{

Timer::Timer(void)
{
	reset();
}

Timer::~Timer(void)
{
}

clock_t Timer::m_sec(long sec){
	return sec * PER_SEC;
}

void Timer::setState(t_state state){
	this->state = state;
}

Timer::t_state Timer::getState(){
	return state;
}

clock_t Timer::getStartTime() const{
	return this->start_time;
}

clock_t Timer::getStopTime() const{
	return this->stop_time;
}

clock_t Timer::getSumStop() const{
	return this->sum_stop;
}

void Timer::start(){
	reset();
	start_time = clock();
	setState(Timer::START);
}

clock_t Timer::stop(){
	if(start_time == -1) return -1;
	stop_time = clock();
	setState(Timer::STOP);
	return stop_time;
}

clock_t Timer::restart(){
	if(start_time == -1) return -1;
	sum_stop += clock() - stop_time;
	stop_time = -1;
	setState(Timer::START);
	return sum_stop;
}

void Timer::reset(){
	start_time = -1;
	stop_time = -1;
	sum_stop = 0;
	lap_time.clear();
	setState(Timer::RESET);
}

clock_t Timer::lap(){
	if(start_time == -1) return -1;
	lap_time.push_back(getNow());
	return lap_time.back();
}

clock_t Timer::lap(long m_sec){
	if(m_sec < 0)
		throw OutOfRangeException<long>(m_sec,"m_sec","Timer.cpp","Timer::lap()");
	if(start_time == -1) return -1;
	if(lap_time.empty())	lap_time.push_back(m_sec);
	else lap_time.push_back(lap_time.back() + m_sec);
	return lap_time.back();
}

clock_t Timer::getDiff(){
	if(start_time == -1 || stop_time != -1) return -1;
	if(lap_time.empty())
		return getNow();
	else
		return getNow() - lap_time.back();
}

clock_t Timer::getNow(){
	if(start_time == -1) return -1;
	if(stop_time == -1) return clock() - sum_stop - start_time;
	else return stop_time - sum_stop - start_time;
}

}