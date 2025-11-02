# ============================================================================
# Chat Module
# Manages chat operations
# ============================================================================

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
    Message.h
    Message.cpp
    ChatList.h
    ChatList.cpp
    RecentChat.h
    RecentChat.cpp
    RecentChatList.h
    RecentChatList.cpp
    RecentChatProxyList.h
    RecentChatProxyList.cpp
    ChatManager.h
    ChatManager.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
