#include "ComplexPlane.h"

int main() 
{

	VideoMode vm(1920, 1080);

	RenderWindow window(vm, "Mandelbrot", Style::Default);

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
                    Vector2f complexCoord = complexPlane.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
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
