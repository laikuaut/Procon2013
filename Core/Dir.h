#pragma once

#include"Core.h"

#include<string>
#include<boost/filesystem.hpp>

// �f�B���N�g���ɂ����Ă͂����Ȃ�������T�����鐳�K�\��
#define DIR_REGEX_STR "[:*?\"<>|]"

namespace pro{

// error C2061: �\���G���[ : ���ʎq 'DirException'
class DirException;

/**               ���� 
 * boost::filesystem::path �� std::string ��
 * �I�[�o�[���[�h�������܂��Ȍ^�ƂȂ邽��
 * boost:filesystem::path �Ɉ����𓝈ꂷ��B 
 **/

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

	Dir();
	Dir(const boost::filesystem::path& path);

	~Dir(void);
	
	static bool isPath(const boost::filesystem::path& path);
	
	const std::string pwd() const;
	
	void cd(const boost::filesystem::path& path);
	void cd(const boost::filesystem::path& path,const DirException& e);

	bool create(int option = NONE);
	bool create(const boost::filesystem::path& path,int option = NONE);
	bool remove() const;
	bool remove(const boost::filesystem::path& path) const;
	boost::uintmax_t remove_all() const;
	boost::uintmax_t remove_all(const boost::filesystem::path& path) const;

	static const char* test();

	void setErrorShow(bool errorShow);

};

}