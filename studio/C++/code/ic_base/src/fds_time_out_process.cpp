#include "fds_time_out_process.hpp"
#include "ic_log.h"
#include <algorithm>

FdsTimeOutProcess::FdsTimeOutProcess()
{
}

void FdsTimeOutProcess::start()
{
	stop();
	is_end = false;

	try
	{
		timer_thread = new std::thread(&FdsTimeOutProcess::timer_thread_fun, this);
		IC_LOG_INFO("timer start ... %p", timer_thread);

	}
	catch (std::exception &ex)
	{
		IC_LOG_ERROR("%s", ex.what());
	}
}

FdsTimeOutProcess::~FdsTimeOutProcess()
{
	stop();
}

void FdsTimeOutProcess::timer_thread_fun()
{
	timer_id++;
	while(timer_thread == nullptr) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		IC_LOG_DEBUG("timer_thread_fun %p", timer_thread);
	}
	IC_LOG_INFO("timer_thread_fun %p", timer_thread);
	t_thread_s[timer_thread] = timer_id;
	thread_local uint64_t _timer_id = timer_id;
	std::unique_lock<std::mutex> lock(m_mutex,std::defer_lock);
	do
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(timeSpace));
		lock.lock();
		auto thread_Ptr = std::find_if(t_thread_s.begin(), t_thread_s.end(),
									[this](const std::unordered_map<std::thread *, uint64_t>::value_type item)
									{
										IC_LOG_DEBUG("item.second: %lu %lu", item.second, _timer_id);
										return item.second == _timer_id;
									});
		if(thread_Ptr == t_thread_s.end())
		{
			lock.unlock();
			return;
		}
		lock.unlock();
		if (call_fun != nullptr)
		{
			call_fun(value);
		}
	} while (is_loop);
	is_end = true;
}

void FdsTimeOutProcess::setTimeSpace(const int &space)
{
	timeSpace = space;
}

void FdsTimeOutProcess::setCallFun(FdsTimeOutProCallFun fun)
{
	call_fun = fun;
}

void FdsTimeOutProcess::setValue(const float &v)
{
	value = v;
}

void FdsTimeOutProcess::setCancel(const bool &s)
{
	stop();
}

bool FdsTimeOutProcess::isEnd()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return is_end;
}

void FdsTimeOutProcess::stop()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (timer_thread != nullptr)
	{
		while(!t_thread_s.count(timer_thread))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			IC_LOG_INFO("wait t_thread_s ...");
		}
		std::size_t size = t_thread_s.erase(timer_thread);
		IC_LOG_INFO("remove timer_thread %p remove size: %zu", timer_thread, size);
		timer_thread->detach();
		delete timer_thread;
		timer_thread = nullptr;
		is_end = true;
		IC_LOG_INFO("remove timer_thread end");
	}
}

void FdsTimeOutProcess::setLoop(const bool &loop)
{
	is_loop = loop;
}
