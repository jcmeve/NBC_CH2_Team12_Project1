#include "SaveManager.h"
#include<fstream>
#include<sstream>
#include <codecvt>
#include <locale>
SaveManager::SaveManager() {
}

SaveManager::~SaveManager() {
}

bool SaveManager::LoadAscii(const std::wstring& name, std::wstring& buf) {
	std::wifstream file(L"Assets\\Ascii\\" + name + L".txt");
	if (file.is_open()) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
		std::wstringstream wss;
		wss << file.rdbuf();
		buf.assign(wss.str());
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool SaveManager::LoadItems(const std::wstring& name, std::vector<std::vector<std::wstring>>& out) {
	out.clear();
	std::wifstream file(L"Assets\\Item\\" + name);
	if (file.is_open()) {
		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
		std::wstring line;

		while (std::getline(file, line)) {
			if (!line.empty() && (unsigned short)line[0] == 65279) { //65001 BOM 처리
				line.erase(0, 1);
			}
			out.push_back(std::vector<std::wstring>());
			std::wstringstream wss(line);
			std::wstring temp;
			while (std::getline(wss, temp, L',')) {

				out[out.size() - 1].push_back(temp);
			}
		}
		return true;
	}
	return false;
}

bool SaveManager::SaveGame(Character* player) {
	return false;
}

bool SaveManager::LoadGame(Character* player) {
	return false;
}
