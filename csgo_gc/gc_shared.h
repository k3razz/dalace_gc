#pragma once

#include "gc_message.h"
#include <queue>

class SharedGC
{
public:
    bool HasOutgoingMessages(uint32_t &size);
    bool PopOutgoingMessage(uint32_t &type, void *buffer, uint32_t bufferSize, uint32_t &size);

protected:
    std::queue<GCMessageWrite> m_outgoingMessages;
};
