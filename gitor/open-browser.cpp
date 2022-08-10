#include "open-browser.h"

#include <sysarch.h>
#ifdef OS_WIN
#include <Windows.h>
#include <shellapi.h>

bool OpenURL(std::string const& url)
{
	return (INT_PTR)ShellExecuteA(NULL, "open", url.c_str(), 0, 0, SW_SHOWNORMAL) > 0x20;
}
#elif OS_MAC
#include <process.hpp>

bool OpenURL(std::string const& url)
{
	using namespace std::string_literals;
	process::exec("open "s + url);
}
#else

bool OpenURL(std::string const& url)
{
	return false;
}
#endif
