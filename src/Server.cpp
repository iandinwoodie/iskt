#include "Server.h"
#include <stdexcept>
#include <iostream>

namespace
{
std::string kDashFooter("--------------------------------------------------------------------------------");
std::string kRecvHeader("----------------------------------- RECEIVED -----------------------------------");
} // namespace

Server::Server(QObject* parent)
  : QObject(parent), server_(new QTcpServer(this))
{
  connect(server_, SIGNAL(newConnection(void)),
          this, SLOT(newConnection(void)));
}

void Server::listen(quint16 port)
{
  if (!server_->listen(QHostAddress::Any, port)) {
    throw std::runtime_error(
        QString("Unable to start server: %1")
            .arg(server_->errorString())
            .toStdString());
  }
  qDebug() << "listening locally on port:" << port;
}

void Server::newConnection(void)
{
  while (server_->hasPendingConnections()) {
    qDebug() << "fetching next connection";
    QTcpSocket *socket = server_->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
  }
}

void Server::disconnected(void)
{
  qDebug() << "disconnected from a client";
  QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
  socket->deleteLater();
}

void Server::readyRead(void)
{
  QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
  QByteArray data = socket->readAll();
  std::cout << kRecvHeader << std::endl;
  qDebug() << data;
  std::cout << kDashFooter << std::endl;
  socket->disconnectFromHost();
}
