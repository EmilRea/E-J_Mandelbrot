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
	m_zoomCount--;
}
void ComplexPlane::zoomOut()
{
	m_zoomCount++;
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{

}
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{

}
void ComplexPlane::loadText(Text& text)
{

}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
    {
		for (int i = 0; i < m_vArray.getVertexCount(); i++)
		{
			for (int j = 0; j < m_vArray.getVertexCount(); j++)
			{
				m_vArray[j + i * pixelWidth].position = { (float)j,(float)i };


			}
		}
    }
}

}
int ComplexPlane::countIterations(Vector2f coord)
{
	return 0;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	float x = ((mousePixel.x - 0) / (float)m_pixel_size.x) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0f);
    float y = ((mousePixel.y - m_pixel_size.y) / (float)(0 - m_pixel_size.y)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0f);

    return { x, y };

}



