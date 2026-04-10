#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    bool enabled; 
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;

// Creamos las luces
uniform Light light1; // Sol
uniform Light light2; // LLuna
uniform sampler2D texture_diffuse1; 

// Calculamos la luz individual
vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    if(!light.enabled) {
        return vec3(0.0);
    }

    vec3 ambient = light.ambient * material.diffuse;
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    return (ambient + diffuse + specular);
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = CalcLight(light1, norm, FragPos, viewDir);
    result += CalcLight(light2, norm, FragPos, viewDir);
    vec4 texColor = texture(texture_diffuse1, TexCoords);
    if(texColor.a < 0.1) discard; // Descartar transparencias
    color = vec4(result, 1.0f) * texColor;
}