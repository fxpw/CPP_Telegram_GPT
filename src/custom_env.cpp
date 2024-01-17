#include "custom_env.hpp"

void custom_env::load_dotenv() {
	std::ifstream env_file(".env");
	std::string line;
	while (std::getline(env_file, line)) {
		size_t delimiter_pos = line.find('=');
		if (delimiter_pos != std::string::npos) {
			std::string key = line.substr(0, delimiter_pos);
			std::string value = line.substr(delimiter_pos + 1);
			// fmt::print(fmt::format("\"{}\" = \"{}\"\n", key.c_str(), value.c_str()));
			setenv(key.c_str(), value.c_str(), 1);
		}
	}
}
std::string custom_env::get_str_param(const char* param_name)
{
	const char *_temp_param = getenv(param_name);
	if (_temp_param == NULL){
		return "error";
	}
	return std::string(_temp_param);
}
int custom_env::get_int_param(const char* param_name)
{
	const char *_temp_param = getenv(param_name);
	if (_temp_param == NULL){
		return 0;
	}
	return atoi(_temp_param);
}
