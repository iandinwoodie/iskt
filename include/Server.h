#ifndef INCLUDE_SERVER_H
#define INCLUDE_SERVER_H

#include <QtCore>
#include <QtNetwork>
#include <string>

class Server : public QObject
{
  Q_OBJECT

  public:
    Server(QObject* parent = nullptr);
    void listen(quint16 port);

  private slots:
    void newConnection(void);
    void disconnected(void);
    void readyRead(void);

  private:
    QTcpServer* server_ = nullptr;
};

#endif//INCLUDE_SERVER_H
