#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

// Propiedades comunes
uniform vec3 viewPos;
uniform bool isNightMode;
uniform vec3 Color;

// Primera luz
uniform vec3 light1Color;
uniform vec3 light1Pos;
uniform vec3 light1Dir;
uniform vec3 objectColor;

// Segunda luz
uniform vec3 light2Color;
uniform vec3 light2Pos;
uniform vec3 light2Dir;

// Texturas
uniform sampler2D ourTexture;

// Función para calcular la iluminación de una sola luz
vec3 calculateLight(vec3 lightColor, vec3 lightPos, vec3 lightDir) {
    // Luz ambiental
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    // Vector fragmento a luz
    vec3 fd = normalize(vec3(FragPos - lightPos));
    
    // Solo iluminamos si está dentro del cono de luz
    if(acos(dot(fd, lightDir)) < radians(15.0)) {
        // Luz difusa
        vec3 norm = normalize(Normal);
        vec3 lightDirNorm = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDirNorm), 0.0);
        vec3 diffuse = diff * lightColor;
        
        // Luz especular
        float specularStrength = 1.0;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDirNorm, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
        vec3 specular = specularStrength * spec * lightColor;
        
        return (ambient + diffuse) * Color;
    } else {
        return ambient * Color;
    }
}

void main() {
    if (isNightMode) {
        // Calcular contribución de ambas luces
        vec3 result1 = calculateLight(light1Color, light1Pos, light1Dir);
        vec3 result2 = calculateLight(light2Color, light2Pos, light2Dir);
        
        // Combinar resultados (sumamos las contribuciones)
        vec3 finalResult = result1 + result2;
        
        // Aseguramos que no se exceda el valor máximo
        finalResult = min(finalResult, vec3(1.0));

        vec4 texColor = texture(ourTexture, TexCoord);
        if (texColor.a < 0.1) discard;
        else FragColor = mix (vec4(finalResult, 1.0), texColor, .5);
    } else {
        vec4 texColor = texture(ourTexture, TexCoord);
        if (texColor.a < 0.1) discard;
        else FragColor = mix (vec4(Color, 1.0), texColor, .5);
    }
}