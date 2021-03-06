#include <unnecessary/graphics/utility/debugging.h>

namespace un {

    void print_bound_elements() {

        std::cout << "Currently bound targets are:" << std::endl;
        print_bound_target(GL_VERTEX_ARRAY_BUFFER_BINDING, "Vertex Array");
        print_bound_target(GL_ARRAY_BUFFER_BINDING, "Vertex Buffer");
        print_bound_target(GL_ELEMENT_ARRAY_BUFFER_BINDING, "Index Buffer");
    }

    void print_bound_target(uint32_t pName, const std::string &desc) {
        int result;
        glGetIntegerv(pName, &result);
        std::cout << "Target '" << desc << "' bound @ " << result << std::endl;
    }
}

void glClearErrors() {
    while (glGetError() != GLEW_NO_ERROR);
}

void glCheckErrors(const std::string &functionName) {
    uint32_t error;
    while ((error = glGetError()) != GLEW_NO_ERROR) {
        std::cerr << "Error while calling function " << functionName << ": " << std::hex << error << std::dec << std::endl;
    }
}