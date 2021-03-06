#ifndef OPENGL_LAYOUT_H
#define OPENGL_LAYOUT_H

#include <cstdint>
#include <iostream>
#include <vector>

namespace un {
    class LayoutElement {
    private:
        /**
         * The bytes length of a single item.
         */
        uint8_t elementLength;
        /**
         * How many items are in this element.
         */
        uint8_t elementCount;
    public:
        LayoutElement(
                uint8_t elementLength,
                uint8_t elementCount
        );

        uint8_t getElementLength() const;

        uint8_t getCount() const;

        uint8_t getSize() const;

        friend std::ostream &operator<<(std::ostream &os, const LayoutElement &element);
    };


    template<typename E>
    class Layout {
    private:
        std::vector<E> elements;
    public:

        Layout(
                std::initializer_list<E> elements = {}
        ) : elements(elements) {}

        const std::vector<E> &getElements() const {
            return elements;
        }

        uint8_t getStride() const {
            uint8_t s = 0;
            for (auto &e : elements) {
                s += e.getSize();
            }
            return s;
        }


    };
}
#endif
