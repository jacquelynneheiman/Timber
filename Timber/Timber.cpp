#include <SFML/Graphics.hpp>

using namespace sf;

void HandleInput();
void Update();
void Render();
void InitializeSprites();

VideoMode vm(1920, 1080);
RenderWindow gameWindow(vm, "Timber!!", Style::Fullscreen);

Font gameFont;

Clock gameClock;

Texture backgroundTexture;
Texture treeTexture;
Texture beeTexture;
Texture cloudTexture;

Sprite backgroundSprite;
Sprite treeSprite;
Sprite beeSprite;
Sprite cloud1Sprite;
Sprite cloud2Sprite;
Sprite cloud3Sprite;

bool beeActive = false;
bool cloud1Active = false;
bool cloud2Active = false;
bool cloud3Active = false;

bool gamePaused = true;

float beeSpeed = 0.0f;
float cloud1Speed = 0.0f;
float cloud2Speed = 0.0f;
float cloud3Speed = 0.0f;

int main()
{
	gameFont.loadFromFile("Fonts/KOMIKAP.ttf");

	InitializeSprites();

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
	}
}

void Update()
{
	float deltaTime = gameClock.restart().asSeconds();

	if (!gamePaused)
	{
		// update the bee
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

		// update the clouds
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
			cloud3Sprite.setPosition(-200, height);
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
		Text pausedGameText("Press Return to Begin", gameFont);
		pausedGameText.setCharacterSize(75);
		pausedGameText.setPosition(600, 300);

		gameWindow.draw(pausedGameText);
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
}