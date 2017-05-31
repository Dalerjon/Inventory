#ifndef RUNDLG_H
#define RUNDLG_H
#include "ui_RunDlg.h"
#include <QString>
#include <QMessageBox>

class RunDlg : public QDialog, public Ui::RunDlg
{
	Q_OBJECT
public:
	RunDlg(int* isRun, QString* ip);
	~RunDlg();
	private slots:
	void startGame();
	void closeDialog();
	void hideAndShow();
private:
	void createConnections();
	void likeCollapce(bool);
	int* isRun;
	QString* ip;
};
#endif