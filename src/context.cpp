#include "context.h"

ContextUPtr Context::Create()   {
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
    }

    bool Context::Init() {
        
    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right, red
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right, green
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left, blue
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // top left, yellow
    };
    uint32_t indices[] = { // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3, // second triangle
    };

    m_vertexLayout = VertexLayout::Create();
    /*glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);*/

    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 24);

    /*glGenBuffers(1, &m_vertexBuffer);// Generate a vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);//GL_ARRAY_BUFFER 얘를 편의상 VBO라고 부르기도함.(정확히는 m_vertexBuffer의 키가 가리키는 주소가 VBO),data를 넣을때는 GL_ARRAY_BUFFER라는 통로를 연결한 뒤에 넣음, 즉 GL_ARRAY_BUFFER는 VBO를 의미하는게 아니라, VBO에 데이터를 넣을때 쓰는 용도임), 나중에 element buffer object와 index buffer object라는 이름의 VBO도 있음. 얘네는 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexBuffer) 이런식으로 바인딩(연결)함.
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);
    //sizeof 변수, 자료형, 배열이 메모리에서 차지하는 크기(바이트 단위) 함수가 아니라 연산자라 컴파일 시 그냥 그 자리에서 숫자로 바꿔치기함.
    //float은 4바이트, vertices는 float형 배열이고, 3개의 vertex가 있고, 각 vertex는 3개의 좌표(x,y,z)를 가지므로 총 9개의 float이므로 sizeof(float) * 9(=36)임.
    //GL_STATIC_DRAW는 GPU에 데이터를 한번만 보내고, 그 이후에는 거의 안 바뀌는 데이터를 의미함.
    //vertices는 포인터라는데 무슨 소리야? vertices는 float형 배열의 시작 주소를 가리키는 포인터임.*/ //위 코드 한 줄로 대체(클래스 분리)

    //m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    m_vertexLayout->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, sizeof(float) * 3);
    /*glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);*/

    m_indexBuffer=Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(uint32_t) * 6);
    /*glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, indices, GL_STATIC_DRAW);*/

        ShaderPtr vertShader = Shader::CreateFromFile("./shader/per_vertex_color.vs", GL_VERTEX_SHADER);
        ShaderPtr fragShader = Shader::CreateFromFile("./shader/per_vertex_color.fs", GL_FRAGMENT_SHADER);
        if (!vertShader || !fragShader)
            return false;
        SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
        SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

        m_program = Program::Create({fragShader, vertShader});
         if (!m_program)
            return false;
            
        SPDLOG_INFO("program id: {}", m_program->Get());

        /*auto loc = glGetUniformLocation(m_program->Get(), "color");
        //color라는 변수의 위치를 정수 형태로 반환하는 함수, 이 위치를 이용해서 color라는 uniform 변수에 값을 넣을 수 있음.
        m_program->Use();
        glUniform4f(loc, 0.0f, 1.0f, 0.0f, 1.0f);*/

        glClearColor(0.0f, 0.1f, 0.2f, 0.0f);

        
        return true;
    }

void Context::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

//     static float time = 0.0f;
//   float t = sinf(time) * 0.5f + 0.5f;
//   auto loc = glGetUniformLocation(m_program->Get(), "color");
   m_program->Use();
//   glUniform4f(loc, t*t, 2.0f*t*(1.0f-t), (1.0f-t)*(1.0f-t), 1.0f);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//   time += 0.016f;

    // m_program->Use();
    // //glUseProgram(m_program->Get());
    // //glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}