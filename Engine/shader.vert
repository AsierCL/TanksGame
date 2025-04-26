#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

out vec3 ourColor;
out vec3 FragPos;  // Posición del fragmento en el espacio del mundo
out vec3 Normal;   // Normal en el espacio del mundo
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0f));  // Calcula la posición del fragmento
    Normal = mat3(transpose(inverse(model))) * aNormal;  // Calcula la normal transformada
    ourColor = aColor;  // Pasa el color al fragment shader
    TexCoord = aTexCoord;
}