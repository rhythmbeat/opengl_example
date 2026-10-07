#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"

CLASS_PTR(Context)

class Context {
public:
    static ContextUPtr Create();
    void Render();    
    void ProcessInput(GLFWwindow* window);
    void Reshape(int width, int height);
    
private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;
    

    VertexLayoutUPtr m_vertexLayout;
    //uint32_t m_vertexArray;
    //uint32_t m_vertexArrayObject;//gpu메모리에 vertex array object를 생성하고, 그 id(key)를 저장하는 변수. 이 id를 이용해서 gpu메모리에 접근할 수 있음.
    //uint32_t m_vertexBuffer;//gpu메모리에 vertex buffer object를 생성하고, 그 id를 저장하는 변수. 이 id를 이용해서 gpu메모리에 접근할 수 있음.
    //uint32_t m_indexBuffer;

    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;
    TextureUPtr m_texture;
    TextureUPtr m_texture2;

    // camera parameter
    glm::vec3 m_cameraPos { glm::vec3(0.0f, 0.0f, 3.0f) };
    glm::vec3 m_cameraFront { glm::vec3(0.0f, 0.0f, -1.0f) };
    glm::vec3 m_cameraUp { glm::vec3(0.0f, 1.0f, 0.0f) };

    int m_width {WINDOW_WIDTH};
    int m_height {WINDOW_HEIGHT};


};

#endif // __CONTEXT_H__