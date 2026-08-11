#pragma once

#include "config.h"
#include "gc_shared.h"
#include "inventory.h"
#include "networking_client.h"

struct MicroTxnAuthorizationResponse_t;
class ServerGC;

struct Transaction
{
    uint64_t id;
    std::vector<uint64_t> itemIds;
};

class ClientGC final : public SharedGC
{
public:
    ClientGC(uint64_t steamId, ISteamNetworking *networking);
    ~ClientGC();

    void HandleMessage(uint32_t type, const void *data, uint32_t size);

    void Update();

    bool GetMicroTransactionResponse(MicroTxnAuthorizationResponse_t &response);

    void SendSOCacheToGameSever();
    void HandleNetMessage(GCMessageRead &messageRead);

    void SetListenServer(ServerGC *serverGC, uint64_t serverSteamId);

    void SetAuthTicket(uint32_t handle, const void *data, uint32_t size);
    void ClearAuthTicket(uint32_t handle);

private:
    void SendMessageToGame(bool sendToGameServer, uint32_t type,
        const google::protobuf::MessageLite &message, uint64_t jobId = JobIdInvalid);

    void OnClientHello(GCMessageRead &messageRead);
    void AdjustItemEquippedState(GCMessageRead &messageRead);
    void ClientPlayerDecalSign(GCMessageRead &messageRead);
    void UseItemRequest(GCMessageRead &messageRead);
    void ClientRequestJoinServerData(GCMessageRead &messageRead);
    void SetItemPositions(GCMessageRead &messageRead);
    void IncrementKillCountAttribute(GCMessageRead &messageRead);
    void ApplySticker(GCMessageRead &messageRead);
    void StoreGetUserData(GCMessageRead &messageRead);
    void StorePurchaseInit(GCMessageRead &messageRead);
    void StorePurchaseFinalize(GCMessageRead &messageRead);

    void UnlockCrate(GCMessageRead &messageRead);
    void EconPreviewDataBlockRequest(GCMessageRead &messageRead);
    void NameItem(GCMessageRead &messageRead);
    void NameBaseItem(GCMessageRead &messageRead);
    void RemoveItemName(GCMessageRead &messageRead);

    void BuildMatchmakingHello(CMsgGCCStrike15_v2_MatchmakingGC2ClientHello &message);
    void BuildClientWelcome(CMsgClientWelcome &message, const CMsgCStrike15Welcome &csWelcome,
        const CMsgGCCStrike15_v2_MatchmakingGC2ClientHello &matchmakingHello);
    void SendRankUpdate();

    void MonitorInventoryFile();
    void MonitorConfigFile();

    int XPForLevel(int level) const;
    bool IsMatchEnded() const;
    void OnMatchEnd();

    uint32_t AccountId() const { return m_steamId & 0xffffffff; }

    const uint64_t m_steamId;
    NetworkingClient m_networking;

    GCConfig m_config;
    Inventory m_inventory;

    Transaction m_transaction{};

    uint64_t m_inventoryLastWriteTime{ 0 };
    uint64_t m_configLastWriteTime{ 0 };

    bool m_matchInProgress{ false };
    uint64_t m_matchStartTime{ 0 };
};