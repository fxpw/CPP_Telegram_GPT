#include <custom_gpt_chat.hpp>



CustomGPTChat::CustomGPTChat(std::string openai_api_key, std::string openai_model,openai::OpenAI*openai_instance):api_key(openai_api_key),model(openai_model),openai_instance(openai_instance)
{
}

std::string CustomGPTChat::MakeRequest(std::string request_text)
{
	nlohmann::json request;
	request["model"] = model;
	request["messages"] = nlohmann::json::array({ 
		{{"role", "user"}, {"content", request_text}} 
	});
	// request["max_tokens"] = 17;
	request["temperature"] = 0;
	auto response = openai_instance->chat.create(request);
	// fmt::print(std::string(response.dump(4)));
	std::cout<<response.dump(4)<<std::endl;
    if (response.contains("choices") && response["choices"].is_array()) {
        auto choices = response["choices"];
        if (!choices.empty() && choices[0].contains("message") && choices[0]["message"].contains("content")) {
            std::string content = choices[0]["message"]["content"];
			// fmt::print(fmt::format("{}",std::string(response.dump(4))));
            return content;
        }
    }
	// for debug
	return response.dump(4);
}

