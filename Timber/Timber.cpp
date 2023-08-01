#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

void HandleInput();
void Update();
void Render();
void InitializeSprites();
void InitializeText();
void InitializeShapes();
void UpdateBee(float);
void UpdateClouds(float);
void UpdateBranches(float);
void InitializeBranches(int);

const Vector2f resolution(1920, 1080);
const Vector2f initSpawnPosition(-2000, -2000);

const int numBranches = 6;

enum class Side { LEFT, RIGHT, NONE };

VideoMode vm(1920, 1080);
RenderWindow gameWindow(vm, "Timber!!", Style::Fullscreen);

Font gameFont;

Clock gameClock;

Texture backgroundTexture;
Texture treeTexture;
Texture beeTexture;
Texture cloudTexture;
Texture branchTexture;

Sprite backgroundSprite;
Sprite treeSprite;
Sprite beeSprite;
Sprite cloud1Sprite;
Sprite cloud2Sprite;
Sprite cloud3Sprite;
Sprite branches[numBranches];

bool beeActive = false;
bool cloud1Active = false;
bool cloud2Active = false;
bool cloud3Active = false;

bool gamePaused = true;

float beeSpeed = 0.0f;
float cloud1Speed = 0.0f;
float cloud2Speed = 0.0f;
float cloud3Speed = 0.0f;
float timeBarStartWidth = 400.0f;
float timeBarHeight = 80.0f;
float timeRemaining = 6.0f;
float timeBarWitdhPerSecond = timeBarStartWidth / timeRemaining;

Text gameTitleText;
Text startGameText;
Text scoreText;

string scoreString;

int score;
int branchSeed;

RectangleShape timeBar;

Time gameTimeTotal;

Side branchPosition[numBranches];

int main()
{
	gameFont.loadFromFile("Fonts/KOMIKAP.ttf");

	InitializeSprites();
	InitializeText();
	InitializeShapes();

	InitializeBranches(1);
	InitializeBranches(2);
	InitializeBranches(3);
	InitializeBranches(4);
	InitializeBranches(5);


	while (gameWindow.isOpen())
	{
		HandleInput();
		Update();
		Render();
	}
	return 0;
}

void HandleInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		gameWindow.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		gamePaused = false;

		score = 0;
		timeRemaining = 6;
	}
}

void Update()
{
	float deltaTime = gameClock.restart().asSeconds();

	if (!gamePaused)
	{
		timeRemaining -= deltaTime;
		timeBar.setSize(Vector2f(timeBarWitdhPerSecond * timeRemaining, timeBarHeight));

		if (timeRemaining <= 0.0f)
		{
			gamePaused = true;

			gameTitleText.setString("Out of time!");
			gameTitleText.setOrigin(gameTitleText.getLocalBounds().width / 2, gameTitleText.getLocalBounds().height / 2);
			gameTitleText.setPosition(resolution.x / 2, 300);
		}

		UpdateBee(deltaTime);
		UpdateClouds(deltaTime);
		UpdateBranches(deltaTime);
		

		scoreString = "Score: " + to_string(score);
		
	}
}

void Render()
{
	gameWindow.clear();

	gameWindow.draw(backgroundSprite);

	gameWindow.draw(cloud1Sprite);
	gameWindow.draw(cloud2Sprite);
	gameWindow.draw(cloud3Sprite);

	gameWindow.draw(treeSprite);
	gameWindow.draw(beeSprite);

	if (gamePaused)
	{
		gameWindow.draw(gameTitleText);
		gameWindow.draw(startGameText);
	}
	else
	{
		for (int i = 0; i < numBranches; i++)
		{
			gameWindow.draw(branches[i]);
		}

		gameWindow.draw(scoreText);
		gameWindow.draw(timeBar);
	}

	gameWindow.display();
}

void InitializeSprites()
{
	// initialize the background
	backgroundTexture.loadFromFile("Graphics/background.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);

	//initialize the tree
	treeTexture.loadFromFile("Graphics/tree.png");
	treeSprite.setTexture(treeTexture);
	treeSprite.setPosition(810, 0);

	// initialize the bee
	beeTexture.loadFromFile("Graphics/bee.png");
	beeSprite.setTexture(beeTexture);
	beeSprite.setPosition(0, 640);

	// initialize the clouds
	cloudTexture.loadFromFile("Graphics/cloud.png");
	cloud1Sprite.setTexture(cloudTexture);
	cloud2Sprite.setTexture(cloudTexture);
	cloud3Sprite.setTexture(cloudTexture);

	cloud1Sprite.setPosition(0, 0);
	cloud2Sprite.setPosition(0, 250);
	cloud3Sprite.setPosition(0, 500);

	// initialize the branches
	branchTexture.loadFromFile("Graphics/branch.png");

	for (int i = 0; i < numBranches; i++)
	{
		// set texture and position of the sprite
		branches[i].setTexture(branchTexture);
		branches[i].setPosition(initSpawnPosition);

		// set the origin to the center of the sprite
		FloatRect bounds = branches[i].getLocalBounds();
		branches[i].setOrigin(bounds.width / 2, bounds.height / 2);
	}
}

void InitializeText()
{
	// initalize game title text
	gameTitleText.setFont(gameFont);
	gameTitleText.setString("Timber!!");
	gameTitleText.setCharacterSize(90);
	gameTitleText.setOrigin(gameTitleText.getLocalBounds().width / 2, gameTitleText.getLocalBounds().height / 2);
	gameTitleText.setPosition(960, 250);

	// initialize the start game message
	startGameText.setFont(gameFont);
	startGameText.setString("Press return to continue...");
	startGameText.setCharacterSize(50);
	startGameText.setOrigin(startGameText.getLocalBounds().width / 2, gameTitleText.getLocalBounds().height / 2);
	startGameText.setPosition(960, 500);

	// initialize score text
	scoreText.setFont(gameFont);
	scoreText.setString("Score: " + to_string(score));
	scoreText.setCharacterSize(70);
	scoreText.setPosition(30, 30);
}

void InitializeShapes()
{
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((resolution.x / 2) - timeBarStartWidth / 2, 980);
}

void UpdateBee(float deltaTime)
{
	if (!beeActive)
	{
		beeActive = true;

		srand(static_cast<int>(time(0)));
		beeSpeed = static_cast<float>((rand() % 200) + 200);

		srand(static_cast<int>(time(0) * 10));
		float height = static_cast<float>((rand() % 1350) + 500);
		beeSprite.setPosition(2000, height);
	}
	else
	{
		Vector2f currentPosition = beeSprite.getPosition();
		currentPosition.x -= beeSpeed * deltaTime;

		beeSprite.setPosition(currentPosition);

		if (currentPosition.x < -100)
		{
			beeActive = false;
		}
	}
}

void UpdateClouds(float deltaTime)
{
	if (!cloud1Active)
	{
		cloud1Active = true;

		srand(static_cast<int>(time(0)) * 10);
		cloud1Speed = static_cast<float>((rand() % 200));

		srand(static_cast<int>(time(0) * 10));
		float height = static_cast<float>((rand() % 150));
		cloud1Sprite.setPosition(-200, height);
	}
	else
	{
		Vector2f currentPosition = cloud1Sprite.getPosition();
		currentPosition.x += cloud1Speed * deltaTime;

		cloud1Sprite.setPosition(currentPosition);

		if (currentPosition.x > 1920)
		{
			cloud1Active = false;
		}
	}

	if (!cloud2Active)
	{
		cloud2Active = true;

		srand(static_cast<int>(time(0)) * 20);
		cloud2Speed = static_cast<float>((rand() % 200));

		srand(static_cast<int>(time(0) * 20));
		float height = static_cast<float>((rand() % 300) - 150);
		cloud2Sprite.setPosition(-200, height);
	}
	else
	{
		Vector2f currentPosition = cloud2Sprite.getPosition();
		currentPosition.x += cloud2Speed * deltaTime;

		cloud2Sprite.setPosition(currentPosition);

		if (currentPosition.x > 1920)
		{
			cloud2Active = false;
		}
	}

	if (!cloud3Active)
	{
		cloud3Active = true;

		srand(static_cast<int>(time(0)) * 30);
		cloud3Speed = static_cast<float>((rand() % 200));

		srand(static_cast<int>(time(0) * 30));
		float height = static_cast<float>((rand() % 450) - 150);
		cloud3Sprite.setPosition(-200.0f, height);
	}
	else
	{
		Vector2f currentPosition = cloud2Sprite.getPosition();
		currentPosition.x += cloud3Speed * deltaTime;

		cloud3Sprite.setPosition(currentPosition);

		if (currentPosition.x > 1920)
		{
			cloud3Active = false;
		}
	}
}

void UpdateBranches(float deltaTime)
{
	for (int i = 0; i < numBranches; i++)
	{
		float height = i * 150.0f;

		if (branchPosition[i] == Side::LEFT)
		{
			branches[i].setPosition(610, height);
			branches[i].setRotation(180);
		}
		else if (branchPosition[i] == Side::RIGHT)
		{
			branches[i].setPosition(1330, height);
			branches[i].setRotation(0);
		}
		else
		{
			branches[i].setPosition(initSpawnPosition);
		}
	}
}

void InitializeBranches(int seed)
{
	for (int i = numBranches; i > 0; i--)
	{
		branchPosition[i] = branchPosition[i - 1];
	}

	srand(static_cast<int>(time(0)) + seed);
	int r = (rand() % 5);

	switch (r) 
	{
	case 0:
		branchPosition[0] = Side::LEFT;
		break;
	case 1:
		branchPosition[0] = Side::RIGHT;
		break;
	default:
		branchPosition[0] = Side::NONE;
		break;
	}
	
}