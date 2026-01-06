
#include <Windows.h>
#include <mmsystem.h>
#include "SoundManager.h"

#pragma comment(lib,"winmm.lib")
SoundManager::SoundManager() {
	//LoadAudio(L"test");
	//SetVolume(L"test", 100);
	//PlayAudio(L"test");
}

SoundManager::~SoundManager() {
	for (std::wstring name : audioFiles) {
		StopAudio(name);
		std::wstring cmd = L"close " + name;
		mciSendStringW(cmd.c_str(), nullptr, 0, nullptr);
	}
	audioFiles.clear();
}

void SoundManager::LoadAudio(const std::wstring& name) {
	CloseAudio(name);
	std::wstring cmd = L"open \"Assets\\Audio\\" + name + L".wav\" type mpegvideo alias " + name;
	mciSendStringW(cmd.c_str(), nullptr, 0, nullptr);
	audioFiles.insert(name);
}

void SoundManager::PlayAudio(const std::wstring& name, bool loop) {
	std::wstring cmd = L"play " + name + L" from 0 ";
	if (loop)cmd += L" repeat";
	mciSendStringW(cmd.c_str(), nullptr, 0, nullptr);
}

void SoundManager::StopAudio(const std::wstring& name) {
	std::wstring cmd = L"stop " + name;
	mciSendStringW(cmd.c_str(), nullptr, 0, nullptr);
}

void SoundManager::CloseAudio(const std::wstring& name) {
	std::wstring cmd = L"close " + name;
	mciSendStringW(cmd.c_str(), nullptr, 0, nullptr);
	audioFiles.erase(name);
}

void SoundManager::SetVolume(const std::wstring& name, int volume) {
	std::wstring cmd = L"setaudio " + name + L" volume to " + std::to_wstring(volume);
	mciSendStringW(cmd.c_str(), nullptr, 0, nullptr);
}
