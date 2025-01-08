#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Texture {
public:
    Texture(const std::string& filePath, const glm::vec2& spriteSheetSize);
    ~Texture();
    void Bind(unsigned int unit = 0) const;
    const glm::vec2& GetSpriteSheetSize() const;

    GLuint m_TextureID;
    int m_Width, m_Height, m_NumChannels;
    glm::vec2 m_SpriteSheetSize; 

private:
    void LoadTexture(const std::string& filePath);
};

#endif // TEXTURE_H