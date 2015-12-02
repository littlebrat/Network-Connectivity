#include "connectivitydialog.h"
#include "ui_connectivitydialog.h"
#include "backend/Connectivity.h"

ConnectivityDialog::ConnectivityDialog(const Network::Connectivity& connectivity,QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ConnectivityDialog)
{
	ui->setupUi(this);

	// output the connectivity value
	ui->labelValue->setText(QString::number(connectivity.getValue()));

	// display all the disconnect nodes in the list widget
	for(auto nodeId : connectivity.getDisconnectNodes()) {
		ui->listWidget->addItem("Node " + QString::number(nodeId));
	}
}

ConnectivityDialog::~ConnectivityDialog()
{
	delete ui;
}
