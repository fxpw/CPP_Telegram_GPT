# cpp telegram+chat_gpt project

Thats simple custom telegram bot for use whit youre ChatGPT, also have proxies support if it needed

# Run

Before run

* check and change your .env.example/.env whit your parametrs
* rename .env.example to .env
* .env and cpp_telegram_gpt file need to be at same directory
* if need use proxy add it to .env
* run cpp_telegram_gpt

# Build

```bash
make build_project_release #build release
```

```bash
make build_project_debug #build release
```

Check Makefile for more commands

# Info

Сhange ./vscode/settings.json:"CMAKE_TOOLCHAIN_FILE" if you build whit vcpkg in vscode

# Used libs\headers\things

* https://github.com/fxpw/openai-cpp
* https://github.com/fxpw/tgbot-cpp
* https://github.com/fxpw/fmt
* https://github.com/fxpw/boost
* https://github.com/fxpw/curl
* https://github.com/fxpw/json
