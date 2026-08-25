#version 330 core
in vec4 vertexColor;
in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D tex;
//sampler2D는 텍스쳐를 샘플링하는데 쓰이는 자료형임. 텍스쳐를 샘플링한다는 것은 텍스쳐 좌표를 이용해서 텍스쳐의 색상을 가져오는 것을 의미함.
uniform sampler2D tex2;

void main() {
    fragColor = texture(tex, texCoord)*0.8+texture(tex2, texCoord)*0.2;//texture()는 텍스쳐 좌표를 이용해서 텍스쳐의 색상(픽셀의 값)을 가져오는 함수임.
    //sampler2D형 변수 tex에 texture함수로 texCoord의 좌표를 이용해서 텍스쳐의 색상을 가져와서 fragColor에 저장함.
}