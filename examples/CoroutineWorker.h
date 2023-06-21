//
// Created by systembug on 23. 6. 14.
//

#ifndef EXAMPLES_COROUTINEWORKER_H
#define EXAMPLES_COROUTINEWORKER_H

#include <napi.h>

namespace alchera::cys {
class CoroutineWorker : public Napi::AsyncWorker {
    public:
        CoroutineWorker() = default;
        virtual ~CoroutineWorker();
        CoroutineWorker(Napi::Env env, const std::string& name);

    public:
        Napi::Promise::Deferred& getDeferred() { return m_deferred; }

    private:
        void Execute() override;
        void OnOK() override;
        void OnError(const Napi::Error &e) override;

    private:
        Napi::Promise::Deferred m_deferred;
        std::string m_statements;
    };
}


#endif //EXAMPLES_COROUTINEWORKER_H
