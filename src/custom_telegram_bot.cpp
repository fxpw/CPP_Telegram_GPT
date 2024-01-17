#include <custom_telegram_bot.hpp>

CustomTelegramBot::CustomTelegramBot(std::string telegram_token, int telegram_admin_id): token(telegram_token), admin_id(telegram_admin_id), bot(telegram_token)
{
	token = telegram_token;
	admin_id = telegram_admin_id;
	// TgBot::Bot bot(telegram_token);
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
		// Getting or creating a user
        CustomTelegramUser& user = all_users.GetUser(message->from->id);

        // We make a request to GPT and get a response
        std::string response = user.RequestToGPT(message->text);

		bot.getApi().sendMessage(message->chat->id, "Your message is: \n" + message->text + "\nGPT Response: \n" + response);
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
