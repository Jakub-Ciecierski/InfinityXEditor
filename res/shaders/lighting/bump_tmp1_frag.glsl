#version 330 core

/*
 * Bump mapping
 * http://www.nvidia.com/object/real-time-normal-map-dxt-compression.html
 * http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
 */

// ---------- IN/OUT ---------- //

in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;
in vec3 FragPos;
in vec2 TexCoords;

in mat4 ViewMatrix_ps;
in mat4 ProjectionMatrix_ps;

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

// Big leap of faith, assumes that Cubemap object has bound the uniform texture
uniform samplerCube cubemap;

// ---------- HEADERS ---------- //

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos,
                        vec3 viewDir, mat3 TBN);
vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir, mat3 TBN);
vec3 computeSpotLight(SpotLight light, vec3 norm, vec3 fragPos,
                        vec3 viewDir, mat3 TBN);

void main()
{
    // Load normal from normal map and normalize to [-1. 1].
    vec3 norm = normalize(texture(material.normal, TexCoords).rgb * 2.0 - 1.0);
    //norm = normalize(Normal);

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

    float ratio = 1.00f / 1.33f;
    vec3 I = -viewDir;

    vec3 Rreflect = reflect(I, norm);
    vec3 Rrefract = refract(I, norm, ratio);

    vec4 refl = texture(cubemap, Rreflect);
    vec4 refr = texture(cubemap, Rrefract);

    // Constants !
    float rzero = pow((1.33 - 1.0)/(1.33 + 1.0), 2.0);
    float cosfi = abs(normalize(viewDir).y);
    float frasnel = rzero + (1.0-rzero) * pow(1.0-cosfi, 5.0);

    color = vec4(vec3(mix(refr, refl, frasnel)), 0.5f);
}

vec3 computePointLight(PointLight light, vec3 norm, vec3 fragPos,
                        vec3 viewDir, mat3 TBN){
    vec3 lightDir = normalize(light.position - fragPos);

    // ---- Transform to TBN basis ----- //
    //viewDir = TBN * viewDir;
    //lightDir = TBN * lightDir;

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

vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir, mat3 TBN){
    vec3 lightDir = normalize(-light.direction);

    // ---- Transform to TBN basis ----- //
    //viewDir = TBN * viewDir;
    //lightDir = TBN * lightDir;

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

vec3 computeSpotLight(SpotLight light, vec3 norm, vec3 fragPos, vec3 viewDir,
                        mat3 TBN){
    vec3 lightDir = normalize(light.position - fragPos);

    // ---- Transform to TBN basis ----- //
    //viewDir = TBN * viewDir;
    //lightDir = TBN * lightDir;

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