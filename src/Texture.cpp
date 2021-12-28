#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char *filePath) {
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D_ARRAY, _id);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, 32, 32, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    {
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(R"(C:\CompSci\Block Game\res\dirt.png)", &width, &height, &nrChannels, 0);
        if (data) {
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
                            0, 0, 0,
                            32, 32, 1,
                            GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    {
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(R"(C:\CompSci\Block Game\res\grass.png)", &width, &height, &nrChannels, 0);
        if (data) {
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
                            0, 0, 1,
                            32, 32, 1,
                            GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}

Texture::~Texture() {
    glDeleteTextures(1, &_id);
}

void Texture::Use() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);
}

