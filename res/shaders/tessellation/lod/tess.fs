#version 400 core

in vec3 teNormal;
in vec3 teTangent;
in vec3 teBinormal;
in vec3 teFragPos;
in vec2 teTexCoords;

out vec4 color;


// ---------- VARIABLES  ---------- //

struct Material {
    sampler2D diffuse; // ambient == diffuse
    sampler2D specular;
    sampler2D normal;
    sampler2D displacement;

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

const vec3 diffColor = vec3(1.0f, 1.0f, 0.0f);
const vec3 specColor = vec3(0.0f, 0.0f, 0.0f);

// ---------- HEADERS ---------- //

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos,
                        vec3 viewDir);
vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir);
vec3 computeSpotLight(SpotLight light, vec3 norm, vec3 fragPos,
                        vec3 viewDir);

void main()
{
    vec3 norm = normalize(texture(material.normal,
                            teTexCoords).rgb * 2.0 - 1.0);
    norm = (norm.x * teTangent) + (norm.y * teBinormal) + (norm.z * teNormal);
    norm = normalize(norm);

    vec3 viewDir = normalize(viewPos - teFragPos);

    vec3 result = vec3(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < pointlightCount; i++){
        result += computePointLight(pointLights[i], norm, teFragPos, viewDir);
    }
    for(int i = 0; i < dirlightCount; i++){
        result += computeDirLight(dirLights[i], norm, viewDir);
    }
    for(int i = 0; i < spotlightCount; i++){
        result += computeSpotLight(spotLights[i], norm, teFragPos, viewDir);
    }

    color = vec4(result, 1.0f);
}

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos,
                        vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);

    // ---- Ambient ----- //
    vec3 ambient = vec3(texture(material.diffuse, teTexCoords)) * light.ambient;
    //vec3 ambient = diffColor * light.ambient;

    // ---- Diffuse ----- //
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = //diffuseFactor * diffColor * light.diffuse;
    diffuseFactor * vec3(texture(material.diffuse, teTexCoords)) * light.diffuse;

    // ---- Specular ----- //
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = //specColor * spec * light.specular;
    vec3(texture(material.specular, teTexCoords)) * spec * light.specular;

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
    vec3 ambient = diffColor * light.ambient;
    //vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

    // ---- Diffuse ----- //
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diffuseFactor * diffColor * light.diffuse;
    //diffuseFactor * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;


    // ---- Specular----- //
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specColor * spec * light.specular;
    //vec3(texture(material.specular, TexCoords)) * spec * light.specular;

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
    vec3 ambient = vec3(texture(material.diffuse, teTexCoords)) * light.ambient;
    //vec3 ambient = diffColor * light.ambient;

    // ---- Diffuse ----- //
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = //diffuseFactor * diffColor * light.diffuse;
    diffuseFactor * vec3(texture(material.diffuse, teTexCoords)) * light.diffuse;

    // ---- Specular ----- //
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = //specColor * spec * light.specular;
    vec3(texture(material.specular, teTexCoords)) * spec * light.specular;

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