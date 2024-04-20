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
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		// update scene
		
		// draw scene
		window.clear();

		window.display();
	}
}
