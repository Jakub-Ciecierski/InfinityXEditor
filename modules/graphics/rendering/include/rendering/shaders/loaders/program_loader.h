#ifndef DUCK_PROGRAM_LOADER_H
#define DUCK_PROGRAM_LOADER_H

#include <rendering/shaders/program.h>
#include <rendering/shaders/loaders/shader_loader.h>

/*
 * Loads specific shaders compiled into Programs from resources
 */
class ProgramLoader {
private:
    ShaderLoader shaderLoader;
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
