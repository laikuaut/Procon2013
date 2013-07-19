#pragma once

#include"Core.h"

#include<string>

namespace pro{

class PRO_EXPORTS Dir
{
private:
	
	std::string abs_path;
	std::string rel_path;
	std::vector<std::string> array_path;

	std::string drive_name;

	void createArrayPath();
	
	// •s•K—v
	bool isAbsPath(std::string path);
	bool isRelPath(std::string path);

	/* func
	_mkdir
	_chdir
	_fullpath
	_getdrive
	_getcwd
	_getdcwd
	_chdrive
	_rmdir
	*/

public:
	Dir(void);
	Dir(std::string path);
	~Dir(void);

	std::string pwd();
	void ls();
	void cd(std::string path);

	void create(std::string path);
	void remove(std::string path);

};

}