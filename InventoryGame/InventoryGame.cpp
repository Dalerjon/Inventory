// InventoryGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <QApplication>
#include <QtWidgets>
#include <QtGUI>
#include "GameWindow.h"
#include "RunDlg.h"
#include <QResource>
#include <QtGui>
#include <QString>



int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	//����������� ��������
	QResource::registerResource("InventoryResource.rcc");
	//���������� ��� ����������� ������(������ ��� ������)
	int* isRun = new int;
	QString* ip = new QString();
	RunDlg rDlg(isRun, ip);
	rDlg.exec();
	//��������� ������ ��� ���������� ������� �� �������
	bool isServer = true;
	
	if (*isRun == 1 && (ip->isEmpty() || ip->toStdString() == ""))
	{
		GameWindow gWindow(isServer, ip);
		gWindow.show();
		return app.exec();
	}
	if (*isRun == 1 && (!ip->isEmpty() || ip != QString("")))
	{
		isServer = false;
		GameWindow gWindow(isServer,ip);
		gWindow.show();
		return app.exec();
	}
}

