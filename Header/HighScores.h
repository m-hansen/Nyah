#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define MAX_HIGH_SCORES 10
#define MAX_NAME_LEN 3

class HighScoresC
{
public:
	static HighScoresC* CreateInstance();
	static HighScoresC* GetInstance() { return sInstance; };
	~HighScoresC() = default;
	void init();
	void destory();
	void loadHighScores();
	void storeHighScores();
	bool determineIfHighScore();
	void addNewHighScoreToTable(uint32_t newScore);
	HighScoreEntry* getHighScores() { return mHighScores; };
	int32_t getMaxNumberOfHighScores() { return MAX_HIGH_SCORES; }
	void promptForPlayerName();
	const std::string& getPlayerName();
	int32_t getNewHighScoreIndex() { return mNewHighScoreIndex; }
private:
	static HighScoresC* sInstance;
	HighScoresC() {};
	HighScoreEntry mHighScores[MAX_HIGH_SCORES];
	std::string mPlayerName;
	int32_t mNewHighScoreIndex;
};