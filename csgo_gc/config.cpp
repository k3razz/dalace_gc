#include "stdafx.h"
#include "config.h"
#include "keyvalue.h"
#include "random.h"

constexpr const char *ConfigFilePath = "csgo_gc/config.txt";

GCConfig::GCConfig()
{
    KeyValue config{ "config" };

    if (!config.ParseFromFile(ConfigFilePath))
    {
        return;
    }

    const KeyValue *ranks = config.GetSubkey("ranks");
    if (ranks)
    {
        m_competitiveRank = ranks->GetNumber("competitive_rank", m_competitiveRank);
        m_competitiveWins = ranks->GetNumber("competitive_wins", m_competitiveWins);

        m_wingmanRank = ranks->GetNumber("wingman_rank", m_wingmanRank);
        m_wingmanWins = ranks->GetNumber("wingman_wins", m_wingmanWins);

        m_dangerZoneRank = ranks->GetNumber("dangerzone_rank", m_dangerZoneRank);
        m_dangerZoneWins = ranks->GetNumber("dangerzone_wins", m_dangerZoneWins);
    }

    m_destroyUsedItems = config.GetNumber("destroy_used_items", m_destroyUsedItems);

    const KeyValue *rarityWeights = config.GetSubkey("rarity_weights");
    if (rarityWeights)
    {
        m_rarityWeights.clear();
        m_rarityWeights.reserve(rarityWeights->SubkeyCount());

        for (const KeyValue &subkey : *rarityWeights)
        {
            RarityWeight weight;
            weight.rarity = FromString<uint32_t>(subkey.Name());
            weight.weight = FromString<float>(subkey.String());
            m_rarityWeights.push_back(weight);
        }
    }

    m_vacBanned = config.GetNumber("vac_banned", m_vacBanned);
    m_commendedFriendly = config.GetNumber("cmd_friendly", m_commendedFriendly);
    m_commendedTeaching = config.GetNumber("cmd_teaching", m_commendedTeaching);
    m_commendedLeader = config.GetNumber("cmd_leader", m_commendedLeader);
    m_level = config.GetNumber("player_level", m_level);
    m_xp = config.GetNumber("player_cur_xp", m_xp);
}

float GCConfig::GetRarityWeight(uint32_t rarity) const
{
    for (const RarityWeight &weight : m_rarityWeights)
    {
        if (weight.rarity == rarity)
        {
            return weight.weight;
        }
    }

    return 0;
}

void GCConfig::WriteToFile() const
{
    KeyValue config{ "config" };
    
    KeyValue &ranks = config.AddSubkey("ranks");
    ranks.AddNumber("competitive_rank", m_competitiveRank);
    ranks.AddNumber("competitive_wins", m_competitiveWins);
    ranks.AddNumber("wingman_rank", m_wingmanRank);
    ranks.AddNumber("wingman_wins", m_wingmanWins);
    ranks.AddNumber("dangerzone_rank", m_dangerZoneRank);
    ranks.AddNumber("dangerzone_wins", m_dangerZoneWins);
    
    config.AddNumber("destroy_used_items", m_destroyUsedItems);
    config.AddNumber("vac_banned", m_vacBanned);
    config.AddNumber("cmd_friendly", m_commendedFriendly);
    config.AddNumber("cmd_teaching", m_commendedTeaching);
    config.AddNumber("cmd_leader", m_commendedLeader);
    config.AddNumber("player_level", m_level);
    config.AddNumber("player_cur_xp", m_xp);
    
    KeyValue &rarityWeights = config.AddSubkey("rarity_weights");
    for (const RarityWeight &rw : m_rarityWeights)
    {
        rarityWeights.AddNumber(std::to_string(rw.rarity), rw.weight);
    }
    
    config.WriteToFile(ConfigFilePath);
}