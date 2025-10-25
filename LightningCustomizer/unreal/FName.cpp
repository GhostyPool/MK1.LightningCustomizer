#include "FName.h"
#include "..\SDK.h"

FName::FName(const char* Name, EFindName FindType, int formal)
{
	static uintptr_t pat = MK12HOOKSDK::GetPattern("48 89 5C 24 08 57 48 83 EC 30 48 89 54 24 20 41 8B F8 4C 8B CA", 0);
	if (pat)
		((void(__fastcall*)(FName*, const char*, EFindName, int))pat)(this, Name, FindType, formal);
}

FName::FName(const wchar_t* Name, EFindName FindType, int formal)
{
	static uintptr_t pat = MK12HOOKSDK::GetPattern("48 89 5C 24 08 57 48 83 EC 30 48 8B D9 48 89 54 24 20 33 C9", 0);
	if (pat)
		((void(__fastcall*)(FName*, const wchar_t*, EFindName, int))pat)(this, Name, FindType, formal);
}
