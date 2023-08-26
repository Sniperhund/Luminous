#include "Image.h"

#include <lodepng.h>
#include <assimp/MathFunctions.h>

#include "Utility.h"

Image::Image(int width, int height)
{
    m_pixels = std::vector<unsigned char>(width * height * 4);

    m_width = width;
    m_height = height;
}

void Image::SetPixel(int x, int y, const Vector3& color)
{    
    m_pixels[4 * m_width * y + 4 * x + 0] = (unsigned char)(color.x * 255);
    m_pixels[4 * m_width * y + 4 * x + 1] = (unsigned char)(color.y * 255);
    m_pixels[4 * m_width * y + 4 * x + 2] = (unsigned char)(color.z * 255);
    m_pixels[4 * m_width * y + 4 * x + 3] = 255;
}

void Image::Save(const std::string& filename)
{
    lodepng::encode(filename, m_pixels.data(), m_width, m_height);
}
