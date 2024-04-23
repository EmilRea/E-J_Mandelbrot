#include "ComplexPlane.h"

int main() 
{
	const int PIXEL_WIDTH = VideoMode::getDesktopMode().width;
	const int PIXEL_HEIGHT = VideoMode::getDesktopMode().height;

	Font displayFont;
	Text displayText;
	displayFont.loadFromFile("./fonts/displayFont.ttf");
	displayText.setFont(displayFont);
	displayText.setPosition(10.f, 10.f);
	displayText.setColor(Color::White);

	VideoMode vm(PIXEL_WIDTH, PIXEL_HEIGHT);

	RenderWindow window(vm, "Mandelbrot", Style::Default);

	ComplexPlane complexPlane(PIXEL_WIDTH, PIXEL_HEIGHT);

	while (window.isOpen())
	{
		// handle input
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
					Vector2i mousePixel{ event.mouseButton.x, event.mouseButton.y };
                    cout << "Clicked at complex coordinate: (" << mousePixel.x << ", " << mousePixel.y << ")" << endl;
                }
            }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		// update scene
		complexPlane.updateRender();

		// draw scene
		window.clear();

		complexPlane.draw();

		window.display();
	}
}
