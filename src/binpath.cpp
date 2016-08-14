#include "binpath.hpp"

#if defined (__linux__)
	#include "linux/binreloc.h"
#elif defined (__APPLE__)
	#include <mach-o/dyld.h>
	#include <CoreServices/CoreServices.h>
#else
	#include <windows.h>
	#include <shlobj.h>
#endif

#include <stdexcept>
#include <sstream>

namespace binpath {
	std::string get() {
		static std::string* binpath = nullptr;
		if (binpath) {
			return *binpath;
		}
		binpath = new std::string;
	#if defined(__linux__)
		BrInitError error;
		if (br_init(&error) == 0 && error != BR_INIT_ERROR_DISABLED) {
			std::stringstream tmp;
			tmp << "BinReloc failed to initialize (error code " << error << ")";
			throw std::runtime_error(tmp.str());
		}
		auto tmp = br_find_exe_dir("");
		*binpath = tmp;
		free(tmp);
		*binpath += '/';
	#elif defined(__APPLE__)
		uint32_t size = 0;
		if (_NSGetExecutablePath(NULL, &size) == 0) {
			throw std::runtime_error("Can't get executable path!");
		}
		std::vector<char> tmp(size);
		_NSGetExecutablePath(&tmp[0], &size);
		prefix.assign(tmp.begin(), tmp.end());
		boost::filesystem::path prefixPath(prefix);
		*binpath = prefixPath.normalize().remove_leaf().parent_path().string() + "/";
	#else
		char filename[MAX_PATH];
		GetModuleFileName(NULL, filename, MAX_PATH);
		std::string tmp(filename);
		*binpath = tmp.substr(0, tmp.find_last_of("\\/") + 1);
	#endif
		return *binpath;
	}
}
