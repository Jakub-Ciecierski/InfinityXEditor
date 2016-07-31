#include "shaders/loaders/program_loader.h"

#include "resources/resources.h"

ProgramLoader::ProgramLoader(){

}

ProgramLoader::~ProgramLoader() {

}

Program* ProgramLoader::CreateProgram(std::string vertex_path,
                                      std::string fragment_path){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader(vertex_path.c_str());
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader(fragment_path.c_str());

    vertexShader.compile();
    fragmentShader.compile();

    Program* program = new Program(vertexShader, fragmentShader);

    return program;
}
Program* ProgramLoader::CreateProgram(std::string vertex_path,
                                      std::string fragment_path,
                                      std::string tcs_path,
                                      std::string tes_path){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader(vertex_path.c_str());
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader(fragment_path.c_str());
    TessControlShader tessControlShader =
            shaderLoader.loadTessControlShader(tcs_path.c_str());
    TessEvalShader tessEvalShader =
            shaderLoader.loadTessEvalShader(tes_path.c_str());

    vertexShader.compile();
    fragmentShader.compile();
    tessControlShader.compile();
    tessEvalShader.compile();

    Program* program = new Program(vertexShader, fragmentShader,
                                   tessControlShader,
                                   tessEvalShader);

    return program;
}

Program* ProgramLoader::loadTessellationLODProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();
    std::string vertex_path =
            resources.GetResourcePath("tessellation/lod/tess.vs",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("tessellation/lod/tess.fs",
                                      ifx::ResourceType::SHADER);
    std::string tcs_path =
            resources.GetResourcePath("tessellation/lod/tess.tcs",
                                      ifx::ResourceType::SHADER);
    std::string tes_path =
            resources.GetResourcePath("tessellation/lod/tess.tes",
                                      ifx::ResourceType::SHADER);

    Program* program = CreateProgram(vertex_path, fragment_path,
                                     tcs_path, tes_path);
    return program;
}

Program* ProgramLoader::loadTessellationBicubicBezierPolygonProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath
                    ("tessellation/bicubic_bezier/polygon/tess.vs",
                     ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath
                    ("tessellation/bicubic_bezier/polygon/tess.fs",
                     ifx::ResourceType::SHADER);

    Program* program = CreateProgram(vertex_path, fragment_path);

    return program;
}

Program* ProgramLoader::loadTessellationBicubicBezierProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();
    std::string vertex_path =
            resources.GetResourcePath("tessellation/bicubic_bezier/tess.vs",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("tessellation/bicubic_bezier/tess.fs",
                                      ifx::ResourceType::SHADER);
    std::string tcs_path =
            resources.GetResourcePath("tessellation/bicubic_bezier/tess.tcs",
                                      ifx::ResourceType::SHADER);
    std::string tes_path =
            resources.GetResourcePath("tessellation/bicubic_bezier/tess.tes",
                                      ifx::ResourceType::SHADER);

    Program* program = CreateProgram(vertex_path, fragment_path,
                                     tcs_path, tes_path);
    return program;
}

Program* ProgramLoader::loadTessellationProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();
    std::string vertex_path =
            resources.GetResourcePath("tessellation/tess.vs",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("tessellation/tess.fs",
                                      ifx::ResourceType::SHADER);
    std::string tcs_path =
            resources.GetResourcePath("tessellation/tess.tcs",
                                      ifx::ResourceType::SHADER);
    std::string tes_path =
            resources.GetResourcePath("tessellation/tess.tes",
                                      ifx::ResourceType::SHADER);

    Program* program = CreateProgram(vertex_path, fragment_path,
                                     tcs_path, tes_path);
    return program;
}

Program* ProgramLoader::loadAllLightProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath("lighting/light_all_vert.glsl",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("lighting/light_all_frag.glsl",
                                      ifx::ResourceType::SHADER);

    Program* program = CreateProgram(vertex_path, fragment_path);

    return program;
}

Program* ProgramLoader::loadAnisotropicLightProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath("lighting/anis_light_vert.glsl",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("lighting/anis_light_frag.glsl",
                                      ifx::ResourceType::SHADER);

    Program* program = CreateProgram(vertex_path, fragment_path);

    return program;
}

Program* ProgramLoader::loadCubemapProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath("lighting/cubemap_vert.glsl",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("lighting/cubemap_frag.glsl",
                                      ifx::ResourceType::SHADER);

    Program* program = CreateProgram(vertex_path, fragment_path);

    return program;
}

Program* ProgramLoader::loadBumpMappingProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath("lighting/bump_vert.glsl",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("lighting/bump_frag.glsl",
                                      ifx::ResourceType::SHADER);

    Program* program = CreateProgram(vertex_path, fragment_path);

    return program;
}

Program *ProgramLoader::loadLampProgram() {
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath("lighting/lamp_vert.glsl",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("lighting/lamp_frag.glsl",
                                      ifx::ResourceType::SHADER);

    Program* program = CreateProgram(vertex_path, fragment_path);

    return program;
}