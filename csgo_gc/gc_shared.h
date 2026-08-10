class SharedGC
{
public:
    bool HasOutgoingMessages(uint32_t &size);
    bool PopOutgoingMessage(uint32_t &type, void *buffer, uint32_t bufferSize, uint32_t &size);

protected:
    std::queue<std::unique_ptr<GCMessageWrite>> m_outgoingMessages;
};