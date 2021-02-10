#include "function_pool.h"

Function_pool::Function_pool():m_function_queue(),m_lock(),m_data_condition(),m_accept_functions(true){}
Function_pool::~Function_pool(){}

void Function_pool::push(std::function<void()>func){
	std::unique_lock<std::mutex> lock(m_lock);
	m_function_queue.push(func);
	lock.unlock();
	m_data_condition.notify_one();
} 

void Function_pool::done(){
	std::unique_lock<std::mutex> lock(m_lock);
	m_accept_functions = false;
	lock.unlock();
	m_data_condition.notify_all();
}

void Function_pool::infinite_loop_func(){
	std::function<void()> func;
	while(true){
		{
			std::unique_lock<std::mutex> lock(m_lock);
			m_data_condition.wait(lock,[this]() {return !m_function_queue.empty() || !m_accept_functions;});
			if(!m_accept_functions && m_function_queue_empty()){return;}
			func = m_function_queue.front();
			m_function_queue.pop();
		}
		func();
	}
}
