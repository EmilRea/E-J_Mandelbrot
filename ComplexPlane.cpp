#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = pixelHeight / pixelWidth;
	m_plane_center = { 0, 0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray.resize(pixelWidth * pixelHeight);
	m_vArray.setPrimitiveType(Points);
}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);

}
void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float zoomX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float zoomY = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { zoomX, zoomY };
	m_state = State::CALCULATING;
}
void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float zoomX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float zoomY = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { zoomX, zoomY };
	m_state = State::CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = State::CALCULATING;
}
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}
void ComplexPlane::loadText(Text& text)
{
	ostringstream displayStrm;
	//add title
	displayStrm << "Mandelbolt Set\n";
	//add center
	displayStrm << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")" << endl;
	//add cursor
	displayStrm << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << endl;
	// instructions
	displayStrm << "Left-click to Zoom in" << endl;
	displayStrm << "Right-click to Zoom out" << endl;

	text.setString(displayStrm.str());
}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
    {
		for (int i = 0; i < m_pixel_size.y; i++)
		{
			for (int j = 0; j < m_pixel_size.x; j++)
			{
				m_vArray[j + i * m_pixel_size.x].position = { (float)j,(float)i };
				size_t currentIter = countIterations(mapPixelToCoords({ j, i }));

				Uint8 r, g, b;
				iterationsToRGB(currentIter, r, g, b);
				m_vArray[j + i * m_pixel_size.x].color = { r, g, b };

				//iterationsToRGB(currentIter, m_vArray[j + i * m_pixel_size.x].color.r, m_vArray[j + i * m_pixel_size.x].color.g, m_vArray[j + i * m_pixel_size.x].color.b);
			}
		}
	}
	m_state = State::DISPLAYING;
}
int ComplexPlane::countIterations(Vector2f coord)
{
	return abs(coord.x) + abs(coord.y);
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	//Color currentColor = { r, g, b };
	if (count > MAX_ITER)
	{
		r = g = b = 0; // Black


		//currentColor = Color::Black;
	}
	else
	{
		float hue = static_cast<float>(count % 256) / 255.0f;
		float saturation = 1.0f;
		float lightness = 0.5f;

		float c = (1.0f - abs(2.0f * lightness - 1.0f)) * saturation;
		float x = c * (1.0f - abs(fmod(hue * 6.0f, 2.0f) - 1.0f));
		float m = lightness - c / 2.0f;

		float red = 0, green = 0, blue = 0;

		if (hue >= 0 && hue < 1.0f / 6.0f)
		{
			red = c;
			green = x;
		}
		else if (hue >= 1.0f / 6.0f && hue < 2.0f / 6.0f)
		{
			red = x;
			green = c;
		}
		else if (hue >= 2.0f / 6.0f && hue < 3.0f / 6.0f)
		{
			green = c;
			blue = x;
		}
		else if (hue >= 3.0f / 6.0f && hue < 4.0f / 6.0f)
		{
			green = x;
			blue = c;
		}
		else if (hue >= 4.0f / 6.0f && hue < 5.0f / 6.0f)
		{
			red = x;
			blue = c;
		}
		else
		{
			red = c;
			blue = x;
		}

		r = static_cast<Uint8>((red + m) * 255);
		g = static_cast<Uint8>((green + m) * 255);
		b = static_cast<Uint8>((blue + m) * 255);




		//	//increments by 12
		//	Color currentColor = { r, g, b };
		//	if (count < 12) currentColor = Color::Magenta;
		//	else if (count < 24) currentColor = Color::Cyan;
		//	else if (count < 46) currentColor = Color::Yellow;
		//	else if (count < 58) currentColor = Color::Red;
		//	else currentColor = Color::Blue;
		//}
		//r = currentColor.r;
		//g = currentColor.g;
		//b = currentColor.b;
}
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    float x = ((mousePixel.x - 0) / (float(m_pixel_size.x))) * (m_plane_size.y - m_plane_size.x) + (m_plane_size.x);
    float y = ((mousePixel.y - m_pixel_size.y) / (float(0 - m_pixel_size.y))) * (m_plane_size.y - m_plane_size.x) + (m_plane_size.y);

	return { x, y };

}



