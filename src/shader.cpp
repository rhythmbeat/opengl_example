#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType) {
  auto shader = ShaderUPtr(new Shader());
  if (!shader->LoadFile(filename, shaderType))
    return nullptr;
  return std::move(shader);
}

Shader::~Shader(){
  if (m_shader) {
    glDeleteShader(m_shader);
  }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType) {
  auto result = LoadTextFile(filename);
  if (!result.has_value())
    return false;

  auto& code = result.value();
  //optional의 .value()를 사용하면 optional객체 자체(string)를 반환, 값이 없으면 예외 처리(std::bad_optional_access)
  //= string&
  const char* codePtr = code.c_str();
  //c.str()는 string의 내부 버퍼를 const char*로 반환, null-terminated string
  //C++의 std::string 객체를 C 언어 스타일의 문자열(null-terminated string)로 변환해 주는 함수
  int32_t codeLength = (int32_t)code.length();

  // create and compile shader
m_shader = glCreateShader(shaderType);
glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength);
glCompileShader(m_shader);

 // check compile error
  int success = 0;
  glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[1024];
    glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
    SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
    SPDLOG_ERROR("reason: {}", infoLog);
    return false;
  }
  return true;
}