#ifndef CUSTOM_ENV_HPP
#define CUSTOM_ENV_HPP
	#include <cstdlib>
	#include <iostream>
	#include <fstream>
	#include <string>
	#include <fmt/format.h>
	namespace custom_env{
		void load_dotenv();
		std::string get_str_param(const char* param_name);
		int get_int_param(const char* param_name);
	}
#endif // CUSTOM_ENV_HPP
