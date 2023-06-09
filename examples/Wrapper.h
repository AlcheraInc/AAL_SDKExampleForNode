//
// Created by systembug on 23. 6. 5.
//

#ifndef EXAMPLES_WRAPPER_H
#define EXAMPLES_WRAPPER_H

#include <napi.h>
#include <thread>

void callJS(Napi::Env env, Napi::Function callback, Napi::Reference<Napi::Value>* context, uint32_t* data) {
    if (env != nullptr) {
        if (callback != nullptr) {
            callback.Call(context->Value(), {Napi::Number::New(env, *data)});
        }
    }

    delete data;
}

namespace alchera::cys {
    class Wrapper : public Napi::Addon<Wrapper> {
    public:
        Wrapper() = default;
        Wrapper(Napi::Env env, Napi::Object exports);
        Wrapper(const Wrapper& wrapper) = delete;
        Wrapper(Wrapper&& wrapper) noexcept;
        virtual ~Wrapper() = default;

    public:
        Napi::Value testNum(const Napi::CallbackInfo& info);
        Napi::Value testStr(const Napi::CallbackInfo& info);
        Napi::Value testArr(const Napi::CallbackInfo& info);
        Napi::Value testSetSimpleCallback(const Napi::CallbackInfo& info);
        Napi::Value testRunSimpleCallback(const Napi::CallbackInfo& info);
        Napi::Value testTimer(const Napi::CallbackInfo& info);
        Napi::Value testCoroutine(const Napi::CallbackInfo& info); // not implemented yet

    private:
        std::thread                                                                                 m_nativeThread;
        Napi::ThreadSafeFunction                                                                    m_simpleCallback;
        Napi::TypedThreadSafeFunction<Napi::Reference<Napi::Value>, uint32_t, callJS>                m_timerCallback;
        bool                                                                                        m_setSimpleCallback;

    };

    NODE_API_ADDON(Wrapper)
}



#endif //EXAMPLES_WRAPPER_H

