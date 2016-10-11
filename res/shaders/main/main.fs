#version 330 core

/**
 * Contains:
 *
 *  Blinn-Phong
 *
 *  Multiple light sources:
 *      1) Point Light
 *      2) Directional
 *      3) Spotlight
 *
 *  Bump Mapping (TODO Correct TBN)
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
    sampler2D normal;

    float shininess;
};

#define MAX_LIGHT_COUNT 16

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    mat4 LightSpaceMatrix;
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

// Shadow Mapping
uniform sampler2D shadow_map;

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

// Shadow Mapping
float ShadowMappingCalculation(vec4 fragPosLightSpace);

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos,
                       vec3 viewDir, mat3 TBN);
vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir, mat3 TBN);
vec3 computeSpotLight(SpotLight light, vec3 norm, vec3 fragPos,
                      vec3 viewDir, mat3 TBN);

vec3 computeAmbient(vec3 ambientLight);
vec3 computeDiffuse(vec3 norm, vec3 lightDir, vec3 diffuseLight);
vec3 computeSpecular(vec3 norm, vec3 lightDir,
                     vec3 viewDir, vec3 specularLight);

float ShadowMappingCalculation(vec4 fragPosLightSpace){
    // Projection.
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // Depth map is in range [0,1].
    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadow_map, projCoords.xy).r;
    float currentDepth = projCoords.z;
    float shadow = closestDepth < currentDepth ? 1 : 0;

    //return currentDepth;
    //return closestDepth;
    return shadow;
}

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos,
                        vec3 viewDir, mat3 TBN){
    vec3 lightDir = normalize(light.position - fragPos);

    // ---- Transform to TBN basis ----- //
    //viewDir = TBN * viewDir;
    //lightDir = TBN * lightDir;

    vec3 ambient = computeAmbient(light.ambient);
    vec3 diffuse = computeDiffuse(norm, lightDir, light.diffuse);
    vec3 specular = computeSpecular(norm, lightDir, viewDir, light.specular);

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

vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir, mat3 TBN){
    vec3 lightDir = normalize(-light.direction);

    // ---- Transform to TBN basis ----- //
    //viewDir = TBN * viewDir;
    //lightDir = TBN * lightDir;

    vec3 ambient = computeAmbient(light.ambient);
    vec3 diffuse = computeDiffuse(norm, lightDir, light.diffuse);
    vec3 specular = computeSpecular(norm, lightDir, viewDir, light.specular);

    // Shadow Mapping
    vec4 fragPosLightSpace = light.LightSpaceMatrix * vec4(FragPos, 1.0);
    float shadow = ShadowMappingCalculation(fragPosLightSpace);

    vec3 result = (ambient + diffuse + specular);
    //vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular));

    return result;
}

vec3 computeSpotLight(SpotLight light, vec3 norm, vec3 fragPos, vec3 viewDir,
                      mat3 TBN){
    vec3 lightDir = normalize(light.position - fragPos);

    // ---- Transform to TBN basis ----- //
    //viewDir = TBN * viewDir;
    //lightDir = TBN * lightDir;

    vec3 ambient = computeAmbient(light.ambient);
    vec3 diffuse = computeDiffuse(norm, lightDir, light.diffuse);
    vec3 specular = computeSpecular(norm, lightDir, viewDir, light.specular);

    // ---- Spotlight ----- //
    // Check the flashlight condition.
    // The cosine between light direction and direction from the fragment
    float theta = dot(lightDir, normalize(-light.direction));
    // Calculate the outer cone difference
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // ---- Attenuation ----- //
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f /  ((light.constant) + (light.linear * distance) +
        (light.quadratic * (distance* distance)));

    ambient *= attenuation;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    vec3 result = (ambient + diffuse + specular);
    return result;
}


vec3 computeAmbient(vec3 ambientLight){
    vec3 ambientObject = vec3(texture(material.diffuse, TexCoords));
    vec3 ambient = ambientObject * ambientLight;

    return ambient;
}

vec3 computeDiffuse(vec3 norm, vec3 lightDir, vec3 diffuseLight){
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);

    vec3 diffuseObject = vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = diffuseFactor * diffuseObject * diffuseLight;

    return diffuse;
}

vec3 computeSpecular(vec3 norm, vec3 lightDir,
                     vec3 viewDir, vec3 specularLight){
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float specularFactor
        = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specularObject = vec3(texture(material.specular, TexCoords));
    vec3 specular = specularObject * specularFactor * specularLight;

    return specular;
}

void main() {
    // Load normal from normal map and normalize to [-1. 1].
    vec3 norm = normalize(texture(material.normal, TexCoords).rgb * 2.0 - 1.0);
    norm = normalize(Normal);

    vec3 viewDir = normalize(viewPos - FragPos);

    // The Tangent Basis
    mat3 TBN = transpose(mat3(Tangent, Binormal, Normal));

    vec3 result = vec3(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < pointlightCount; i++){
        result += computePointLight(pointLights[i], norm, FragPos, viewDir,
                                    TBN);
    }
    for(int i = 0; i < dirlightCount; i++){
        result += computeDirLight(dirLights[i], norm, viewDir, TBN);
    }
    for(int i = 0; i < spotlightCount; i++){
        result += computeSpotLight(spotLights[i], norm, FragPos, viewDir, TBN);
    }

    color = vec4(result, 1.0f);

    float depthValue = texture(shadow_map, TexCoords).r;
    //color = vec4(vec3(depthValue), 1.0);
}
