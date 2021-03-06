#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <cstdint>
#include <utility>
#include <vector>
#include <streambuf>
#include <filesystem>
#include <fstream>
#include <unnecessary/graphics/utility/layout.h>
#include <GL/glew.h>

#include <ostream>
#include <unnecessary/graphics/utility/debugging.h>

namespace un {
    class ShaderElement : LayoutElement {
    private:
        GLenum type;
    public:
        ShaderElement(
                uint8_t elementLength,
                uint8_t elementCount,
                GLenum type
        );

        GLenum getType() const;

        friend std::ostream &operator<<(std::ostream &os, const ShaderElement &element);
    };

    typedef Layout <un::ShaderElement> ShaderLayout;

    class ShaderSource {
    private:
        std::string source;
        un::ShaderLayout layout;

        static bool checkCompileStatus(uint32_t id);

        static void showCompileError(uint32_t id);

    public:
        ShaderSource(
                std::string source,
                ShaderLayout layout
        );

        static ShaderSource from(
                const std::filesystem::path &path,
                const ShaderLayout &layout
        );

        uint32_t exportShader(GLenum type) const;
    };

    class Shader {
    private:
        ShaderSource vertex, fragment;
        ShaderSource *geometry;
    public:
        Shader(
                ShaderSource vertex,
                ShaderSource fragment,
                ShaderSource *geometry = nullptr
        ) : vertex(std::move(vertex)), fragment(std::move(fragment)), geometry(std::move(geometry)) {

        }

        const ShaderSource &getVertex() const;

        const ShaderSource &getFragment() const;

        ShaderSource *getGeometry() const;

        static Shader from(
                const std::filesystem::path &vertexPath,
                const ShaderLayout &vertexLayout,
                const std::filesystem::path &fragmentPath,
                const ShaderLayout &fragmentLayout
        );

        static Shader from(
                const std::filesystem::path &vertexPath,
                const ShaderLayout &vertexLayout,
                const std::filesystem::path &fragmentPath,
                const ShaderLayout &fragmentLayout,
                const std::filesystem::path &geometryPath,
                const ShaderLayout &geometryLayout
        );

    };
}
#endif
