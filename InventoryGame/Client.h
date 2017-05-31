#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QMainWindow>

class Client : public QObject
{
	Q_OBJECT
public:
	Client(QMainWindow* mParent);
	~Client();
	void start(QString address, quint16 port);
	void stop();
	bool isSocketActive();
	QTcpSocket socket;
	QString clientParamAsString();
	public slots:
	void getInitState();
	void startWrite(QString message);
	void startRead();
private:
	QMainWindow* parentWidg;
	QString ip;
	QString port;
};

#endif