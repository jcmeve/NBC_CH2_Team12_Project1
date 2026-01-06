#pragma once
#include <string>
#include <vector>

class Character;
class QTE;

struct StoryLine
{
	int id;
	std::wstring asciiFileName;
	std::wstring speaker;
	std::wstring text;
	float duration;
};

class StoryManager
{
private:
	StoryManager();
	~StoryManager();
	StoryManager& operator=(const StoryManager& other) = delete;
	StoryManager(const StoryManager& other) = delete;
	StoryManager& operator=(const StoryManager&& other) = delete;
	StoryManager(const StoryManager&& other) = delete;
	friend class GameManager;

private:
	std::vector<StoryLine> currentChapterLines;
	int currentIndex = -1;

	bool isPlaying = false;
	float lineTimer = 0.0f;
	bool isAutoNext = false; // duration > 0 이면 true

	bool isWatingQTE = false;
	bool shouldSkipNextLine = false; // QTE 성공/실패 시 라인 건너뛰기
	QTE* activeQTE = nullptr;
	Character* targetPlayer = nullptr; // QTE 타겟

	std::wstring lastAsciiFile;
	std::wstring cachedAsciiArt;

public:
	bool IsStoryFinished() const;
	void LoadChapter(std::wstring csvFileName);

	void Tick(float deltaTime);

	void SetPlayer(Character* player);

private:
	void PlayLine(int index);
	void NextLine();
	std::wstring FormatText(std::wstring text, float timeVal);

	void ParseCSV(std::wstring filePath);
	std::vector<std::wstring> Split(const std::wstring& str, wchar_t delimiter);
	std::wstring StringToWString(const std::string& str);
};

