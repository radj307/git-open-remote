#include "rc/version.h"
#include "open-browser.h"

#include <TermAPI.hpp>
#include <opt3.hpp>
#include <process.hpp>
#include <envpath.hpp>

struct Help {
	friend std::ostream& operator<<(std::ostream& os, const Help& h)
	{
		return os
			<< "gitor v" << gitor_VERSION_EXTENDED << '\n'
			<< "  Opens the default git remote of the repository in the working directory.\n"
			<< '\n'
			<< "USAGE:\n"
			<< "  gitor [OPTIONS]" << '\n'
			<< '\n'
			<< "OPTIONS:\n"
			<< "  -h, --help           Shows this help display, then exits." << '\n'
			<< "  -v, --version        Shows the current version number, then exits." << '\n'
			;
	}
};

inline std::optional<std::string> exec(const std::string& command)
{
	std::stringstream ss;
	if (process::exec(&ss, command) == 0)
		return ss.str();
	return std::nullopt;
}

inline constexpr auto GIT_GET_REMOTE_URL{ "git ls-remote --get-url" };

int main(const int argc, char** argv)
{
	try {
		opt3::ArgManager args{ argc, argv };

		const bool quiet{ args.check_any<opt3::Flag, opt3::Option>('q', "quiet") };

		if (args.check_any<opt3::Flag, opt3::Option>('h', "help")) {
			std::cout << Help{};
			return 0;
		}
		else if (args.check_any<opt3::Flag, opt3::Option>('v', "version")) {
			if (!quiet) std::cout << "gitor v";
			std::cout << gitor_VERSION_EXTENDED << '\n';
			return 0;
		}


		if (const auto& remote{ exec(GIT_GET_REMOTE_URL) }; remote.has_value())
			OpenURL(remote.value());
		else throw make_exception("Directory '", std::filesystem::current_path().generic_string(), "' is not a git repository!");

		return 0;
	} catch (const std::exception& ex) {
		std::cerr << term::get_fatal() << ex.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << term::get_fatal() << "An undefined exception occurred!" << std::endl;
		return 1;
	}
}
