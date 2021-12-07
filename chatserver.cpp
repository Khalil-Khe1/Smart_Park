#include "chatserver.h"

void ChatServer::incomingConnection(qintptr socketDescriptor)
{

    ServerWorker *worker = new ServerWorker(this);

    if (!worker->setSocketDescriptor(socketDescriptor)) {

        worker->deleteLater();
        return;
    }

    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));
    connect(worker, &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));
    connect(worker, &ServerWorker::jsonReceived, this, std::bind(&ChatServer::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);

    m_clients.append(worker);

    emit logMessage(QStringLiteral("New client Connected"));
}

void ChatServer::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    destination->sendJson(message);
}

void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{

    for (ServerWorker *worker : m_clients) {
        if (worker == exclude)
            continue;
        sendJson(worker, message);
    }
}
