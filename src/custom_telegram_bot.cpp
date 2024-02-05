#include <custom_telegram_bot.hpp>

CustomTelegramBot::CustomTelegramBot(std::string telegram_token, int64_t telegram_admin_id): token(telegram_token), admin_id(telegram_admin_id), bot(telegram_token)
{
	token = telegram_token;
	admin_id = telegram_admin_id;
	
	std::string openai_api_key = custom_env::get_env_var("OPENAI_API_KEY");
	// const char * openai_model = getenv("OPENAI_MODEL");
	std::string proxyUrl = CustomProxy::GetCurrentProxyFromList();
	// openai_instance = nullptr;
	openai_instance = new openai::OpenAI(openai_api_key);
	openai_instance->setProxy(proxyUrl);

	CustomTelegramUsers users_list;
	RegisterEvents();
	try
	{
		printf("Bot username: %s\n", this->bot.getApi().getMe()->username.c_str());
		this->bot.getApi().deleteWebhook();

		TgBot::TgLongPoll longPoll(this->bot);
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
	this->bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr message)
	{
		this->bot.getApi().sendMessage(message->chat->id, "Hello, this is a test bot written in cpp and associated with ChatGPT 3.5 turbo.!");
	});
	bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr message)
	{
		fmt::print(fmt::format("User wrote {}\n", message->text));
		if (StringTools::startsWith(message->text, "/start")) {
			this->bot.getApi().sendMessage(message->chat->id, std::string("For more info check https://github.com/fxpw/CPP_Telegram_GPT"),false,0,nullptr,"Markdown");
			return;
		}
		bool isCheckIdRequired = custom_env::get_str_param("TELEGRAM_NEED_CHECK_ID") == "TRUE";
		bool isAdminId = std::to_string(message->chat->id) == custom_env::get_str_param("TELEGRAM_ADMIN_ID");
		bool isCheckIdNotRequired = custom_env::get_str_param("TELEGRAM_NEED_CHECK_ID") == "FALSE";
		if (isCheckIdNotRequired || (isCheckIdRequired && isAdminId)){
			CustomTelegramUser& user = this->all_users.GetUser(message->from->id,openai_instance);
			std::string response = user.RequestToGPT(message->text);
			try{
				this->bot.getApi().sendMessage(message->chat->id, "Your message is: \n" + message->text + fmt::format("\n\nChatGPT({}) answer: \n",custom_env::get_str_param("OPENAI_MODEL")) + response,false,0,nullptr,"Markdown");
			}
			catch (std::exception &e)
			{
				fmt::print(fmt::format("error {}\n", e.what()));
			}
			return;
		}else{
			this->bot.getApi().sendMessage(message->chat->id, std::string("You not user for that bot.\n For more info check https://github.com/fxpw/CPP_Telegram_GPT"),false,0,nullptr,"Markdown");
		}
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
