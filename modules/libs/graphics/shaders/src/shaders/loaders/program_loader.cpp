#include "shaders/loaders/program_loader.h"

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

    Program* program = new Program(&vertexShader,
                                   &fragmentShader);

    return program;
}

Program* ProgramLoader::CreateProgram(std::string vertex_path,
                                      std::string fragment_path,
                                      std::string geometry_path){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader(vertex_path.c_str());
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader(fragment_path.c_str());
    GeometryShader geometryShader =
            shaderLoader.loadGeometryShader(geometry_path.c_str());

    vertexShader.compile();
    fragmentShader.compile();
    geometryShader.compile();

    Program* program = new Program(&vertexShader,
                                   &fragmentShader,
                                   &geometryShader);

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

    Program* program = new Program(&vertexShader,
                                   &fragmentShader,
                                   nullptr,
                                   &tessControlShader,
                                   &tessEvalShader);

    return program;
}