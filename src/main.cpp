// #include <stdlib.h>
// #include <tgbot/tgbot.h>

// #include <openai.hpp>
#include <custom_telegram_bot.hpp>

int main()
{
	custom_env::load_dotenv();
	CustomProxy::Init();
	std::string telegram_bot_token = custom_env::get_str_param("TELEGRAM_TOKEN");
	if (telegram_bot_token == "") {return 1;};
	int telegram_bot_admin_id = custom_env::get_int_param("TELEGRAM_ADMIN_ID");
	CustomTelegramBot tg_bot(telegram_bot_token,telegram_bot_admin_id);


	// nlohmann::json request;
	// request["model"] = openai_model ? std::string(openai_model) : "gpt-3.5-turbo";
	// request["messages"] = nlohmann::json::array({ 
	// 	{{"role", "user"}, {"content", "blah"}} 
	// });
	// request["max_tokens"] = 17;
	// request["temperature"] = 0;
	// auto response = openai_instance.chat.create(request);
	// std::cout << "Response is:\n" << response.dump(4) << '\n';
	return 0;
}
