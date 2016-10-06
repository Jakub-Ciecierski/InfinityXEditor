#version 400 core

in vec2 vTexCoords;
out vec4 color;

uniform sampler2D screen_texture;

// Convolution matrix offset
const float offset = 1.0 / 300;
const int kernel_size = 9;
vec2 offsets[kernel_size] = vec2[](
    vec2(-offset, offset),  // top-left
    vec2(0.0f,    offset),  // top-center
    vec2(offset,  offset),  // top-right
    vec2(-offset, 0.0f),    // center-left
    vec2(0.0f,    0.0f),    // center-center
    vec2(offset,  0.0f),    // center-right
    vec2(-offset, -offset), // bottom-left
    vec2(0.0f,    -offset), // bottom-center
    vec2(offset,  -offset)  // bottom-right
);

vec4 getColor();
vec4 getInversionColor();
vec4 getGrayscale();

vec4 getConvolutionColor();
float[kernel_size] getSharpenKernel();
float[kernel_size] getBlurKernel();
float[kernel_size] getEdgeDetectionKernel();

void main()
{
    color = getGrayscale();
    //color = getConvolutionColor();
}

vec4 getColor(){
    return texture(screen_texture, vTexCoords);
}

vec4 getInversionColor(){
    return vec4(vec3(1.0 - texture(screen_texture, vTexCoords)), 1.0);
}

vec4 getGrayscale(){
    vec4 default_color = getColor();

    float average = (default_color.r + default_color.g + default_color.b) / 3.0;
    return  vec4(average, average, average, 1.0);
}

vec4 getConvolutionColor(){
    float[kernel_size] kernel = getBlurKernel();

    vec3 sampleTex[kernel_size];
    for(int i = 0; i < kernel_size; i++){
        sampleTex[i] = vec3(texture(screen_texture, vTexCoords.xy + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for(int i = 0; i < kernel_size; i++)
        col += sampleTex[i] * kernel[i];

    return vec4(col, 1.0);
}

float[kernel_size] getSharpenKernel(){
    float kernel[kernel_size] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );
    return kernel;
}

float[kernel_size] getBlurKernel(){
    float kernel[kernel_size] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16
    );
    return kernel;
}

float[kernel_size] getEdgeDetectionKernel(){
    float kernel[kernel_size] = float[](
        1, 1,  1,
        1, -8, 1,
        1, 1,  1
    );
    return kernel;
}