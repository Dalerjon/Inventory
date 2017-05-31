#include <QtNetwork>
#include <QMessageBox>
#include "SocketThread.h"

class Server : public QTcpServer {
	Q_OBJECT
public:
	explicit Server(QObject *parent = 0);
	~Server();
	//bool isSocketActive();
	//QTcpSocket _socket;
	//public slots:
	//void startRead();
	bool startListen();
	//void startWrite(QString message);
protected:
	void incomingConnection(qintptr socketDescriptor) override;
};

