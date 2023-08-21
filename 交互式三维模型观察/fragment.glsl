#version 330
out vec4 FragColor;
in vec3 ourColor; // 向片段着色器输出一个颜色


void main() {
FragColor = vec4(ourColor,1.0f);

}
