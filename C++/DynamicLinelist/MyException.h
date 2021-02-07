	#pragma once
	#include<exception>
	#include<string>
	class MyException :public std::exception
	{
	public:
		MyException(const std::string &Msg);

		 ~MyException()=default;
	
		virtual const char* what()const noexcept override;
	private:
		std::string msg;
	};

