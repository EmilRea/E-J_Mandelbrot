#include "ComplexPlane.h"

int main() 
{
	const int PIXEL_WIDTH = VideoMode::getDesktopMode().width / 2;
	const int PIXEL_HEIGHT = VideoMode::getDesktopMode().height / 2;

	Font displayFont;
	Text displayText;
	displayFont.loadFromFile("./fonts/displayFont.ttf");
	displayText.setFont(displayFont);

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
				Vector2i mousePixel{ event.mouseButton.x, event.mouseButton.y };
				cout << "Clicked at pixel coordinate: (" << mousePixel.x << ", " << mousePixel.y << ")" << endl;

                if (event.mouseButton.button == Mouse::Left)
                {                
					complexPlane.setCenter(mousePixel);
					complexPlane.zoomIn();
				}
				if (event.mouseButton.button == Mouse::Right)
				{
					complexPlane.setCenter(mousePixel);
					complexPlane.zoomOut();
				}
            }
			else if (event.type == Event::MouseMoved)
			{
				Vector2i mousePixel{ event.mouseMove.x, event.mouseMove.y };
				complexPlane.setMouseLocation(mousePixel);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		// update scene
		complexPlane.updateRender();
		complexPlane.loadText(displayText);

		// draw scene
		window.clear();
		window.draw(complexPlane);
		window.draw(displayText);
		window.display();

	}

	return 0;
}
