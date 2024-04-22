#include "ComplexPlane.h"

int main() 
{
	const int PIXEL_WIDTH = VideoMode::getDesktopMode().width;
	const int PIXEL_HEIGHT = VideoMode::getDesktopMode().height;

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
					Vector2f complexCoord = complexPlane.mapPixelToCoords(mousePixel);
                    cout << "Clicked at complex coordinate: (" << complexCoord.x << ", " << complexCoord.y << ")" << endl;
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

		window.display();
	}
}
