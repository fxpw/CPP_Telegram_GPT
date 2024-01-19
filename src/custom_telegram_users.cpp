#include <custom_telegram_users.hpp>


CustomTelegramUsers::CustomTelegramUsers()
{
	std::map<int, CustomTelegramUser> users_list;
}

CustomTelegramUser &CustomTelegramUsers::GetUser(int telegram_user_id,openai::OpenAI*openai_instance)
{
	auto it = users_list.find(telegram_user_id);
	if (it == users_list.end()) {
		// If the user is not on the map, create a new one and replace it
		auto result = users_list.emplace(telegram_user_id, CustomTelegramUser(telegram_user_id,openai_instance));
		return result.first->second;
	} else {
		// If the user already exists, return it
		return it->second;
	}
}

CustomTelegramUser::CustomTelegramUser(int telegram_user_id,openai::OpenAI*openai_instance)
{
	std::map<int, CustomGPTChat> gpt_chats;
	user_id = telegram_user_id;
	fmt::print(fmt::format("new CustomTelegramUser::CustomTelegramUser {} {}\n", telegram_user_id, current_gpt_chat_id));
	CreateGPTChat(openai_instance);
}



bool CustomTelegramUser::CreateGPTChat(openai::OpenAI*openai_instance)
{
	int chat_id = GetLastGPTChatKey()+1;
	current_gpt_chat_id = chat_id;
	auto it = gpt_chats.find(chat_id);
	if (it == gpt_chats.end()) {
		// If the user is not on the map, create a new one and replace it
		auto result = gpt_chats.emplace(chat_id, CustomGPTChat(custom_env::get_str_param("OPENAI_API_KEY"), custom_env::get_str_param("OPENAI_MODEL"), openai_instance));
		return true;
	} else {
		// If the user already exists, return it
		return false;
	}
}

bool CustomTelegramUser::ChangeGPTChat(int chat_id)
{
	current_gpt_chat_id = chat_id;
	return true;
}

CustomGPTChat &CustomTelegramUser::GetCurrentGPTChat()
{
	auto it = gpt_chats.find(current_gpt_chat_id);
	if (it != gpt_chats.end()) {
		// Возвращаем ссылку на чат
		return it->second;
	} else {
		// Если чата с таким ID нет, бросаем исключение или обрабатываем эту ситуацию иначе
		throw std::runtime_error("GPT chat not found");
	}
}

std::string CustomTelegramUser::RequestToGPT(std::string request)
{
	CustomGPTChat& chat = GetCurrentGPTChat();
	return chat.MakeRequest(request);
}

std::map<int, CustomGPTChat> CustomTelegramUser::GetAllGPTChats()
{
	return gpt_chats;
}

int CustomTelegramUser::GetLastGPTChatKey()
{
    if (!gpt_chats.empty()) {
        return gpt_chats.rbegin()->first; // rbegin() возвращает итератор на последний элемент map
    } else {
        return 0;
    }
}

