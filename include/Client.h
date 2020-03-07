#ifndef INCLUDE_CLIENT_H
#define INCLUDE_CLIENT_H

#include <QtCore>
#include <QtNetwork>
#include <string>

class Client : public QObject
{
  Q_OBJECT

  public:
    Client(QObject* parent = nullptr);
    void connectToHost(const std::string& address, quint16 port);
    void write(const QByteArray& byteArray);

  private slots:
    void readyRead(void);
    void handleError(QAbstractSocket::SocketError socketError);

  private:
    QTcpSocket* socket_ = nullptr;
};

#endif//INCLUDE_CLIENT_H
