#ifndef COMPONENT_H
#define COMPONENT_H

#include "Frame.h"

namespace Engine
{ // interface
    class Frame;
    class Component
    { /* data */
    public:
        virtual void run(Frame *super) {}
        virtual void setUp(Frame *super) {}
        virtual void clean(Frame *super) {}
    };
}

#endif;