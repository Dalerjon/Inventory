#include "stdafx.h"
#include "RunDlg.h"

RunDlg::RunDlg(int* dIsRun, QString* dIp)
{
	setupUi(this);
	*dIsRun = 0;
	isRun = dIsRun;
	ip = dIp;
	//������� ����� ��� IP
	QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
	QRegExp ipRegex("^" + ipRange
		+ "\\." + ipRange
		+ "\\." + ipRange
		+ "\\." + ipRange + "$");
	QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
	ipEdit->setValidator(ipValidator);

	//������� ���������� ����� ��������� � �������
	createConnections();
	likeCollapce(true);
}

RunDlg::~RunDlg()
{
	
}

void RunDlg::createConnections()
{
	//���������� ����� ��������� � �������
	QObject::connect(okBtn, &QPushButton::released, this, &RunDlg::startGame);
	QObject::connect(cancelBtn, &QPushButton::released, this, &RunDlg::closeDialog);
	QObject::connect(serverRbx, &QRadioButton::released, this, &RunDlg::hideAndShow);
	QObject::connect(clientRbx, &QPushButton::released, this, &RunDlg::hideAndShow);
}


void RunDlg::closeDialog()
{
	this->close();
}

void RunDlg::startGame()
{
	if (clientRbx->isChecked())
	{
		if (ipEdit->text().isEmpty())
		{
				QMessageBox::information(NULL, QString(tr("Warning...")),
				QString(tr("Please fill the IP field!")),
				QString(tr("OK")));
		}
		else
		{
			*ip = QString(ipEdit->text().toUtf8().constData());
			*isRun = 1;
			this->close();
		}
	}
	if (serverRbx->isChecked())
	{
		*isRun = 1;
		this->close();
	}
}

void RunDlg::hideAndShow()
{
	if (serverRbx->isChecked())
	{
		ipEdit->clear();
		likeCollapce(true);
	}
	if (clientRbx->isChecked())
	{
		ipEdit->clear();
		likeCollapce(false);
	}
}


void RunDlg::likeCollapce(bool isCollapced)
{
	//������� ������� ������������� ������� ���� � ������ �� ���������
	if (isCollapced == true)
	{
		for (int i = 40; i > 0; i--)
		{
			hidenWidget->setMaximumHeight(i);

			hidenWidget->updateGeometry();
		}
	}
	else
	{
		for (int i = 0; i < 41; i++)
		{
			hidenWidget->setMaximumHeight(i);
			hidenWidget->updateGeometry();
		}
	}

}