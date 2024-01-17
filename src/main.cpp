// #include <stdlib.h>
// #include <tgbot/tgbot.h>
#include <custom_env.hpp>
// #include <openai.hpp>
#include <custom_proxy.hpp>
#include <custom_telegram_bot.hpp>

int main()
{
	custom_env::load_dotenv();
	std::string telegram_bot_token = custom_env::get_str_param("TELEGRAM_TOKEN");
	if (telegram_bot_token == "") {return 1;};
	int telegram_bot_admin_id = custom_env::get_int_param("TELEGRAM_ADMIN_ID");

	CustomProxy::Init();
	CustomTelegramBot tg_bot(telegram_bot_token,telegram_bot_admin_id);
	// const char *openai_api_key = getenv("OPENAI_API_KEY");
	// const char *openai_model = getenv("OPENAI_MODEL");
	// std::cout << openai_api_key << std::endl;
	// std::string proxyUrl = Proxy::GetCurrentProxyFromList();
	// openai::OpenAI openai_instance{openai_api_key};
	// // fmt::print(proxyUrl);
	// openai_instance.setProxy(proxyUrl);

	// nlohmann::json request;
	// request["model"] = openai_model ? std::string(openai_model) : "gpt-3.5-turbo";
	// request["prompt"] = "Say this is a test";
	// request["max_tokens"] = 7;
	// request["temperature"] = 0;
	// auto response = openai_instance.completion.create(request);
	// std::cout << "Response is:\n" << response.dump(4) << '\n';
	return 0;
}
