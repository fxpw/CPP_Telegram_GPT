#include "custom_proxy.hpp"
#include <fmt/format.h>

// Initializing Static Variables
std::vector<CustomProxy::ProxyData> CustomProxy::proxyServersData;
int CustomProxy::currentProxyIndex = 0;
std::vector<std::string> CustomProxy::proxiesList;
bool CustomProxy::hasProxy = false;

void CustomProxy::Init()
{
	CustomProxy::hasProxy = false;
	InitializeProxiesServersData();
	if (hasProxy)
	{
		InitializeProxiesLists();
		CustomProxy::currentProxyIndex = rand() % CustomProxy::proxyServersData.size();
		// CustomProxy::proxiesList = {};
		// std::string httpProxy = proxiesList[currentProxyIndex];
		std::cout << "Proxy initialized." << std::endl;
	}
	else
	{
		std::cout << "Proxy not initialized." << std::endl;
	}
}

void CustomProxy::InitializeProxiesLists()
{
	for (const auto &data : proxyServersData)
	{
		std::string proxy = "";
		if (data.is_socs5 == "yes")
		{
			proxy = "socks5://" + data.login + ":" + data.pass + "@" + data.ip + ":" + data.port;
		}
		else
		{
			proxy = "http://" + data.login + ":" + data.pass + "@" + data.ip + ":" + data.port;
		}
		fmt::print(fmt::format("proxy {} \n", proxy));
		proxiesList.push_back(proxy);
	}
}

void CustomProxy::InitializeProxiesServersData()
{
	// for (int i = 1; i <= 10; ++i) {
	// std::ostringstream ipEnv, httpEnv, sockEnv, loginEnv, passEnv;

	// ipEnv << "PROXY_IP";
	// httpEnv << "PROXY_HTTP";
	// sockEnv << "PROXY_SOC5";
	// loginEnv << "PROXY_LOGIN";
	// passEnv << "PROXY_PASSWORD";
	// boolEnv << "PROXY_IS_SOCKS5";

	if (!(custom_env::get_str_param("PROXY_IP") == ""))
	{
		CustomProxy::ProxyData data{
			custom_env::get_str_param("PROXY_IP"),
			custom_env::get_str_param("PROXY_PORT"),
			custom_env::get_str_param("PROXY_LOGIN"),
			custom_env::get_str_param("PROXY_PASSWORD"),
			custom_env::get_str_param("PROXY_USE_SOCKS5")};
		// fmt::print(fmt::format("init {} {} {} \n", getenv(ipEnv.str().c_str())),getenv(loginEnv.str().c_str()),getenv(passEnv.str().c_str()));
		CustomProxy::proxyServersData.push_back(data);
		CustomProxy::hasProxy = true;
	}
	else
	{
		// fmt::print(fmt::format("index for {} don't exist\n", ipEnv.str().c_str()));
	}
	// }
}

// void CustomProxy::SetRandomProxy()
// {
// 	std::set<int> available_indexes;
// 	for (int i = 0; i < proxyServersData.size(); ++i)
// 	{
// 		if (i != currentProxyIndex)
// 		{
// 			available_indexes.insert(i);
// 		}
// 	}

// 	if (!available_indexes.empty())
// 	{
// 		int newProxy = *std::next(available_indexes.begin(), rand() % available_indexes.size());
// 		SetProxy(newProxy);
// 	}
// }

bool CustomProxy::SetProxy(int index)
{
	if (index >= 0 && index < proxiesList.size())
	{
		currentProxyIndex = index;
		std::string httpProxy = proxiesList[currentProxyIndex];
		return true;
	}
	else
	{
		std::cerr << "Invalid proxy index." << std::endl;
		return false;
	}
}

std::string CustomProxy::GetCurrentProxyFromList()
{
	return proxiesList[currentProxyIndex];
}
