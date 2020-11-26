#include <iostream>
#include <exception>
#include <stdexcept>

namespace errorHandler{

	void room_unexp() 
	{
		throw;
	}
	
	void room_bad_exception throw(std::bad_exception)
	{
		throw std::runtime_error("Room");
	}

}
