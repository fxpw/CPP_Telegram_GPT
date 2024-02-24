#include <custom_gpt_chat.hpp>


CustomGPTChat::CustomGPTChat(std::string openai_api_key, std::string openai_model,openai::OpenAI*openai_instance):api_key(openai_api_key),model(openai_model),openai_instance(openai_instance)
{
}

std::string CustomGPTChat::MakeRequest(std::string request_text)
{
	try {
		nlohmann::json request;
		request["model"] = model;
		int max_tokens = 4096 - static_cast<int>(request_text.size());
		std::string truncated_text = request_text.substr(0, 4095);
		request["messages"] = nlohmann::json::array({ 
			{{"role", "user"}, {"content", truncated_text}} 
		});
		request["max_tokens"] = max_tokens > 0 ? max_tokens : 0;
		request["temperature"] = 0;
		auto response = this->openai_instance->chat.create(request);
		std::cout<<response.dump(4)<<std::endl;
		if (response.contains("choices") && response["choices"].is_array()) {
			auto choices = response["choices"];
			if (!choices.empty() && choices[0].contains("message") && choices[0]["message"].contains("content")) {
				std::string content = choices[0]["message"]["content"];
				return content;
			}
		}
		return response.dump(4);
	}catch (const std::exception& e) {
		return fmt::format("Error: {}", e.what());
	}
}

