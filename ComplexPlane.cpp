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
void ComplexPlane::draw(RenderTarget& target, RenderStates states)const
{
	target.draw(m_vArray);

}
void ComplexPlane::zoomin()
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
	istringstream displayStrm;
	//add title
	displayStrm.str() = "Mandelbolt Set\n";
	//add center
	displayStrm.str() 

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
				iterationsToRGB(currentIter, m_vArray[j + i * m_pixel_size.x].color.r, m_vArray[j + i * m_pixel_size.x].color.g, m_vArray[j + i * m_pixel_size.x].color.b);
			}
		}
	}
	m_state = State::DISPLAYING;
}
int ComplexPlane::countIterations(Vector2f coord)
{
	return abs(coord.x)+abs(coord.y);
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	Color currentColor = { r, g, b };
	if (count > MAX_ITER)
	{
		currentColor = Color::Black;
	}
	else
	{
		//increments by 12
		Color currentColor = { r, g, b };
		if (count < 12) currentColor = Color::Magenta;
		else if (count < 24) currentColor = Color::Cyan;
		else if (count < 46) currentColor = Color::Yellow;
		else if (count < 58) currentColor = Color::Red;
		else currentColor = Color::Blue;
	}
	r = currentColor.r;
	g = currentColor.g;
	b = currentColor.b;
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	float x = ((mousePixel.x - 0) / (float)(m_pixel_size.x - 0)) * (m_plane_size.y -  m_plane_size.x) + m_plane_center.y;
    float y = ((mousePixel.y - m_pixel_size.y) / (float)(0 - m_pixel_size.y)) * (m_plane_size.y - m_plane_size.x) + m_plane_center.y;

	return { x, y };

}



