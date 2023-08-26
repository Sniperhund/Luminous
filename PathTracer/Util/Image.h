#pragma once
#include <string>
#include <vector>

#include "../Math/Vector3.h"

class Image
{
public:
    Image(int width, int height);

    void SetPixel(int x, int y, const Vector3& color);
    void Save(const std::string& filename);

private:
    std::vector<unsigned char> m_pixels;

    int m_width, m_height;
};
