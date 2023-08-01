#include <SFML/Graphics.hpp>

using namespace sf;

void HandleInput();
void Update();
void Render();

VideoMode vm(1920, 1080);
RenderWindow gameWindow(vm, "Timber!!", Style::Fullscreen);

Texture backgroundTexture;

Sprite backgroundSprite;

int main()
{
	backgroundTexture.loadFromFile("Graphics/background.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);

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
}

void Update()
{

}

void Render()
{
	gameWindow.clear();

	gameWindow.draw(backgroundSprite);

	gameWindow.display();
}