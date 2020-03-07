#include "Client.h"
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <iostream>

namespace
{
std::string kDashFooter("--------------------------------------------------------------------------------");
std::string kSentHeader("------------------------------------- SENT -------------------------------------");
std::string kRecvHeader("----------------------------------- RECEIVED -----------------------------------");
} // namespace


Client::Client(QObject* parent)
  : QObject(parent), socket_(new QTcpSocket(this))
{
  connect(socket_, SIGNAL(readyRead(void)),
          this, SLOT(readyRead(void)));
  connect(socket_, SIGNAL(error(QAbstractSocket::SocketError)),
          this, SLOT(handleError(QAbstractSocket::SocketError)));
  connect(socket_, SIGNAL(disconnected(void)),
          QCoreApplication::instance(), SLOT(quit(void)));
}

void Client::connectToHost(const std::string& address, quint16 port)
{
  socket_->abort();
  socket_->connectToHost(QString::fromStdString(address), port);
}

void Client::write(const QByteArray& byteArray)
{
  socket_->write(byteArray);

  std::cout << kSentHeader << std::endl;
  qDebug() << byteArray;
  std::cout << kDashFooter << std::endl;
}

void Client::readyRead(void)
{
  std::cout << kRecvHeader << std::endl;
  qDebug() << socket_->readAll();
  std::cout << kDashFooter << std::endl;
}

void Client::handleError(QAbstractSocket::SocketError socketError)
{
  switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        std::cout << "The remote host closed the connection." << std::endl;
        break;
    case QAbstractSocket::HostNotFoundError:
        std::cerr << "The host address was not found." << std::endl;
        break;
    case QAbstractSocket::ConnectionRefusedError:
        std::cerr << "The connection was refused by the peer." << std::endl;
        break;
    default: {
        QString message = QString("The following error occurred: %1.")
            .arg(socket_->errorString());
        std::cerr << message.toStdString() << std::endl;
    }
  }
}
