//
// Created by systembug on 23. 6. 5.
//

#include "Wrapper.h"
#include <memory>
#include <chrono>

namespace alchera::cys {
    Wrapper::Wrapper(Napi::Env env, Napi::Object exports)
        : m_setSimpleCallback(false)
    {
        DefineAddon(exports, {
            InstanceMethod("testNum", &Wrapper::testNum),
            InstanceMethod("testStr", &Wrapper::testStr),
            InstanceMethod("testArr", &Wrapper::testArr),
            InstanceMethod("testSetSimpleCallback", &Wrapper::testSetSimpleCallback),
            InstanceMethod("testRunSimpleCallback", &Wrapper::testRunSimpleCallback),
            InstanceMethod("testTimer", &Wrapper::testTimer)
        });
    }

    Wrapper::Wrapper(Wrapper&& wrapper) noexcept
        : m_setSimpleCallback(wrapper.m_setSimpleCallback)
    {

    }

    Napi::Value Wrapper::testNum(const Napi::CallbackInfo& info)
    {
        auto env = info.Env();
        if (info.Length() > 1) {
            Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
            return env.Null();
        }

        if (!info[0].IsNumber()) {
            Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
            return env.Null();
        }

        auto sum = 0;
        sum += info[0].As<Napi::Number>().Int32Value();
        return Napi::Number::New(env, sum);
    }

    Napi::Value Wrapper::testStr(const Napi::CallbackInfo& info)
    {
        std::string str = "TEST";
        return Napi::String::New(info.Env(), str);
    }

    Napi::Value Wrapper::testArr(const Napi::CallbackInfo& info)
    {
        auto env = info.Env();
        if (info.Length() > 1) {
            Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
            return env.Null();
        }

        if (!info[0].IsArray()) {
            Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
            return env.Null();
        }

        auto arrLength = info[0].As<Napi::Array>().Length();
        auto arr = info[0].As<Napi::Array>();
        for (auto i = 0; i < arrLength; ++i) {
            auto val = arr.Get(i).As<Napi::Number>().FloatValue() + 11.1;
            arr.Set(i, Napi::Number::New(env, val));
        }

        return arr;
    }

    Napi::Value Wrapper::testSetSimpleCallback(const Napi::CallbackInfo& info)
    {
        auto env = info.Env();
        if (info.Length() > 1) {
            Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
            return env.Null();
        }

        if (!info[0].IsFunction()) {
            Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
            return env.Null();
        }

        auto function = info[0].As<Napi::Function>();
        m_simpleCallback = Napi::ThreadSafeFunction::New(env, function, "callback", 0, 1);
        m_setSimpleCallback = true;
        return Napi::String::New(env, "Done");
    }

    Napi::Value Wrapper::testRunSimpleCallback(const Napi::CallbackInfo& info)
    {
        auto env = info.Env();
        if (!m_setSimpleCallback) {
            Napi::TypeError::New(env, "Callback was not set.").ThrowAsJavaScriptException();
            return env.Null();
        }

        auto napiStatus = m_simpleCallback.NonBlockingCall();
        auto timeoutCnt = 5;
        while (napiStatus == napi_queue_full && timeoutCnt > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            napiStatus = m_simpleCallback.NonBlockingCall();
            --timeoutCnt;
        }

        if (timeoutCnt < 0) {
            Napi::TypeError::New(env, "Timeout").ThrowAsJavaScriptException();
            return env.Null();
        }

        m_simpleCallback.Release();
        m_setSimpleCallback = false;
        return Napi::String::New(env, "Done");
    }

    Napi::Value Wrapper::testTimer(const Napi::CallbackInfo& info)
    {
        auto env = info.Env();
        if (info.Length() < 2) {
            Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
            return env.Null();
        }

        if (!info[0].IsFunction()) {
            Napi::TypeError::New(env, "Wrong arguments as function").ThrowAsJavaScriptException();
            return env.Null();
        }

        if (!info[1].IsNumber()) {
            Napi::TypeError::New(env, "Wrong arguments as number").ThrowAsJavaScriptException();
            return env.Null();
        }

        auto count = info[1].As<Napi::Number>().Int32Value();
        auto context = new Napi::Reference<Napi::Value>(Napi::Persistent(info.This()));

        m_timerCallback = Napi::TypedThreadSafeFunction<Napi::Reference<Napi::Value>, uint32_t, callJS>::New(
                env, info[0].As<Napi::Function>(), "Test", 0, 1, context,
                [this](Napi::Env, void*, Napi::Reference<Napi::Value>* ctx) {
                    m_nativeThread.join();
                    delete ctx;
                });

        m_nativeThread = std::thread([this, count] {
            for (auto i = 0; i < count; ++i) {
                auto now = std::chrono::system_clock::now();
                auto epoch = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch();
                auto value = new uint32_t(epoch.count());
                auto status = m_timerCallback.BlockingCall(value);
                if (status != napi_ok)
                    break;

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            m_timerCallback.Release();
        });

        return Napi::Boolean::New(env, true);
    }

    Napi::Value Wrapper::testCoroutine(const Napi::CallbackInfo& info)
    {
        // TODO: implement with coroutine
        return info.Env().Null();
    }
}