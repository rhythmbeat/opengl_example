#include "context.h"
#include "image.h"
ContextUPtr Context::Create()   {
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
    }

    bool Context::Init() {

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

        0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
    };

    uint32_t indices[] = {
        0,  2,  1,  2,  0,  3,
        4,  5,  6,  6,  7,  4,
        8,  9, 10, 10, 11,  8,
        12, 14, 13, 14, 12, 15,
        16, 17, 18, 18, 19, 16,
        20, 22, 21, 22, 20, 23,
    };

    m_vertexLayout = VertexLayout::Create();
    /*glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);*/

    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 120);

    /*glGenBuffers(1, &m_vertexBuffer);// Generate a vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);//GL_ARRAY_BUFFER 얘를 편의상 VBO라고 부르기도함.(정확히는 m_vertexBuffer의 키가 가리키는 주소가 VBO),data를 넣을때는 GL_ARRAY_BUFFER라는 통로를 연결한 뒤에 넣음, 즉 GL_ARRAY_BUFFER는 VBO를 의미하는게 아니라, VBO에 데이터를 넣을때 쓰는 용도임), 나중에 element buffer object와 index buffer object라는 이름의 VBO도 있음. 얘네는 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexBuffer) 이런식으로 바인딩(연결)함.
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);
    //sizeof 변수, 자료형, 배열이 메모리에서 차지하는 크기(바이트 단위) 함수가 아니라 연산자라 컴파일 시 그냥 그 자리에서 숫자로 바꿔치기함.
    //float은 4바이트, vertices는 float형 배열이고, 3개의 vertex가 있고, 각 vertex는 3개의 좌표(x,y,z)를 가지므로 총 9개의 float이므로 sizeof(float) * 9(=36)임.
    //GL_STATIC_DRAW는 GPU에 데이터를 한번만 보내고, 그 이후에는 거의 안 바뀌는 데이터를 의미함.
    //vertices는 포인터라는데 무슨 소리야? vertices는 float형 배열의 시작 주소를 가리키는 포인터임.*/ //위 코드 한 줄로 대체(클래스 분리)

    //m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0); //xyw
    //m_vertexLayout->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 3); //처음에서 3만큼 건너뛰면 rgb
    m_vertexLayout->SetAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, sizeof(float) * 3); //처음에서 6만큼 건너뛰면 uv 텍스쳐 좌표
    /*glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);*/

    m_indexBuffer=Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(uint32_t) * 36);
    /*glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, indices, GL_STATIC_DRAW);*/

        ShaderPtr vertShader = Shader::CreateFromFile("./shader/texture.vs", GL_VERTEX_SHADER);
        ShaderPtr fragShader = Shader::CreateFromFile("./shader/texture.fs", GL_FRAGMENT_SHADER);
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

        auto image = Image::Load("./image/container.jpg");
        if (!image) 
             return false;


         SPDLOG_INFO("image: {}x{}, {} channels", 
            image->GetWidth(), image->GetHeight(), image->GetChannelCount());
        

        m_texture = Texture::CreateFromImage(image.get());//유니크포인터로부터 그냥 로우포인터를 가져오는 방법은 .get(); .하면 유니크포인터에 들어있는 기본 함수를 호출할 수 있다는데 애초에 유니크 포인터에 get() 등등이 들어있다는 소리인가?
        
        auto image2 = Image::Load("./image/awesomeface.png");
        m_texture2 = Texture::CreateFromImage(image2.get());
        /* glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//이미지가 많이 축소되었을 때 쓰는 필터, linear로 지정
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//이미지가 많이 확대되었을 때 쓰는 필터, linear로 지정
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//텍스쳐가 0, 1 좌표를 벗어났을 때 어떻게 처리할지 지정, GL_CLAMP_TO_EDGE는 좌표가 0보다 작으면 0, 1보다 크면 1로 처리함.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//텍스쳐 좌표계에서 S축과 T축이 있음, S축은 x축, T축은 y축임. GL_CLAMP_TO_EDGE는 제일 모서리에 있는 픽셀 색상을 그대로 사용함. GL_REPEAT는 좌표를 0~1 범위로 나눈 나머지 값을 사용함. GL_MIRRORED_REPEAT는 좌표를 0~1 범위로 나눈 몫이 짝수면 그대로, 홀수면 1에서 뺀 값을 사용함.

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
            image->GetWidth(), image->GetHeight(), 0,
            GL_RGB, GL_UNSIGNED_BYTE, image->GetData());*/ //texture.cpp에서 Texture 클래스의 SetTextureFromImage 함수로 대체
                
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture->Get());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture2->Get());

        m_program->Use();
        m_program->SetUniform("tex", 0);
        m_program->SetUniform("tex2", 1);

        // // 위치 (1, 0, 0)의 점. 동차좌표계 사용해서 마지막 w가 1.0f
        // glm::vec4 vec(1.0f,  0.0f, 0.0f, 1.0f); //여기서 vec4는 클래스, 뒤는 클래스에 인수값을 집어넣는 것뿐
        // // 단위행렬 기준 (1, 1, 0)만큼 평행이동하는 행렬(trans)
        // auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        // // 단위행렬 기준 z축으로 90도만큼 회전하는 행렬
        // auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // // 단위행렬 기준 모든 축에 대해 3배율 확대하는 행렬
        // auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f));
        // // 확대 -> 회전 -> 평행이동 순으로 점에 선형 변환 적용
        // vec = trans * rot * scale * vec; //vec에 붙어있는 순서대로 계산, scale, rot, trans
        // //(3,0,0)=>(0,3,0)=>(1,4,0)
        // SPDLOG_INFO("transformed vec: [{}, {}, {}]", vec.x, vec.y, vec.z);

        // x축으로 -55도 회전
        auto model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // 카메라는 원점으로부터 z축 방향으로 -3만큼 떨어짐
        auto view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        // 종횡비 4:3, 세로화각 45도의 원근 투영
        auto projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 10.0f);
        auto transform = projection * view * model;
        m_program->SetUniform("transform", transform);//이 코드로 아래 두 줄 대체
       /* auto transformLoc = glGetUniformLocation(m_program->Get(), "transform");//"transform"이라는 변수가 해당하는 위치를 알려달라
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));//value_ptr은 floating point 값 16개를 담고있는 transform 클래스?변수?에서 첫번째 값이 저장되어 있는 주소값을 리턴하는 함수, 덕분에 16개의 주소를 줄줄이 얻어서 gpu에 넘겨줄 수 있다*/
        return true;
    }

    

void Context::Render() {

    std::vector<glm::vec3> cubePositions = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f, 2.0f, -2.5f),
        glm::vec3( 1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f),
    };



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
//     static float time = 0.0f;
//   float t = sinf(time) * 0.5f + 0.5f;
//   auto loc = glGetUniformLocation(m_program->Get(), "color");
   m_program->Use();

    auto projection = glm::perspective(glm::radians(45.0f),
        (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 10.0f);
    auto view = glm::translate(glm::mat4(1.0f),
        glm::vec3(0.0f, 0.0f, -3.0f));

   for (size_t i = 0; i < cubePositions.size(); i++){
        auto& pos = cubePositions[i];
        auto model = glm::translate(glm::mat4(1.0f), pos);
        model = glm::rotate(model,
            glm::radians((float)glfwGetTime() * 120.0f + 20.0f * (float)i),
            glm::vec3(1.0f, 0.5f, 0.0f));
        auto transform = projection * view * model;
        m_program->SetUniform("transform", transform);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

//   time += 0.016f;

    // m_program->Use();
    // //glUseProgram(m_program->Get());
    // //glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}