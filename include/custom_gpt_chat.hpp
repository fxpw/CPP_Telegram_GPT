#ifndef CUSTOM_GPT_CHAT_HPP
#define CUSTOM_GPT_CHAT_HPP
	#include <openai.hpp>
	#include <string>
	#include <fmt/format.h>
	class CustomGPTChat{
		private:
			std::string model;
			std::string api_key;
			openai::OpenAI* openai_instance;
		public:
			CustomGPTChat(std::string openai_api_key, std::string openai_model,openai::OpenAI*openai_instance);
			~CustomGPTChat() = default;
			bool ChangeModel(std::string openai_model);
			bool ChangeAPIKey(std::string openai_api_key);
			std::string MakeRequest(std::string request_text);
	};
#endif //CUSTOM_GPT_CHAT_HPP