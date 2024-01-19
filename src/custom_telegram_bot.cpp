#include <custom_telegram_bot.hpp>

CustomTelegramBot::CustomTelegramBot(std::string telegram_token, int telegram_admin_id): token(telegram_token), admin_id(telegram_admin_id), bot(telegram_token)
{
	token = telegram_token;
	admin_id = telegram_admin_id;
	
	const char * openai_api_key = getenv("OPENAI_API_KEY");
	// const char * openai_model = getenv("OPENAI_MODEL");
	std::string proxyUrl = CustomProxy::GetCurrentProxyFromList();
	openai_instance = new openai::OpenAI(openai_api_key);
	openai_instance->setProxy(proxyUrl);

	CustomTelegramUsers users_list;
	RegisterEvents();
	try
	{
		printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
		bot.getApi().deleteWebhook();

		TgBot::TgLongPoll longPoll(bot);
		while (true)
		{
			printf("Long poll started\n");
			longPoll.start();
		}
	}
	catch (std::exception &e)
	{
		printf("error: %s\n", e.what());
	}
}

CustomTelegramBot::~CustomTelegramBot()
{
}


void CustomTelegramBot::RegisterEvents()
{
	bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr message)
	{ bot.getApi().sendMessage(message->chat->id, "Hello, this is a test bot written in cpp and associated with ChatGPT 3.5 turbo.!"); });
	bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr message)
	{
		printf("User wrote %s\n", message->text.c_str());
		if (StringTools::startsWith(message->text, "/start")) {
			return;
		}
		if (std::to_string(message->chat->id)==custom_env::get_str_param("TELEGRAM_ADMIN_ID")) {
			CustomTelegramUser& user = all_users.GetUser(message->from->id,openai_instance);
			std::string response = user.RequestToGPT(message->text);
			bot.getApi().sendMessage(message->chat->id, "Your message is: \n" + message->text + fmt::format("\n\nChatGPT({}) answer: \n",custom_env::get_str_param("OPENAI_MODEL")) + response,false,0,nullptr,"Markdown");
			return;
		}
		bot.getApi().sendMessage(message->chat->id, std::string("You not user for that bot.\n For more info check https://github.com/fxpw/CPP_Telegram_GPT"),false,0,nullptr,"Markdown");
	});
}

// TgBot::Bot CustomTelegramBot::GetBot()
// {
// 	return bot;
// }

bool CustomTelegramBot::Close()
{
	return false;
}
