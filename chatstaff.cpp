#include "chatstaff.h"

ChatStaff::ChatStaff(QObject *staff)
    : QObject(staff)
        , m_clientSocket(new QTcpSocket(this))
        , m_loggedIn(false)
{

        connect(m_clientSocket, &QTcpSocket::connected, this, &ChatStaff::connected);
        connect(m_clientSocket, &QTcpSocket::disconnected, this, &ChatStaff::disconnected);

        connect(m_clientSocket, &QTcpSocket::readyRead, this, &ChatStaff::onReadyRead);

        connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ChatStaff::error);

        connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}


void ChatStaff::login(const QString &userName)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected

        QDataStream clientStream(m_clientSocket);

        clientStream.setVersion(QDataStream::Qt_5_7);

        QJsonObject message;
        message["type"] = QStringLiteral("login");
        message["username"] = userName;

        clientStream << QJsonDocument(message).toJson();
    }
}

void ChatStaff::sendMessage(const QString &text)
{
    if (text.isEmpty())
        return;

    QDataStream clientStream(m_clientSocket);

    clientStream.setVersion(QDataStream::Qt_5_7);

    QJsonObject message;
    message["type"] = QStringLiteral("message");
    message["text"] = text;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
}
void ChatStaff::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}
void ChatStaff::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address, port);
}
void ChatStaff::jsonReceived(const QJsonObject &docObj)
{

    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0) { //It's a login message
        if (m_loggedIn)
            return;
        const QJsonValue resultVal = docObj.value(QLatin1String("success"));
        if (resultVal.isNull() || !resultVal.isBool())
            return;
        const bool loginSuccess = resultVal.toBool();
        if (loginSuccess) {

            emit loggedIn();
            return;
        }

        const QJsonValue reasonVal = docObj.value(QLatin1String("reason"));
        emit loginError(reasonVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0) { //It's a chat message

        const QJsonValue textVal = docObj.value(QLatin1String("text"));

        const QJsonValue senderVal = docObj.value(QLatin1String("sender"));
        if (textVal.isNull() || !textVal.isString())
            return;
        if (senderVal.isNull() || !senderVal.isString())
            return;

        emit messageReceived(senderVal.toString(), textVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("newuser"), Qt::CaseInsensitive) == 0) { // A user joined the chat

        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return;

        emit userJoined(usernameVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("userdisconnected"), Qt::CaseInsensitive) == 0) { // A user left the chat

        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return;
        emit userLeft(usernameVal.toString());
    }
}
void ChatStaff::onReadyRead()
{

    QByteArray jsonData;

    QDataStream socketStream(m_clientSocket);

    socketStream.setVersion(QDataStream::Qt_5_7);

    for (;;) {

        socketStream.startTransaction();

        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {

            QJsonParseError parseError;

            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {

                if (jsonDoc.isObject())
                    jsonReceived(jsonDoc.object());
            }

        } else {

            break;
        }
    }
}

