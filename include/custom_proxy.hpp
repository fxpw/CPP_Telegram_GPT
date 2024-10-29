#ifndef CUSTOM_PROXY_HPP
#define CUSTOM_PROXY_HPP
	#ifdef _WIN32
		#include <windows.h>
	#else
		#include <cstdlib>
	#endif
	#include <string>
	#include <vector>
	#include <random>
	#include <iostream>
	#include <set>
	#include <algorithm>
	#include <custom_env.hpp>
	#include <sstream>

	class CustomProxy {
	public:
		struct ProxyData {
			std::string ip;
			std::string port;
			std::string login;
			std::string pass;
			std::string is_socs5;
		};

		static std::vector<ProxyData> proxyServersData;
		static int currentProxyIndex;
		static std::vector<std::string> proxiesList;
		static bool hasProxy;

		static void Init();
		static void InitializeProxiesLists();
		static void InitializeProxiesServersData();
		static void SetRandomProxy();
		static bool SetProxy(int index = 0);
		static std::string GetCurrentProxyFromList();
	};

#endif // CUSTOM_PROXY_HPP