#ifndef PROJECT_PROGRAM_FACTORY_H
#define PROJECT_PROGRAM_FACTORY_H

#include <shaders/program.h>

namespace ifx {

class ProgramFactory {
public:

    ProgramFactory();

    ~ProgramFactory();

    Program* LoadFBOProgram();

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
}

#endif //PROJECT_PROGRAM_FACTORY_H
