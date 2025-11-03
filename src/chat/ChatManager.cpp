#include "ChatManager.h"
#include "Message.h"
#include "ChatEngine.h"

#include <QApplicationStatic>

Q_APPLICATION_STATIC(ChatManager, _chatManagerInstance)

ChatManager::ChatManager(QObject *parent)
    : QObject(parent)
    , m_userList(new UserList(this))
    , m_userProxyList(new UserProxyList(this))
    , m_mainUser(new User(0, "MeAndYou", this))
    , m_openedChatUser(new User(1,"LLMModel", this))
    , m_chatEngine(new ChatEngine(this))
    , m_lastMessage(nullptr)
{
    connect(this, &ChatManager::sendMessage, this, &ChatManager::onSendMessage, Qt::QueuedConnection);
    connect(this, &ChatManager::sendMessage, this, &ChatManager::onAsk, Qt::QueuedConnection);

    connect(m_chatEngine, &ChatEngine::tokenArrived, this, &ChatManager::onTokenArrived, Qt::QueuedConnection);
    connect(m_chatEngine, &ChatEngine::responseDone, this, &ChatManager::onResponseDone, Qt::QueuedConnection);
    connect(m_chatEngine, &ChatEngine::error, this, &ChatManager::onError);

    m_userProxyList->setSourceModel(m_userList);

    //Test section
    m_chatEngine->load("/home/umbrella/Desktop/models/mistral-7b-instruct-v0.2.Q4_K_M.gguf");

    QTimer* tmr = new QTimer(this);

    tmr->setInterval(15000);

    connect(tmr, &QTimer::timeout, this, [this](){
        emit m_chatEngine->error("");
    });

    //tmr->start();
}

ChatManager *ChatManager::instance()
{
    return _chatManagerInstance();
}

UserList *ChatManager::userList() const
{
    return m_userList;
}

User *ChatManager::openedChatUser() const
{
    return m_openedChatUser;
}

void ChatManager::setOpenedChatUser(User* newOpenedChatUser)
{
    if (m_openedChatUser == newOpenedChatUser)
        return;
    m_openedChatUser = newOpenedChatUser;
    emit openedChatUserChanged();
}

User *ChatManager::mainUser() const
{
    return m_mainUser;
}

void ChatManager::onSendMessage(const QString &message)
{
    if(m_openedChatUser == Q_NULLPTR)
        return;
    m_openedChatUser->addMessage(new Message(message, m_mainUser->ID(), m_openedChatUser));
}

void ChatManager::onAsk(const QString &message)
{
    if(!m_chatEngine->isModelReady() ) {
        qWarning() << "Model is not ready";
        return;
    }

    if(m_lastMessage) {
        qInfo() << "On going response exist";
        return;
    }

    m_openedChatUser->setWriting(true);
    m_chatEngine->send(message);
}

void ChatManager::onTokenArrived(const QString &piece)
{
    if(m_lastMessage) {
        m_lastMessage->appendToContents(piece);
        return;
    }

    m_lastMessage = new Message(piece, m_openedChatUser->ID());
    m_openedChatUser->addMessage(m_lastMessage);
}

void ChatManager::onError(const QString &message)
{
    Q_UNUSED(message)

    if(m_lastMessage) {
        m_openedChatUser->setWriting(false);
        m_lastMessage->setFailed(true);
        m_chatEngine->stop();
    }
}

void ChatManager::onResponseDone()
{
    m_openedChatUser->setWriting(false);
    m_lastMessage = nullptr;
}

void ChatManager::stop()
{
    m_openedChatUser->setWriting(false);
    m_chatEngine->stop();
}

UserProxyList *ChatManager::userProxyList() const
{
    return m_userProxyList;
}
