#ifndef DUCK_LIGHT_SHADER_BUILDER_H
#define DUCK_LIGHT_SHADER_BUILDER_H

#include <string>

namespace ifx {

    /*
     * Abstract Class for building strings for shader binding
     */
    class LightShaderBuilder {
    protected:
        int id;

    public:

        LightShaderBuilder(int id);

        virtual ~LightShaderBuilder();

        std::string appendToBase(int id,
                                 const std::string baseName,
                                 const std::string fieldName);

        virtual void build() = 0;
    };
}

#endif //DUCK_LIGHT_SHADER_BUILDER_H
