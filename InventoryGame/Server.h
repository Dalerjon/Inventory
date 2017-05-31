#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMainWindow>

class Server : public QObject
{
	Q_OBJECT
public:
	Server(QMainWindow* mParent);
	~Server();
	bool startListen();
	void stop();
	bool isSocketActive();
	QString serverParamAsString();
	QTcpSocket* socket;
	public slots:
	void acceptConnection();
	void connectingError();
	void startRead();
	void startWrite(QString message);
private:
	QTcpServer* server;
	QString ip;
	QString port;
	QMainWindow* parentWidg;
};

#endif
