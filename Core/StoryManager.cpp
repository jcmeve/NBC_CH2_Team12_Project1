#include "StoryManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <codecvt>
#include "QTE.h"
#include "GameManager.h"
#include "DisplayManager.h"
#include "SaveManager.h"

using namespace std;

StoryManager::StoryManager()
{

}

StoryManager::~StoryManager()
{

}

void StoryManager::Tick(float deltaTime)
{
	if (!isPlaying)
	{
		return;
	}
	if (!cachedAsciiArt.empty())
	{
		GM::GetDisplay().DrawAscii(cachedAsciiArt, 0, 0);
	}

	// QTE 진행중
	if (isWatingQTE)
	{
		if (activeQTE && activeQTE->IsFinished())
		{
			bool isSuccess = !activeQTE->IsFailed(); // 성공 여부

			activeQTE = nullptr;
			isWatingQTE = false;

			if (isSuccess)
			{
				currentIndex++; // 성공 대사 출력
				shouldSkipNextLine = true; // 실패 대사 스킵 예약
				PlayLine(currentIndex);
			}
			else
			{
				currentIndex += 2; // 실패 대사 출력
				shouldSkipNextLine = false; // 스킵= 없이 정상 진행
				PlayLine(currentIndex);
			}
		}
		return;
	}

	// 자동 진행 (Duration > 0)
	if (isAutoNext)
	{
		lineTimer -= deltaTime;
		if (lineTimer <= 0.0f)
		{
			NextLine();
		}
	}

	// 수동 진행 (Spacebar)
	else
	{
		if (GM::GetInput().IsKeyDown(VK_SPACE))
		{
			NextLine();
		}
	}
}

void StoryManager::PlayLine(int index)
{
	const StoryLine& line = currentChapterLines[index];

	// 아스키아트 변경
	if (!line.asciiFileName.empty() && line.asciiFileName != lastAsciiFile)
	{
		lastAsciiFile = line.asciiFileName;
		if (!GM::GetSave().LoadAscii(lastAsciiFile, cachedAsciiArt))
		{
			GM::GetLogger().Log(L"이미지 로드 실패: " + lastAsciiFile);
			cachedAsciiArt = L"";
		}
	}

	// QTE 이벤트
	if (line.speaker == L"QTE")
	{
		isWatingQTE = true;

		wstring finalMsg = FormatText(line.text, line.duration);
		GM::GetLogger().Log(finalMsg);

		activeQTE = GM::CreateActor<QTE>(L"Story QTE");
		activeQTE->Init(targetPlayer, line.duration);
	}
	else
	{
		wstring logMsg;
		if (line.speaker == L"Narration")
		{
			logMsg = line.text;
		}
		else
		{
			logMsg = L"[" + line.speaker + L"]" + line.text;
		}

		GM::GetLogger().Log(logMsg);
	}

	if (line.duration > 0.0f)
	{
		isAutoNext = true;
		lineTimer = line.duration;
	}
	else
	{
		isAutoNext = false; // 스페이스바 대기
	}
}


void StoryManager::LoadChapter(wstring csvFileName)
{
	currentChapterLines.clear();
	ParseCSV(csvFileName);

	currentIndex = -1;
	isPlaying = true;
	isWatingQTE = false;
	lastAsciiFile = L"";
	cachedAsciiArt = L"";

	NextLine();
}

void StoryManager::NextLine()
{
	if (shouldSkipNextLine)
	{
		currentIndex++;
		shouldSkipNextLine = false;
	}

	currentIndex++;

	if (currentIndex >= currentChapterLines.size())
	{
		isPlaying = false; // 현재 챕터 종료

		//GM::GetLogger().Log(L"--------------------------------");
		//GM::GetLogger().Log(L"[SPACE] 계속");

		return;
	}
	PlayLine(currentIndex);
}

std::wstring StoryManager::FormatText(wstring text, float timeVal)
{
	wstring token = L"{time}";
	size_t pos = text.find(token);

	if (pos != wstring::npos)
	{
		text.replace(pos, token.length(), to_wstring((int)timeVal));
	}

	return text;
}

bool StoryManager::IsStoryFinished() const
{
	return !isPlaying;
}

void StoryManager::SetPlayer(Character* player)
{
	targetPlayer = player;
}

// ==========================================================
// CSV 파싱 구현
// ==========================================================


void StoryManager::ParseCSV(std::wstring filePath)
{
	std::wstring fullPath = L"Assets\\Story\\" + filePath + L".csv";
	wstring path(fullPath.begin(), fullPath.end());
	ifstream file(path);

	if (!file.is_open())
	{
		GM::GetLogger().Log(L"파일을 찾을 수 없습니다: " + filePath);
		return;
	}

	string line;
	bool isFirstLine = true;


	while (getline(file, line))
	{
		if (line.empty()) continue;

		// UTF-8 BOM(Byte Order Mark) 제거
		if (isFirstLine)
		{
			if (line.size() >= 3 &&
				(unsigned char)line[0] == 0xEF &&
				(unsigned char)line[1] == 0xBB &&
				(unsigned char)line[2] == 0xBF)
			{
				line = line.substr(3);
			}
			isFirstLine = false;
		}

		if (!line.empty() && line.back() == '\r') {
			line.pop_back();
		}
		wstring wLine = StringToWString(line);
		vector<wstring> parts = Split(wLine, L'|');

		if (parts.size() >= 5)
		{
			StoryLine sLine;
			try {
				sLine.id = stoi(parts[0]);
			}
			catch (...) {
				continue;
			}

			sLine.asciiFileName = parts[1];
			sLine.speaker = parts[2];
			sLine.text = parts[3];
			sLine.duration = stof(parts[4]);

			currentChapterLines.push_back(sLine);
		}
	}

	file.close();
}

std::vector<std::wstring> StoryManager::Split(const std::wstring& str, wchar_t delimiter)
{
	std::vector<std::wstring> tokens;
	std::wstring token;
	std::wstringstream ss(str);
	while (std::getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

std::wstring StoryManager::StringToWString(const std::string& str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
	std::wstring wstr;
	if (len > 0)
	{
		wstr.resize(len);
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], len);
	}
	return wstr;
}
