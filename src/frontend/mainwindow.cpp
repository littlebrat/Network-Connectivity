#include <unistd.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backend/Graph.h"

using namespace Network;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow), network(nullptr) {

	ui->setupUi(this);
	this->setFixedSize(490, 171);

	// connect signals to slots
	connect(ui->buttonLoad, SIGNAL(clicked(bool)), this, SLOT(onButtonLoadClicked()));

	// operations inputs are disabled until a network has been loaded
	setOperationsInputEnabled(false);
	// the default operation is connectivity
	ui->radioButtonConnectivity->setChecked(true);
}

MainWindow::~MainWindow() {
	if(this->network != nullptr) {
		delete this->network;
	}

	delete ui;
}

void MainWindow::onButtonLoadClicked() {

	// disable all user input while loading the network
	ui->lineEdit->setEnabled(false);
	ui->buttonLoad->setEnabled(false);
	ui->radioButtonConnectivity->setEnabled(false);
	ui->radioButtonDistribuition->setEnabled(false);
	ui->checkBox->setEnabled(false);
	ui->labelNode1->setEnabled(false);
	ui->labelNode2->setEnabled(false);
	ui->spinBoxNode1->setEnabled(false);
	ui->spinBoxNode2->setEnabled(false);
	ui->buttonStart->setEnabled(false);

	// notify the user that the network is being loaded
	ui->statusBar->showMessage("loading...");

	// to test only the ui functionality for now will use the graph default constructor
	// but this must be replaced by the file name constructor
//	this->network = new Graph(ui->lineEdit->text());
	this->network = new Graph();

	sleep(3);

	ui->statusBar->showMessage("Loaded network: " + ui->lineEdit->text());

	// reenable user input
	ui->lineEdit->setEnabled(true);
	ui->buttonLoad->setEnabled(true);
	setOperationsInputEnabled(true);
}

void MainWindow::setOperationsInputEnabled(bool enabled) {
	ui->radioButtonConnectivity->setEnabled(enabled);
	ui->radioButtonDistribuition->setEnabled(enabled);
	setConnectivityInputEnabled(enabled);
}

void MainWindow::setConnectivityInputEnabled(bool enabled) {
	// only enable the conenctivity input if the connectivity radiobutton is enabled and checked
	enabled = enabled &&
			ui->radioButtonConnectivity->isEnabled() &&
			ui->radioButtonConnectivity->isChecked();

	ui->checkBox->setEnabled(enabled);
	ui->labelNode1->setEnabled(enabled);
	ui->labelNode2->setEnabled(enabled);
	ui->spinBoxNode1->setEnabled(enabled);
	ui->spinBoxNode2->setEnabled(enabled);
	ui->buttonStart->setEnabled(enabled);
}



