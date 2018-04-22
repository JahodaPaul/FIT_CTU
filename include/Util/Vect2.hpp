#pragma once

namespace RG {
    /**
     * \class Vect2f
     * \brief
     */
    //TODO create conversion to sfml and box2d vectors
    template<class T>
    struct Vect2
    {
        T x, y;
    };

    typedef Vect2<int> Vect2i;
    typedef Vect2<unsigned int> Vect2u;
    typedef Vect2<float> Vect2f;
}
