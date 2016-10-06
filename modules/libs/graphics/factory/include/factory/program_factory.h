#ifndef PROJECT_PROGRAM_FACTORY_H
#define PROJECT_PROGRAM_FACTORY_H

#include <shaders/program.h>

#include <memory>

namespace ifx {

class ProgramFactory {
public:

    ProgramFactory();

    ~ProgramFactory();

    std::shared_ptr<Program> LoadMainProgram();

    std::shared_ptr<Program> LoadShadowMappingProgram();

    std::shared_ptr<Program> LoadInstancedProgram();

    std::shared_ptr<Program> LoadFBOProgram();
    std::shared_ptr<Program> LoadNormalVisionProgram();

    std::shared_ptr<Program> loadTessellationLODProgram();
    std::shared_ptr<Program> loadTessellationBicubicBezierPolygonProgram();
    std::shared_ptr<Program> loadTessellationBicubicBezierProgram();
    std::shared_ptr<Program> loadTessellationProgram();
    std::shared_ptr<Program> loadCubemapProgram();
    std::shared_ptr<Program> loadAllLightProgram();
    std::shared_ptr<Program> loadAnisotropicLightProgram();
    std::shared_ptr<Program> loadBumpMappingProgram();
    std::shared_ptr<Program> loadLampProgram();
};
}

#endif //PROJECT_PROGRAM_FACTORY_H
