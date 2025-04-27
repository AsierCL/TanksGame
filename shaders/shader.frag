#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

// Material
uniform vec3 objectColor;
uniform sampler2D ourTexture;

// Ambient
uniform vec3 ambientColor;
uniform float ambientStrength;

// Directional "sun" light
uniform vec3 sunDirection; // normalized, points from fragment toward light
uniform vec3 sunColor;

// Camera position
uniform vec3 viewPos;

void main() {
    // Texture
    vec4 tex = texture(ourTexture, TexCoord);
    if (tex.a < 0.1) discard;
    vec3 baseColor = mix(objectColor, tex.rgb, tex.a);

    // Ambient component
    vec3 ambient = ambientStrength * ambientColor;

    // Diffuse component
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-sunDirection);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * sunColor;

    // Specular component (Phong)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * sunColor;

    vec3 result = (ambient + diffuse + specular) * baseColor;
    FragColor = vec4(result, 1.0);
}
