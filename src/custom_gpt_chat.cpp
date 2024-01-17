#include <custom_gpt_chat.hpp>



CustomGPTChat::CustomGPTChat(std::string openai_api_key, std::string openai_model)
{
	std::string api_key = openai_api_key;
	std::string model = openai_model;
}

std::string CustomGPTChat::MakeRequest(std::string request_text)
{
	nlohmann::json request;
	request["model"] = model;
	request["prompt"] = request_text;
	request["max_tokens"] = 7;
	request["temperature"] = 0;
	return request_text;
}
