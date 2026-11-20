#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/modify/GJScoreCell.hpp>
#include <Geode/modify/GJLevelScoreCell.hpp>
#include <Geode/modify/UserCell.hpp>

using namespace geode::prelude;

// Returns true if this account ID belongs to the logged-in player.
static bool isMe(int accountID) {
    auto am = GJAccountManager::get();
    return accountID != 0 && am && accountID == am->m_accountID;
}

// Returns the custom name, or an empty string if the mod is off / no name set.
static std::string getCustomName() {
    auto mod = Mod::get();
    if (!mod->getSettingValue<bool>("enabled")) return "";
    return mod->getSettingValue<std::string>("custom-name");
}

// Profile page (your own profile and when others view yours locally)
class $modify(CNProfilePage, ProfilePage) {
    void loadPageFromUserInfo(GJUserScore* score) {
        if (score && isMe(score->m_accountID)) {
            auto name = getCustomName();
            if (!name.empty()) score->m_userName = name;
        }
        ProfilePage::loadPageFromUserInfo(score);
    }
};

// Comments you posted (shown on levels / profiles)
class $modify(CNCommentCell, CommentCell) {
    void loadFromComment(GJComment* comment) {
        if (comment && isMe(comment->m_accountID)) {
            auto name = getCustomName();
            if (!name.empty()) comment->m_userName = name;
        }
        CommentCell::loadFromComment(comment);
    }
};

// Leaderboards / top players
class $modify(CNScoreCell, GJScoreCell) {
    void loadFromScore(GJUserScore* score) {
        if (score && isMe(score->m_accountID)) {
            auto name = getCustomName();
            if (!name.empty()) score->m_userName = name;
        }
        GJScoreCell::loadFromScore(score);
    }
};

// Level leaderboards
class $modify(CNLevelScoreCell, GJLevelScoreCell) {
    void loadFromScore(GJUserScore* score) {
        if (score && isMe(score->m_accountID)) {
            auto name = getCustomName();
            if (!name.empty()) score->m_userName = name;
        }
        GJLevelScoreCell::loadFromScore(score);
    }
};

// Friends list / user search results
class $modify(CNUserCell, UserCell) {
    void loadFromScore(GJUserScore* score) {
        if (score && isMe(score->m_accountID)) {
            auto name = getCustomName();
            if (!name.empty()) score->m_userName = name;
        }
        UserCell::loadFromScore(score);
    }
};
