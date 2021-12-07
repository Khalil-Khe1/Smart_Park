#ifndef CHATSTAFF_H
#define CHATSTAFF_H
#include<QObject>
#include<QHostAddress>
#include<QAbstractSocket>
#include <QTcpSocket>
#include<QDataStream>
#include<QJsonObject>
#include <QJsonDocument>
#include<QSqlQueryModel>
#include <QWidget>
#include<QStandardItemModel>
#include<ui_mainwindow.h>
class ChatStaff : public QObject
{
    Q_OBJECT
     Q_DISABLE_COPY(ChatStaff)
public:
    explicit ChatStaff(QObject *staff = nullptr);
  public slots:
      void connectToServer(const QHostAddress &address, quint16 port);
      void login(const QString &userName);
      void sendMessage(const QString &text);
      void disconnectFromHost();
  private slots:
      void onReadyRead();
  signals:
      void connected();
      void loggedIn();
      void loginError(const QString &reason);
      void disconnected();
      void messageReceived(const QString &sender, const QString &text);
      void error(QAbstractSocket::SocketError socketError);
      void userJoined(const QString &username);
      void userLeft(const QString &username);
  private:
      QTcpSocket *m_clientSocket;
      bool m_loggedIn;
      void jsonReceived(const QJsonObject &doc);
};


#endif // CHATSTAFF_H
