#ifndef CUSTOM_TELEGRAM_USERS_HPP
#define CUSTOM_TELEGRAM_USERS_HPP
	#include <map>
	#include <custom_env.hpp>
	#include <custom_gpt_chat.hpp>
	#include <fmt/format.h>
	class CustomTelegramUser{
		public:
			int current_gpt_chat_id;
			int user_id;
			std::map<int, CustomGPTChat> gpt_chats;

			CustomTelegramUser(int telegram_user_id);
			bool CreateGPTChat();
			bool ChangeGPTChat(int chat_id);
			CustomGPTChat& GetCurrentGPTChat();
			std::string RequestToGPT(std::string request);
			std::map<int, CustomGPTChat> GetAllGPTChats();
			int GetLastGPTChatKey();
	};
	class CustomTelegramUsers{
		public:
			std::map<int, CustomTelegramUser> users_list;
			
			CustomTelegramUsers();
			CustomTelegramUser& GetUser(int telegram_user_id);
	};
#endif //CUSTOM_TELEGRAM_USERS_HPP

