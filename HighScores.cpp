#include "Windows.h"
#include "baseTypes.h"
#include "stdio.h"
#include "GameTime.h"
#include "InputManager.h"
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
	mNewHighScoreIndex = MAXUINT32;
	mPlayerName = "AAA";
	for (uint32_t i = 0; i < MAX_HIGH_SCORES; i++)
	{
		mHighScores[i].score = 0;
		mHighScores[i].name = "";
	}
}

void HighScoresC::loadHighScores()
{
	std::ifstream highScoreFile;
	highScoreFile.open("highScores.txt");

	if (highScoreFile.is_open())
	{
		std::uint32_t count = 0;
		std::string line = "";

		while (std::getline(highScoreFile, line))
		{
			// Tokenize whitespace
			std::string buffer;
			std::stringstream stream(line);
			std::vector<std::string> tokens;

			while (stream >> buffer)
			{
				tokens.push_back(buffer);
			}

			mHighScores[count].name = tokens[0];
			mHighScores[count].score = atoi(tokens[1].c_str());
			++count;
		}

		highScoreFile.close();
	}

	/*FILE* highScoreFile = NULL;
	fopen_s(&highScoreFile, "highScores.txt", "r");

	for (uint32_t i = 0; i < MAX_HIGH_SCORES; i++)
	{
		std::
		fscanf(highScoreFile, "%s %d\n", mHighScores[i].name.c_str(), &mHighScores[i].score);
	}

	fclose(highScoreFile);*/
}

void HighScoresC::storeHighScores()
{
	FILE* highScoreFile = NULL;
	fopen_s(&highScoreFile, "highScores.txt", "w");

	for (uint32_t i = 0; i < MAX_HIGH_SCORES; i++)
	{
		fprintf(highScoreFile, "%s %d\n", mHighScores[i].name.c_str(), mHighScores[i].score);
	}

	fclose(highScoreFile);
}

bool HighScoresC::determineIfHighScore()
{
	loadHighScores();
	mNewHighScoreIndex = -1;

	uint32_t currentScore = GameTimeC::GetInstance()->getCurrentTime();
	for (int32_t i = MAX_HIGH_SCORES - 1; i >= 0; i--)
	{
		if (currentScore > mHighScores[i].score)
		{
			mNewHighScoreIndex = i;
		}
		else
		{
			// This element is not a high score against the current index, no need to check the rest
			break;
		}
	}

	if (mNewHighScoreIndex != -1)
	{
		// new high score found from previous index, store it
		// promptFormPlayerName(); // TODO prompt for name
		addNewHighScoreToTable(currentScore);
		storeHighScores();
		return true;
	}

	return false;
}

// Add a new high score at the tableIndex, shifting lower scores down or out of the table
void HighScoresC::addNewHighScoreToTable(uint32_t newScoreToAdd)
{
	for (int32_t i = MAX_HIGH_SCORES - 1; i > mNewHighScoreIndex; i--)
	{
		// Shift the lower scores down the table
		mHighScores[i] = mHighScores[i-1];
	}
	// Add the new high score
	mHighScores[mNewHighScoreIndex].score = newScoreToAdd;
	mHighScores[mNewHighScoreIndex].name = mPlayerName;
}

void HighScoresC::promptForPlayerName()
{
	uint32_t currentNameIndex = 0;
	bool8_t waitingForInput = true;

	for (uint32_t i = 0; i < MAX_NAME_LEN; i++)
	{
		// Initialize the player name
		mPlayerName[i] = 'A';
	}
	mPlayerName[MAX_NAME_LEN] = '\0';

	while (waitingForInput)
	{
		InputManagerC* inputManagerInstance = InputManagerC::GetInstance();

		if (inputManagerInstance->GetUpButton())
		{
			if (mPlayerName[currentNameIndex] < 'Z')
			{
				mPlayerName[currentNameIndex]++;
			}
		}

		if (inputManagerInstance->GetDownButton())
		{
			if (mPlayerName[currentNameIndex] > 'A')
			{
				mPlayerName[currentNameIndex]--;
			}
		}

		if (inputManagerInstance->GetClockwiseRotationButton())
		{
			if (currentNameIndex != MAX_NAME_LEN - 1)
				currentNameIndex++;
		}

		if (inputManagerInstance->GetClockwiseRotationButton())
		{
			if (currentNameIndex != 0)
				currentNameIndex--;
		}

		if (inputManagerInstance->GetStartButton())
		{
			waitingForInput = false;
		}
	}
}

const std::string& HighScoresC::getPlayerName()
{
	return mPlayerName;
}