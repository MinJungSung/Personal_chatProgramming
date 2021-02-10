#pragma once
#ifndef FUNCTION_POOL_H
#define FUNCTION_POOL_H

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cassert>

class Function_pool{

private:
	std::queue<std::function<void()>> m_function_queue;
	std::mutex m_lock;
	std::condition_variable m_data_condition;
	std::atomic<bool> m_accept_functions;
public:
	Function_pool();
	~Function_pool();
	void push(std::function<void()> func);
	void done();
	void infinite_loop_func();

};
#endif
