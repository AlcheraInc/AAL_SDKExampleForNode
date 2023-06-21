//
// Created by systembug on 23. 6. 14.
//

#include "CoroutineWorker.h"
#include <sstream>
#include <iostream>

namespace alchera::cys {
    CoroutineWorker::CoroutineWorker(Napi::Env env, const std::string &str)
        : Napi::AsyncWorker(env)
        , m_deferred(Napi::Promise::Deferred::New(env))
        , m_statements(str)
    {}

    CoroutineWorker::~CoroutineWorker()
    {
        std::cout << "CoroutineWorker is destroyed." << '\n';
    }

    void CoroutineWorker::Execute() {
        std::stringstream str;
        str << "Hello, " << m_statements;
        m_statements = str.str();
    }

    void CoroutineWorker::OnOK() {
        // AsyncWorker::OnOK();
        m_deferred.Resolve(Napi::String::New(Env(), m_statements));
    }

    void CoroutineWorker::OnError(const Napi::Error &e) {
        m_deferred.Reject(e.Value());
    }
}
