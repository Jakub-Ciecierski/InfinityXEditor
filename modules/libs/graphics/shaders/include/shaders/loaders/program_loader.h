#ifndef DUCK_PROGRAM_LOADER_H
#define DUCK_PROGRAM_LOADER_H

#include <shaders/program.h>
#include <shaders/loaders/shader_loader.h>

/*
 * Loads specific shaders compiled into Programs from resources
 */
class ProgramLoader {
private:
    ShaderLoader shaderLoader;

    Program* CreateProgram(std::string vertex_path, std::string fragment_path);
    Program* CreateProgram(std::string vertex_path, std::string fragment_path,
                           std::string tcs_path, std::string tes_path);
public:

    ProgramLoader();

    ~ProgramLoader();

    Program* loadTessellationLODProgram();
    Program* loadTessellationBicubicBezierPolygonProgram();
    Program* loadTessellationBicubicBezierProgram();
    Program* loadTessellationProgram();
    Program* loadCubemapProgram();
    Program* loadAllLightProgram();
    Program* loadAnisotropicLightProgram();
    Program* loadBumpMappingProgram();

    Program* loadLampProgram();

};


#endif //DUCK_PROGRAM_LOADER_H
