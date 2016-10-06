#ifndef DUCK_PROGRAM_LOADER_H
#define DUCK_PROGRAM_LOADER_H

#include <shaders/program.h>
#include <shaders/loaders/shader_loader.h>

#include <memory>

/*
 * Loads specific shaders compiled into Programs from resources
 */
class ProgramLoader {
public:

    ProgramLoader();
    ~ProgramLoader();

    std::shared_ptr<Program> CreateProgram(std::string vertex_path,
                                           std::string fragment_path);
    std::shared_ptr<Program> CreateProgram(std::string vertex_path,
                                           std::string fragment_path,
                                           std::string geometry_path);
    std::shared_ptr<Program> CreateProgram(std::string vertex_path, 
                                           std::string fragment_path,
                                           std::string tcs_path, 
                                           std::string tes_path);
private:
    ShaderLoader shaderLoader;

};


#endif //DUCK_PROGRAM_LOADER_H
