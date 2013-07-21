#pragma once

#include"Core.h"

#include<string>
#include<boost/filesystem.hpp>

// �f�B���N�g���ɂ����Ă͂����Ȃ�������T�����鐳�K�\��
#define DIR_REGEX_STR "[:*?\"<>|]"

namespace pro{

// error C2061: �\���G���[ : ���ʎq 'DirException'
class DirException;

class PRO_EXPORTS Dir
{
public:

	typedef enum CreateOption{
		NONE = 0,					// �ݒ�Ȃ�
		ANOTHER_CREATE = 1,			// ���݂����ꍇ�ق��ɍ��
		OVER_WRITE_REMOVE_ALL = 2,	// ���݂����ꍇ���ׂď����č�蒼��
		OVER_WRITE = 4,				// ���݂���̏ꍇ�����č�蒼��
		CREATE_DIRS = 8				// ���ԃf�B���N�g�����쐬����
	}CreateOption;

private:

	boost::filesystem::path path;

	bool ErrorShow;

//#pragma warning(push)
//#pragma warning(disable:4251) // �����ł��Ȃ��x����}��
//	boost::regex const regex;
//#pragma warning(pop)

public:
	Dir(bool errorShow = false);
	Dir(const std::string& path,bool errorShow = false);
	~Dir(void);
	
	const std::string pwd() const;
	void cd(const std::string& path);
	void cd(const std::string& path,DirException e);

	bool create(int option = NONE);
	bool create(const std::string& path,int option = NONE);
	bool remove();
	bool remove(const std::string& path);
	boost::uintmax_t remove_all();
	boost::uintmax_t remove_all(const std::string& path);

	static const char* test();
	
	static bool isPath(const std::string& path);
	static bool isPath(const boost::filesystem::path& path);
	

};

}