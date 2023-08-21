#version 330 core
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0
layout (location = 1) in vec3 aNormal;


out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    /*
    变换到世界空间坐标
    */
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model*vec4(aPos,1.0f));
    gl_Position = projection*view*model*vec4(aPos,1.0f);
}