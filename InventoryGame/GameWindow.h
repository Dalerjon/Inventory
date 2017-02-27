#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "ui_GameWindow.h"
#include <QSound>
#include <QtWidgets>
#include <QFrame>

class QDragEnterEvent;
class QDropEvent;

class GameWindow : public QMainWindow, public Ui::GameWindow
{
	Q_OBJECT
public:
	GameWindow();
	~GameWindow();
	private slots:
	void startGame();
	void closeWindow();
	void showMenu();
private:
	void createConnections();
	void likeCollapce(bool);
};

#endif //GAMEWINDOW_H
