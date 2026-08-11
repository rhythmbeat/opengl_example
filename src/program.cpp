#include "program.h"

ProgramUPtr Program::Create(const std::vector<ShaderPtr>& shaders) {
  auto program = ProgramUPtr(new Program());
  if (!program->Link(shaders))
    return nullptr;
  return std::move(program);//program 객체를 반환할 때 std::move를 사용하여 소유권을 이전, 반환 후 program은 nullptr이 됨
}//ProgramUPtr은 스마트 포인터이므로 함수가 끝나는 시점에 자동으로 메모리 해제

Program::~Program() {
    if (m_program) {
      glDeleteProgram(m_program);
    }
}

bool Program::Link(const std::vector<ShaderPtr>& shaders) {
    m_program = glCreateProgram();
    for (auto& shader: shaders)
      glAttachShader(m_program, shader->Get());
      glLinkProgram(m_program);
    
    int success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
      char infoLog[1024];
      glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
      SPDLOG_ERROR("failed to link program: {}", infoLog);
      return false;
    }
    return true;
  }

  void Program::Use() const {
    glUseProgram(m_program);
  }