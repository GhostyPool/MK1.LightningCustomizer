#pragma once

enum EFindName
{
	FNAME_Find,
	FNAME_Add,
	FNAME_Replace,
};

class FName {
public:
	int Index;
	int Number;

	FName(const char* Name, EFindName FindType, int formal);
	FName(const wchar_t* Name, EFindName FindType, int formal);

	bool operator==(const FName& Other) const { return Index == Other.Index && Number == Other.Number; }
};
