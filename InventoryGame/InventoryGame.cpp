// InventoryGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <QApplication>
#include <QtWidgets>
#include <QtGUI>
#include "GameWindow.h"
#include <QResource>
#include <QtGui>


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	//регистрация ресурсов
	QResource::registerResource("InventoryResource.rcc");
	GameWindow gWindow;
	gWindow.show();
	return app.exec();
}

