#pragma once

#include <QString>
#include <QUrl>

#include <atomic>
#include <vector>
#include <string>

#include "llama.h"

class LlamaEngine;

class LlamaEnginePrivate
{
public:
    explicit LlamaEnginePrivate(LlamaEngine* qptr);

    void unloadAll();
    void ensureSampler();
    std::string buildPromptFromChat(const std::string& user);
    void clearMessages();

    LlamaEngine* const q;

    llama_model* model;
    llama_context* ctx;
    llama_sampler* smpl;

    const llama_vocab* vocab;

    std::vector<llama_chat_message> messages;
    std::vector<char> formatted;

    std::atomic<bool> cancel;

    int nCtx;
    int nGpuLayers;
    QUrl modelPath;
};
