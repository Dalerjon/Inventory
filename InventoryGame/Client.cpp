#include "stdafx.h"
#include "Client.h"
#include <QHostAddress>
#include "GameWindow.h"
#include "TupleObject.h"
#include <QDomDocument>

Client::Client(QMainWindow* mParent)
{
	parentWidg = mParent;
	connect(&socket, SIGNAL(connected()),
		this, SLOT(getInitState()));
	connect(&socket, SIGNAL(readyRead()),
		this, SLOT(startRead()));
}

Client::~Client()
{
	if (socket.state() == QAbstractSocket::ConnectedState)
		socket.close();
}

void Client::start(QString address, quint16 qport)
{
	QHostAddress addr(address);
	socket.connectToHost(addr, qport);
	qDebug() << socket.waitForConnected();
	if (socket.state() == QAbstractSocket::ConnectedState)
	{
		ip = address;
		port = QString::number(qport);
	}
}

void Client::getInitState()
{
	QString str = "<?xml version = '1.0' encoding='utf-8'?><init></init>";
	socket.write(str.toLatin1());
}

void Client::startWrite(QString message)
{
	
	socket.write(message.toLatin1());
}

void Client::startRead()
{
	//читаем данные из сокета
	QString buffer = "";
	while (socket.bytesAvailable())
	{
		buffer.append(socket.readAll());
		if (buffer.contains("</init>") || buffer.contains("</stop>") || buffer.contains("</start>") || buffer.contains("</close>")
			|| buffer.contains("</object>") || buffer.contains("</list>"))
			break;
	}
	
	qDebug() << buffer;
	GameWindow* gWindow = static_cast<GameWindow*>(parentWidg);

	//флаги для определения комманд
	bool stop = false;
	bool start = false;
	bool close = false;
	bool stopped = false;
	
	//поля объекта
	int row = -1;
	int column = -1;
	QString path;
	QString type;
	int count = 0;

	//кортеж для объекта
	inventoryObject objTuple;
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
		if (root.tagName() == "stopped")
		{
			stopped = true;
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
		gWindow->winClose();
	}
	if (stopped == true)
	{
		QMessageBox::information(NULL, QString(tr("Warning...")),
			QString(tr("Game in server side doesn't started, please wait!")),
			QString(tr("OK")));
		gWindow->menu();
	}
}

bool Client::isSocketActive()
{
	return socket.state() == QTcpSocket::ConnectedState;
}

QString Client::clientParamAsString()
{
	QString str;
	if (isSocketActive())
	{
		str = "Clinet connected to IP = " + ip + ", port = " + port;
		
	}
	else
	{
		str = "Cannot connect to IP = " + ip + ", port = " + port;
		
	}
	return  str;
}

void Client::stop()
{
	socket.close();
}
