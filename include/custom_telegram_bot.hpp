#ifndef CUSTOM_TELEGRAM_BOT_HPP
#define CUSTOM_TELEGRAM_BOT_HPP
	#include <tgbot/tgbot.h>
	
	#include <custom_telegram_users.hpp>
	#include <string>
	#include <exception>

	class CustomTelegramBot{
		private:
			std::string token;
			int admin_id;
			TgBot::Bot bot;
			CustomTelegramUsers all_users;
		public:
			CustomTelegramBot(std::string telegram_token, int telegram_admin_id);
			~CustomTelegramBot();
			void RegisterEvents();
			// TgBot::Bot GetBot();
			bool Close();
	};
#endif //CUSTOM_TELEGRAM_BOT_HPP