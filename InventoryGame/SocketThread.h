#include <QThread>
#include <QObject>
#include <QTcpSocket>

class QTcpSocket;

class SocketThread : public QThread
{
	Q_OBJECT
public:
	SocketThread(qintptr descriptor, QObject *parent = 0);
	~SocketThread();
	void run() override;

	private slots:
	//void onConnected();
	void onReadyRead();
	void onDisconnected();

private:
	QTcpSocket *m_socket;
	qintptr m_descriptor;
};