#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "ui_GameWindow.h"
#include <QSound>
#include <QtWidgets>
#include <QFrame>
#include "Server.h"
#include "Client.h"

class QDragEnterEvent;
class QDropEvent;

class GameWindow : public QMainWindow, public Ui::GameWindow
{
	Q_OBJECT
public:
	GameWindow(bool cIsServer, QString* cIp);
	~GameWindow();
	bool isServer;
	QString* ip;
	Server *server;
	Client *client;
	void menu();
	void winClose();
	void start();
	private slots:
	void startGame();
	void closeWindow();
	void showMenu();
private:
	void createConnections();
	void likeCollapce(bool);
};

#endif //GAMEWINDOW_H
