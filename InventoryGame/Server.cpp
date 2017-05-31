#include "stdafx.h"
#include "Server.h"
#include "GameWindow.h"
#include "TupleObject.h"
#include <QDomDocument>

using namespace std;

Server::Server(QMainWindow* mParent)
{
	parentWidg = mParent;
}

Server::~Server()
{
	server->close();
}

void Server::acceptConnection()
{
	socket = server->nextPendingConnection();

	connect(socket, SIGNAL(readyRead()),
		this, SLOT(startRead()));
}

void Server::startRead()
{
	//читаем данные из сокета
	QString buffer = "";
	while (socket->bytesAvailable())
	{
		buffer.append(socket->readAll());
		if (buffer.contains("</init>") || buffer.contains("</stop>") || buffer.contains("</start>") || buffer.contains("</close>")
			|| buffer.contains("</object>") || buffer.contains("</list>"))
			break;
	}
	
	qDebug() << buffer;
	GameWindow* gWindow = static_cast<GameWindow*>(parentWidg);
	
	//флаги для определения комманд
	bool init = false;
	bool stop = false;
	bool start = false;
	bool close = false;

	//поля объекта
	int row = -1;
	int column = -1;
	QString path;
	QString type;
	int count = 0;

	//кортеж для объекта
	inventoryObject objTuple;
	std::vector<inventoryObject> objList;

	QDomDocument doc;
	QDomElement root;
	QDomNode node;
	//парсим данные, формат xml	
	if (!buffer.contains("<object>"))
	{
		//проверяем команды
		doc.setContent(buffer);
		qDebug() << doc.toString();
		root = doc.documentElement();
		if (root.tagName() == "init")
		{
			init = true;
		}
		if (root.tagName() == "stop")
		{
			stop = true;
		}
		if (root.tagName() == "start")
		{
			start = true;
		}
		if (root.tagName() == "close")
		{
			close = true;
		}
	}
	else
	{
		//проверяем имеетли буффер несколько команд, если да, то разделяем их
		QStringList list = buffer.split("<?xml");
		qDebug() << list.count();
		for (auto listItem : list)
		{
			if (!listItem.isEmpty())
			{
				//так как во время деления на команды структура xml была нарушена, то добавляем удаленный фрагмент обратно
				QString command = QString("<?xml") + listItem;
				qDebug() << command;
				doc.setContent(command);
				qDebug() << doc.toString();
				root = doc.documentElement();
				node = root.firstChild();
				while (!node.isNull()) {
					if (node.toElement().tagName() == "row")
					{
						row = node.firstChild().toText().data().toInt();
					}
					if (node.toElement().tagName() == "column")
					{
						column = node.firstChild().toText().data().toInt();
					}
					if (node.toElement().tagName() == "path")
					{
						path = node.firstChild().toText().data();
					}
					if (node.toElement().tagName() == "type")
					{
						type = node.firstChild().toText().data();
					}
					if (node.toElement().tagName() == "count")
					{
						count = node.firstChild().toText().data().toInt();
					}
					node = node.nextSibling();
				}
				if (row != -1 && column != -1)
				{
					objTuple = std::make_tuple(row, column, path, type, count);
					gWindow->invTableWidget->updateTable(objTuple);
				}
			}
		}
	}
	
	if (init == true)
	{
		if (!gWindow->gamePanelWidget->isEnabled())
		{
			QString message = "<?xml version = '1.0' encoding='utf-8'?><stopped></stopped>";
			socket->write(message.toLatin1());
		}
		if (!gWindow->invTableWidget->inv.isInventoryEmpty<Subject>())
		{
			QString message = gWindow->invTableWidget->inv.inventoryToXmlString();
			socket->write(message.toLatin1());
		}
	}
	if (stop == true)
	{
		gWindow->menu();
	}
	if (start == true)
	{
		gWindow->start();
	}
	if (close == true)
	{
		QMessageBox::information(NULL, QString(tr("Warning...")),
			QString(tr("Client is disconnected! Server is running as standalone.")),
			QString(tr("OK")));
		socket->close();
	}
}

void Server::startWrite(QString message)
{
	if (socket != nullptr)
		socket->write(message.toLatin1());
}

bool Server::startListen() {
	QHostAddress ipAddress;
	server = new QTcpServer();
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	for (int i = 0; i < ipAddressesList.size(); ++i) {
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address()) {
			ipAddress = ipAddressesList.at(i);
			break;
		}
	}

	if (server->listen(ipAddress, 2323))
	{
		connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
		connect(server, SIGNAL(acceptError()), this, SLOT(connectingError()));
		ip = ipAddress.toString();
		port = "2323";
		qDebug() << "Server start at ip: " << ipAddress.toString();
		qDebug() << "Server start at port: " << server->serverPort();
	}
	else
	{
		qDebug() << "Start failure";

	}
	return true;
}

void Server::stop()
{
	server->close();
}

bool Server::isSocketActive()
{
	if (socket != nullptr)
		return socket->state() == QTcpSocket::ConnectedState;
	return false;
}

void  Server::connectingError()
{
	qDebug() << "Cannot create connection!";
}

QString  Server::serverParamAsString()
{
	QString str;
	
	if (!ip.isEmpty())
	{
		str = "Server started at IP = " + ip + ", port = " + port;
	}
	else
	{
		str = "Ops, cannot start the server! Game started as standalone";
	}
	return str;
}