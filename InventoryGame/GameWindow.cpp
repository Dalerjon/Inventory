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
	
	//форматируем инвентарь
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

	//создаем соединение между сигналами и слотами
	createConnections();
	
}

GameWindow::~GameWindow()
{
	
}

void GameWindow::createConnections()
{
	//соединение между сигналами и слотами
	QObject::connect(startBtn, &QPushButton::released, this, &GameWindow::startGame);
	QObject::connect(closeBtn, &QPushButton::released, this, &GameWindow::closeWindow);
	QObject::connect(menuBtn, &QPushButton::released, this, &GameWindow::showMenu);
}

void GameWindow::startGame()
{
	//делаем активным игровое поле
	gamePanelWidget->setDisabled(false);
	invTableWidget->clearTable();
	likeCollapce(true);
}

void GameWindow::showMenu()
{
	//показываем главное меню
	likeCollapce(false);
	gamePanelWidget->setDisabled(true);
}

void GameWindow::closeWindow()
{
	this->close();
}

void GameWindow::likeCollapce(bool isCollapced)
{
	//функция которая сворачивается главное меню и делает ее невидимой
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



