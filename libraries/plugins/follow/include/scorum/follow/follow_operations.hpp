#pragma once

#include <scorum/protocol/base.hpp>

#include <scorum/follow/follow_plugin.hpp>

namespace scorum {
namespace follow {

using scorum::protocol::base_operation;

struct follow_operation : base_operation
{
    account_name_type follower;
    account_name_type following;
    std::set<std::string> what; /// blog, mute

    void validate() const;

    void get_required_posting_authorities(flat_set<account_name_type>& a) const
    {
        a.insert(follower);
    }
};

struct reblog_operation : base_operation
{
    account_name_type account;
    account_name_type author;
    std::string permlink;

    void validate() const;

    void get_required_posting_authorities(flat_set<account_name_type>& a) const
    {
        a.insert(account);
    }
};

typedef fc::static_variant<follow_operation, reblog_operation> follow_plugin_operation;

DEFINE_PLUGIN_EVALUATOR(follow_plugin, follow_plugin_operation, follow);
DEFINE_PLUGIN_EVALUATOR(follow_plugin, follow_plugin_operation, reblog);
}
} // scorum::follow

FC_REFLECT(scorum::follow::follow_operation, (follower)(following)(what))
FC_REFLECT(scorum::follow::reblog_operation, (account)(author)(permlink))

DECLARE_OPERATION_TYPE(scorum::follow::follow_plugin_operation)

FC_REFLECT_TYPENAME(scorum::follow::follow_plugin_operation)
