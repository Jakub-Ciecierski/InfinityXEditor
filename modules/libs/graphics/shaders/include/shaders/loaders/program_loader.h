#ifndef DUCK_PROGRAM_LOADER_H
#define DUCK_PROGRAM_LOADER_H

#include <shaders/program.h>
#include <shaders/loaders/shader_loader.h>

/*
 * Loads specific shaders compiled into Programs from resources
 */
class ProgramLoader {
private:

public:

    ProgramLoader();

    ~ProgramLoader();

    ShaderLoader shaderLoader;

    Program* CreateProgram(std::string vertex_path, std::string fragment_path);
    Program* CreateProgram(std::string vertex_path,
                           std::string fragment_path,
                           std::string geometry_path);
    Program* CreateProgram(std::string vertex_path, std::string fragment_path,
                           std::string tcs_path, std::string tes_path);
};


#endif //DUCK_PROGRAM_LOADER_H
