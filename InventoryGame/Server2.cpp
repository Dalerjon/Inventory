#include "stdafx.h"
#include "Server2.h"


Server::Server(QObject *parent) : QTcpServer(parent) {
	
}

Server::~Server() {
	//_socket.disconnectFromHost();
	//_socket.waitForDisconnected();
}

//void Server::startRead() {
//	QByteArray array = _socket.read(_socket.bytesAvailable());
//}



bool Server::startListen() {
	QHostAddress ipAddress;
	
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
		for (int i = 0; i < ipAddressesList.size(); ++i) {
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address()) {
			ipAddress = ipAddressesList.at(i);
			break;
		}
	}
	
	if (this->listen(ipAddress, 2323)) 
	{
			qDebug() << "Server start at ip: " << ipAddress.toString();
		qDebug() << "Server start at port: " << this->serverPort();
	}
	else 
	{
		qDebug() << "Start failure";
	
	}
	qApp->processEvents();
	return true;
}

void Server::incomingConnection(qintptr handle){

	qDebug() << Q_FUNC_INFO << " new connection";
	SocketThread *socket = new SocketThread(handle);

	connect(socket, SIGNAL(finished()), socket, SLOT(deleteLater()));
	socket->start();
}

//void Server::startWrite(QString message)
//{
	//if (_socket != nullptr)
//		_socket.write(message.toLatin1());
//}

//bool Server::isSocketActive()
//{
//	if (_socket.isValid())
//		return _socket.state() == QTcpSocket::ConnectedState;
//	return false;
//}