#include "MyException.h"

MyException::MyException(const std::string &Msg):msg(Msg)
{

}

const char * MyException::what() const noexcept 
{

	return msg.c_str();
}
