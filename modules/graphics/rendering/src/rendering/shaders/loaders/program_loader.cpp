#include "rendering/shaders/loaders/program_loader.h"

ProgramLoader::ProgramLoader(){

}

ProgramLoader::~ProgramLoader() {

}

Program* ProgramLoader::loadTessellationLODProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/tessellation/lod/tess.vs");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/tessellation/lod/tess.fs");
    TessControlShader tessControlShader =
            shaderLoader.loadTessControlShader
                    ("res/shaders/tessellation/lod/tess.tcs");
    TessEvalShader tessEvalShader =
            shaderLoader.loadTessEvalShader
                    ("res/shaders/tessellation/lod/tess.tes");

    vertexShader.compile();
    fragmentShader.compile();
    tessControlShader.compile();
    tessEvalShader.compile();

    Program* program = new Program(vertexShader, fragmentShader,
                                   tessControlShader,
                                   tessEvalShader);
    return program;
}

Program* ProgramLoader::loadTessellationBicubicBezierPolygonProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/tessellation/bicubic_bezier/polygon/tess.vs");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/tessellation/bicubic_bezier/polygon/tess.fs");

    vertexShader.compile();
    fragmentShader.compile();

    Program* program = new Program(vertexShader, fragmentShader);
    return program;
}

Program* ProgramLoader::loadTessellationBicubicBezierProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/tessellation/bicubic_bezier/tess.vs");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/tessellation/bicubic_bezier/tess.fs");
    TessControlShader tessControlShader =
            shaderLoader.loadTessControlShader
                    ("res/shaders/tessellation/bicubic_bezier/tess.tcs");
    TessEvalShader tessEvalShader =
            shaderLoader.loadTessEvalShader
                    ("res/shaders/tessellation/bicubic_bezier/tess.tes");

    vertexShader.compile();
    fragmentShader.compile();
    tessControlShader.compile();
    tessEvalShader.compile();

    Program* program = new Program(vertexShader, fragmentShader,
                                   tessControlShader,
                                   tessEvalShader);
    return program;
}

Program* ProgramLoader::loadTessellationProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/tessellation/tess.vs");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/tessellation/tess.fs");
    TessControlShader tessControlShader =
            shaderLoader.loadTessControlShader
                    ("res/shaders/tessellation/tess.tcs");
    TessEvalShader tessEvalShader =
            shaderLoader.loadTessEvalShader
                    ("res/shaders/tessellation/tess.tes");

    vertexShader.compile();
    fragmentShader.compile();
    tessControlShader.compile();
    tessEvalShader.compile();

    Program* program = new Program(vertexShader, fragmentShader,
                                              tessControlShader,
                                              tessEvalShader);
    return program;
}

Program* ProgramLoader::loadAllLightProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/light_all_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/light_all_frag.glsl");

    vertexShader.compile();
    fragmentShader.compile();

    Program* programGlobalLight = new Program(vertexShader, fragmentShader);
    return programGlobalLight;
}

Program* ProgramLoader::loadAnisotropicLightProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/anis_light_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/anis_light_frag.glsl");

    vertexShader.compile();
    fragmentShader.compile();

    Program* programGlobalLight = new Program(vertexShader, fragmentShader);
    return programGlobalLight;
}

Program* ProgramLoader::loadCubemapProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/cubemap_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/cubemap_frag.glsl");

    vertexShader.compile();
    fragmentShader.compile();

    Program* programGlobalLight = new Program(vertexShader, fragmentShader);
    return programGlobalLight;
}

Program* ProgramLoader::loadBumpMappingProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/bump_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/bump_frag.glsl");

    vertexShader.compile();
    fragmentShader.compile();

    Program* programGlobalLight = new Program(vertexShader, fragmentShader);
    return programGlobalLight;
}

Program *ProgramLoader::loadLampProgram() {
    VertexShader vertexShaderLight =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/lamp_vert.glsl");
    FragmentShader fragmentShaderLight =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/lamp_frag.glsl");
    vertexShaderLight.compile();
    fragmentShaderLight.compile();

    Program* programLamp = new Program(vertexShaderLight, fragmentShaderLight);

    return programLamp;
}
