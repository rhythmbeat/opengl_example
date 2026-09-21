#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

//class klassName; 이런 이름의 클래스가 있다고 알려주는 전방 선언
//이게 없으면 아래의 unique_ptr<buffer>에서 buffer가 뭔지 몰라서 에러남.std::unique_ptr<Buffer>를 만들려고 할 때
//컴파일러는 "Buffer가 도대체 뭐죠? 변수인가요, 클래스인가요?" 하고 에러를 내게 됩니다.

std::optional<std::string> LoadTextFile(const std::string& filename);

#endif // __COMMON_H__