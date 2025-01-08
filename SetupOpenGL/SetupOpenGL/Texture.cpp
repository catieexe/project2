#include "Texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string& filePath) {
    LoadTexture(filePath);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::SetSpriteSheetSize(const glm::vec2& size) {
    m_SpriteSheetSize = size;
}

void Texture::LoadTexture(const std::string& filePath) {
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_NumChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
