#pragma once

#include"Core.h"

#include<string>
#include<boost/filesystem.hpp>
#include<boost/regex.hpp>

namespace pro{

class PRO_EXPORTS Dir
{
private:

	boost::filesystem::path path;

#pragma warning(push)
#pragma warning(disable:4251) // ‰ğŒˆ‚Å‚«‚È‚¢Œx‚ğ—}§
	boost::regex regex;
#pragma warning(pop)

	bool isPath() const;

public:
	Dir(void);
	Dir(std::string path);
	~Dir(void);
	
	const std::string pwd() const;
	void cd(std::string path);

	bool create();
	bool create(std::string path);
	bool remove();
	bool remove(std::string path);
	bool remove_all();
	bool remove_all(std::string path);

	static const char* test();

};

}