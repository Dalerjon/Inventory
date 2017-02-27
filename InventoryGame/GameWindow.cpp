#include "stdafx.h"
#include <chrono>
#include <thread>
#include "GameWindow.h"
#include <QImageReader>
#include <QDebug>

GameWindow::GameWindow()
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
	likeCollapce(true);
}

void GameWindow::showMenu()
{
	//���������� ������� ����
	likeCollapce(false);
	gamePanelWidget->setDisabled(true);
}

void GameWindow::closeWindow()
{
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



