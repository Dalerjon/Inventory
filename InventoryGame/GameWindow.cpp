#include "stdafx.h"
#include <chrono>
#include <thread>
#include "GameWindow.h"
#include <QImageReader>
#include <QDebug>


GameWindow::GameWindow(bool cIsServer, QString* cIp)
{
	setupUi(this);
	gamePanelWidget->setDisabled(true);
	
	//����������� ���������
	invTableWidget->horizontalHeader()->setDefaultSectionSize(150);
	invTableWidget->verticalHeader()->setDefaultSectionSize(150);
	invTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	invTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	invTableWidget->setAcceptDrops(true);
	invTableWidget->setDragDropMode(QAbstractItemView::DragDrop);
	invTableWidget->setDropIndicatorShown(true);
	invTableWidget->initTable();

	objTableWidget->horizontalHeader()->setDefaultSectionSize(150);
	objTableWidget->verticalHeader()->setDefaultSectionSize(150);
	objTableWidget->setDragDropMode(QAbstractItemView::DragOnly);
	objTableWidget->initTable();

	//������� ���������� ����� ��������� � �������
	createConnections();
	
	//��������� ����� ������� ��� �������  � ����������� �� ������ ������
	isServer = cIsServer;
	ip = cIp;
	
	if (isServer == true)
	{
		server = new Server(this);
		server->startListen();
		statusLb->setText(server->serverParamAsString());
	}
}

GameWindow::~GameWindow()
{
	
}

void GameWindow::createConnections()
{
	//���������� ����� ��������� � �������
	QObject::connect(startBtn, &QPushButton::released, this, &GameWindow::startGame);
	QObject::connect(closeBtn, &QPushButton::released, this, &GameWindow::closeWindow);
	QObject::connect(menuBtn, &QPushButton::released, this, &GameWindow::showMenu);
}

void GameWindow::startGame()
{
	//������ �������� ������� ����
	gamePanelWidget->setDisabled(false);
	invTableWidget->clearTable();
	if (isServer == false)
	{
		if (client == NULL)
		{
			client = new Client(this);
			client->start(*ip, 2323);
			statusLb->setText(client->clientParamAsString());
		}
		else
		{
			QString str = "<?xml version = '1.0' encoding='utf-8'?><start></start>";
			client->socket.write(str.toLatin1());
		}
	}
	else
	{
		if (server->isSocketActive())
		{
			QString str = "<?xml version = '1.0' encoding='utf-8'?><start></start>";
			server->socket->write(str.toLatin1());
		}			
	}
	likeCollapce(true);
}

void GameWindow::showMenu()
{
	//���������� ������� ����
	likeCollapce(false);
	gamePanelWidget->setDisabled(true);
	if (isServer == false)
	{
		QString str = "<?xml version = '1.0' encoding='utf-8'?><stop></stop>";
		client->socket.write(str.toLatin1());
	}
	else
	{
		if (server->isSocketActive())
		{
			QString str = "<?xml version = '1.0' encoding='utf-8'?><stop></stop>";
			server->socket->write(str.toLatin1());
		}
	}
}


void GameWindow::closeWindow()
{
	if (isServer == true)
	{
		if (server->isSocketActive())
		{
			QString str = "<?xml version = \"1.0\" encoding=\"utf-8\"?>\n<close>\n</close>\n";
			server->socket->write(str.toLatin1());
		}
	}
	this->close();
}

void GameWindow::likeCollapce(bool isCollapced)
{
	//������� ������� ������������� ������� ���� � ������ �� ���������
	if (isCollapced == true)
	{
		for (int i = 45; i > 0; i--)
		{
			mainMenuWidget->setMaximumHeight(i);
			
			mainMenuWidget->updateGeometry();
		}
	}
	else
	{
		for (int i = 0; i < 46; i++)
		{
			mainMenuWidget->setMaximumHeight(i);
			mainMenuWidget->updateGeometry();
		}
	}
	
}


void GameWindow::menu()
{
	likeCollapce(false);
	gamePanelWidget->setDisabled(true);
}

void GameWindow::winClose()
{
	this->close();
}
void GameWindow::start()
{
	gamePanelWidget->setDisabled(false);
	invTableWidget->clearTable();
	likeCollapce(true);
}


