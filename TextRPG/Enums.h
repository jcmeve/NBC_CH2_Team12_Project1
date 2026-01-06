#pragma once
#include<string>
#include<map>
enum class STATS{
    HP, ATK, DEF
};
static std::map<std::wstring, STATS> mapSTATS = {
    {L"HP", STATS::HP},
    {L"ATK", STATS::ATK},
    {L"DEF", STATS::DEF},
};
