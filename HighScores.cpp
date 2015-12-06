#include "Windows.h"
#include "baseTypes.h"
#include "stdio.h"
#include "GameTime.h"
#include "HighScores.h"

HighScoresC* HighScoresC::sInstance = NULL;

HighScoresC* HighScoresC::CreateInstance()
{
	if (sInstance != NULL) { return sInstance; }
	else { sInstance = new HighScoresC(); }
	return sInstance;
}

void HighScoresC::init()
{
	for (uint32_t i = 0; i < MAX_HIGH_SCORES; i++)
	{
		mHighScores[i] = 0;
	}
}

void HighScoresC::loadHighScores()
{
	FILE* highScoreFile = NULL;
	fopen_s(&highScoreFile, "highScores.txt", "r");

	for (uint32_t i = 0; i < MAX_HIGH_SCORES; i++)
	{
		fscanf(highScoreFile, "%d\n", &mHighScores[i]);
	}

	fclose(highScoreFile);
}

void HighScoresC::storeHighScores()
{
	FILE* highScoreFile = NULL;
	fopen_s(&highScoreFile, "highScores.txt", "w");

	for (uint32_t i = 0; i < MAX_HIGH_SCORES; i++)
	{
		fprintf(highScoreFile, "%d\n", mHighScores[i]);
	}

	fclose(highScoreFile);
}

bool HighScoresC::determineIfHighScore()
{
	loadHighScores();

	//bool8_t newHighScoreFound = false;
	int32_t newHighScoreIndex = -1;

	DWORD currentScore = GameTimeC::GetInstance()->getCurrentTime();
	for (int32_t i = MAX_HIGH_SCORES - 1; i >= 0; i--)
	{
		if (currentScore > mHighScores[i])
		{
			newHighScoreIndex = i;
		}
		else
		{
			// This element is not a high score against the current index, no need to check the rest
			break;
		}
	}

	if (newHighScoreIndex != -1)
	{
		// new high score found from previous index, store it
		addNewHighScoreToTable(currentScore, newHighScoreIndex);
		storeHighScores();
		return true;
	}

	return false;
}

// Add a new high score at the tableIndex, shifting lower scores down or out of the table
void HighScoresC::addNewHighScoreToTable(DWORD newScoreToAdd, int32_t tableIndex)
{
	for (int32_t i = MAX_HIGH_SCORES - 1; i > tableIndex; i--)
	{
		// Shift the lower scores down the table
		mHighScores[i] = mHighScores[i-1];
	}
	// Add the new high score
	mHighScores[tableIndex] = newScoreToAdd;
}