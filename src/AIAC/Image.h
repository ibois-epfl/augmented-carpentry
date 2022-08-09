#pragma once

#include <string_view>
#include <stdint.h>
#include <stdlib.h>

namespace AIAC
{
    enum class ImageFormat
    {
        None = 0,
        RGB,
        RGBA,
        GRAYSCALE
    };

    class Image
    {
    public:
        Image(const char* path);
        // Image(uint32_t width, uint32_t height, ImageFormat format, const void* data = nullptr);
        ~Image();
    
    private:
        const char* m_Path;

        uint32_t m_Width = 0, m_Height = 0;
        ImageFormat m_Format = ImageFormat::None;
        size_t m_Size = 0;
    };
}