//
// Created by systembug on 23. 6. 5.
//

#ifndef EXAMPLES_WRAPPER_H
#define EXAMPLES_WRAPPER_H

#include <napi.h>

namespace alchera::cys {
    class Wrapper : public Napi::Addon<Wrapper> {
    };
}



#endif //EXAMPLES_WRAPPER_H
