#include "texture.h"

TextureUPtr Texture::CreateFromImage(const Image* image) {
    auto texture = TextureUPtr(new Texture());
    texture->CreateTexture();
    texture->SetTextureFromImage(image);
    return std::move(texture);
}

Texture::~Texture() {
    if (m_texture) {
        glDeleteTextures(1, &m_texture);
    }
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::SetFilter(uint32_t minFilter, uint32_t magFilter) const {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);//이 함수의 역할은 텍스처의 필터링 방식을 설정하는 것이다. minFilter는 텍스처가 축소될 때 사용할 필터링 방식을 지정하고, magFilter는 텍스처가 확대될 때 사용할 필터링 방식을 지정한다.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void Texture::SetWrap(uint32_t sWrap, uint32_t tWrap) const {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
}
    
void Texture::CreateTexture() {
    glGenTextures(1, &m_texture);
    // bind and set default filter and wrap option
    Bind();
    SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    //SetFilter(GL_LINEAR, GL_LINEAR);
    SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

void Texture::SetTextureFromImage(const Image* image) {
    GLenum format = GL_RGBA;
    switch (image->GetChannelCount()) {
        default: break;
        case 1: format = GL_RED; break;
        case 2: format = GL_RG; break;
        case 3: format = GL_RGB; break;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
        image->GetWidth(), image->GetHeight(), 0,
        format, GL_UNSIGNED_BYTE,
        image->GetData());

        glGenerateMipmap(GL_TEXTURE_2D);
}
//이미지 파일의 채널 수(흑백인지, 컬러인지 등)를 파악한 뒤, CPU 메모리에 들어있는 가로·세로 픽셀 데이터(image->GetData())를 그대로 읽어와 GPU의 텍스처 공간으로 업로드하는 함수