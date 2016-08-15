#include "factory/program_factory.h"

#include <shaders/loaders/program_loader.h>
#include <resources/resources.h>

namespace ifx{

ProgramFactory::ProgramFactory(){

}

ProgramFactory::~ProgramFactory(){

}

Program* ProgramFactory::LoadFBOProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath("fbo/fbo.vs", ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("fbo/fbo.fs", ifx::ResourceType::SHADER);

    ProgramLoader programLoader;
    Program* program = programLoader.CreateProgram(vertex_path, fragment_path);

    return program;
}

Program* ProgramFactory::loadTessellationLODProgram(){
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

    ProgramLoader programLoader;
    Program* program = programLoader.CreateProgram(vertex_path, fragment_path,
                                                   tcs_path, tes_path);
    return program;
}

Program* ProgramFactory::loadTessellationBicubicBezierPolygonProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath
                    ("tessellation/bicubic_bezier/polygon/tess.vs",
                     ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath
                    ("tessellation/bicubic_bezier/polygon/tess.fs",
                     ifx::ResourceType::SHADER);

    ProgramLoader programLoader;
    Program* program = programLoader.CreateProgram(vertex_path, fragment_path);

    return program;
}

Program* ProgramFactory::loadTessellationBicubicBezierProgram(){
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

    ProgramLoader programLoader;
    Program* program = programLoader.CreateProgram(vertex_path, fragment_path,
                                                   tcs_path, tes_path);
    return program;
}

Program* ProgramFactory::loadTessellationProgram(){
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

    ProgramLoader programLoader;
    Program* program = programLoader.CreateProgram(vertex_path, fragment_path,
                                                   tcs_path, tes_path);
    return program;
}

Program* ProgramFactory::loadAllLightProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath("lighting/light_all_vert.glsl",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("lighting/light_all_frag.glsl",
                                      ifx::ResourceType::SHADER);

    ProgramLoader programLoader;
    Program* program = programLoader.CreateProgram(vertex_path, fragment_path);

    return program;
}

Program* ProgramFactory::loadAnisotropicLightProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath("lighting/anis_light_vert.glsl",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("lighting/anis_light_frag.glsl",
                                      ifx::ResourceType::SHADER);

    ProgramLoader programLoader;
    Program* program = programLoader.CreateProgram(vertex_path, fragment_path);

    return program;
}

Program* ProgramFactory::loadCubemapProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath("lighting/cubemap_vert.glsl",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("lighting/cubemap_frag.glsl",
                                      ifx::ResourceType::SHADER);

    ProgramLoader programLoader;
    Program* program = programLoader.CreateProgram(vertex_path, fragment_path);

    return program;
}

Program* ProgramFactory::loadBumpMappingProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath("lighting/bump_vert.glsl",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("lighting/bump_frag.glsl",
                                      ifx::ResourceType::SHADER);

    ProgramLoader programLoader;
    Program* program = programLoader.CreateProgram(vertex_path, fragment_path);

    return program;
}

Program *ProgramFactory::loadLampProgram() {
    ifx::Resources& resources = ifx::Resources::GetInstance();

    std::string vertex_path =
            resources.GetResourcePath("lighting/lamp_vert.glsl",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("lighting/lamp_frag.glsl",
                                      ifx::ResourceType::SHADER);

    ProgramLoader programLoader;
    Program* program = programLoader.CreateProgram(vertex_path, fragment_path);

    return program;
}
}