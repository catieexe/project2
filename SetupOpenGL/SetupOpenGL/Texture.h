#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

class Texture
{
public:
    Texture(const std::string& filePath);
    ~Texture();

    void Bind(unsigned int unit = 0) const;

private:
    GLuint m_TextureID;
    int m_Width, m_Height, m_NumChannels;
};

#endif // TEXTURE_H