#pragma once

#ifdef NSTATIC
#	define PRO_EXPORTS __declspec(dllexport)
#else
#	define PRO_EXPORTS 
#endif

//#ifndef PRO_C_EXTERN
//#	define PRO_C_EXTERN extern "C"
//#endif

#ifdef NSTATIC
#	define PRO_C_EXTERN extern "C" __declspec(dllexport)
#else
#	define PRO_C_EXTERN extern "C"
//#else
//#	define PRO_C_EXTERN 
#endif

#ifdef NSTATIC
#define BOOST_ALL_DYN_LINK
#endif

#include<string>
#include<time.h>
#include<vector>
#include<regex>

using std::vector;
using std::string;

/*****************************
 *  warning
 */

// warning C4251 class 'std::basic_string<_Elem,_Traits,_Alloc>' は __export キーワードを使って class 'pro::Dir' にエクスポートしてください。
template class PRO_EXPORTS std::basic_string<char, std::char_traits<char>, std::allocator<char> >;

// warning C4251 class 'std::vector<_Ty>' は __export キーワードを使って class 'pro::Timer' にエクスポートしてください。
// http://support.microsoft.com/default.aspx?scid=kb;ja-jp;168958
// Timer.h
template class PRO_EXPORTS std::vector<clock_t>;
template class PRO_EXPORTS std::vector<std::string>; 
template class PRO_EXPORTS std::vector<int>; 



