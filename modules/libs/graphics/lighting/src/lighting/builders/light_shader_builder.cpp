#include "lighting/builders/light_shader_builder.h"
#include <shaders/data/shader_data.h>

using namespace std;

ifx::LightShaderBuilder::LightShaderBuilder(int id){
    this->id = id;
}

ifx::LightShaderBuilder::~LightShaderBuilder() {

}

std::string ifx::LightShaderBuilder::appendToBase(int id,
                                                  const std::string baseName,
                                                  const std::string fieldName) {
    std::string totalField = "";

    totalField += baseName + "[" + to_string(id) + "]" + LIGHT_SEPARATOR;
    totalField += fieldName;

    return totalField;
}
