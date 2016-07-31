#version 330 core

/*
 * Phong illumination: Flashlight with Attenuation.
 * Use with combination with LightDirectional
 */

// ---------- IN/OUT ---------- //

in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

// ---------- VARIABLES  ---------- //

struct Material {
    sampler2D diffuse; // ambient == diffuse
    sampler2D specular;

    float shininess;
};

#define MAX_LIGHT_COUNT 16

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight{
    vec3 position;
    vec3 direction;

    float cutOff;           // cutOff is expected to be the value
    float outerCutOff;      // of cos(_cutOff), where _cutOff comes from CPU

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

// ---------- UNIFORMS ---------- //

uniform PointLight pointLights[MAX_LIGHT_COUNT];
uniform DirLight dirLights[MAX_LIGHT_COUNT];
uniform SpotLight spotLights[MAX_LIGHT_COUNT];

uniform int pointlightCount;
uniform int dirlightCount;
uniform int spotlightCount;

uniform Material material;
uniform vec3 viewPos;

// ---------- HEADERS ---------- //

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos,
                        vec3 viewDir);
vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir);
vec3 computeSpotLight(SpotLight light, vec3 norm, vec3 fragPos,
                        vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < pointlightCount; i++){
        result += computePointLight(pointLights[i], norm, FragPos, viewDir);
    }
    for(int i = 0; i < dirlightCount; i++){
        result += computeDirLight(dirLights[i], norm, viewDir);
    }
    for(int i = 0; i < spotlightCount; i++){
        result += computeSpotLight(spotLights[i], norm, FragPos, viewDir);
    }

    color = vec4(result, 1.0f);
}

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos,
                        vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);

    // ---- Ambient ----- //
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

    // ---- Diffuse ----- //
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse =
    diffuseFactor * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;

    // ---- Specular ----- //
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =
    vec3(texture(material.specular, TexCoords)) * spec * light.specular;

    // ---- Attenuation ----- //
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f /
    ((light.constant) + (light.linear * distance) +
    (light.quadratic * (distance* distance)));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = (ambient + diffuse + specular);

    return result;
}

vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);

    // ---- Ambient ----- //
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

    // ---- Diffuse ----- //
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse =
    diffuseFactor * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;

    // ---- Specular----- //
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =
    vec3(texture(material.specular, TexCoords)) * spec * light.specular;

    vec3 result = (ambient + diffuse + specular);
    return result;
}

vec3 computeSpotLight(SpotLight light, vec3 norm, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);

    // ---- Spotlight ----- //
    // Check the flashlight condition.
    // The cosine between light direction and direction from the fragment
    float theta = dot(lightDir, normalize(-light.direction));
    // Calculate the outer cone difference
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // ---- Ambient ----- //
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

    // ---- Diffuse ----- //
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse =
    diffuseFactor * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;

    // ---- Specular ----- //
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =
    vec3(texture(material.specular, TexCoords)) * spec * light.specular;

    // ---- Attenuation ----- //
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f /
    ((light.constant) +
    (light.linear * distance) +
    (light.quadratic * (distance* distance)));

    ambient *= attenuation;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    vec3 result = (ambient + diffuse + specular);
    return result;
}