// #include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <fmt/format.h>
#include <tgbot/tgbot.h>

void load_dotenv()
{
	std::ifstream env_file(".env");
	std::string line;
	while (std::getline(env_file, line))
	{
		size_t delimiter_pos = line.find('=');
		if (delimiter_pos != std::string::npos)
		{
			std::string key = line.substr(0, delimiter_pos);
			std::string value = line.substr(delimiter_pos + 1);
			fmt::print(fmt::format("{} = {}\n",key.c_str(),value.c_str()));
			setenv(key.c_str(), value.c_str(), 1);
		}
	}
}

int main()
{
	load_dotenv();
	const char *bot_token = getenv("telegram_token");
	std::cout << bot_token << std::endl;
	return 0;
}
