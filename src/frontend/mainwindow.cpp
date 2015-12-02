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
	connect(ui->radioButtonConnectivity, SIGNAL(toggled(bool)), this, SLOT(onRadioButtonConnectivityToggled(bool)));
	connect(ui->checkBox, SIGNAL(clicked(bool)), this, SLOT(onCheckBoxClicked(bool)));
	connect(ui->buttonStart, SIGNAL(clicked()), this, SLOT(onButtonStartClicked()));

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
	setInputEnabled(false);

	// notify the user that the network is being loaded
	ui->statusBar->showMessage("loading...");

	// to test only the ui functionality for now will use the graph default constructor
	// but this must be replaced by the file name constructor
//	this->network = new Graph(ui->lineEdit->text());
	this->network = new Graph();

	sleep(1);

	ui->statusBar->showMessage("Loaded network: " + ui->lineEdit->text());

	// reenable user input
	setInputEnabled(true);
}

void MainWindow::setInputEnabled(bool enabled) {

	ui->label->setEnabled(enabled);
	ui->buttonLoad->setEnabled(enabled);
	setOperationsInputEnabled(enabled);
}

void MainWindow::setOperationsInputEnabled(bool enabled) {
	ui->radioButtonConnectivity->setEnabled(enabled);
	ui->radioButtonDistribuition->setEnabled(enabled);
	setConnectivityInputEnabled(enabled);
	ui->buttonStart->setEnabled(enabled);
}

void MainWindow::setConnectivityInputEnabled(bool enabled) {
	// only enable the conenctivity input if the connectivity radiobutton is enabled and checked
	enabled = enabled &&
			ui->radioButtonConnectivity->isEnabled() &&
			ui->radioButtonConnectivity->isChecked();

	ui->checkBox->setEnabled(enabled);
	setNodeInputEnabled(enabled);
}

void MainWindow::setNodeInputEnabled(bool enabled) {
	enabled = enabled && ui->checkBox->isEnabled() && !ui->checkBox->isChecked();
	ui->labelNode1->setEnabled(enabled);
	ui->spinBoxNode1->setEnabled(enabled);
	ui->labelNode2->setEnabled(enabled);
	ui->spinBoxNode2->setEnabled(enabled);
}

void MainWindow::onRadioButtonConnectivityToggled(bool checked) {
	setConnectivityInputEnabled(checked);
}

void MainWindow::onCheckBoxClicked(bool checked) {
	bool enabled = !checked;
	ui->labelNode1->setEnabled(enabled);
	ui->spinBoxNode1->setEnabled(enabled);
	ui->labelNode2->setEnabled(enabled);
	ui->spinBoxNode2->setEnabled(enabled);
}

void MainWindow::onButtonStartClicked() {

	setInputEnabled(false);
	// notify the user that it is processing
	ui->statusBar->showMessage("processing...");

	if(ui->radioButtonConnectivity->isChecked()) {
		// compute a connectivity
		Connectivity connectivity;
		if(ui->checkBox->isChecked()) {
//			connectivity = network->getConnectivity();
			sleep(1);
		} else {
//			connectivity = network->getConnectivity(ui->spinBoxNode1->value(), ui->spinBoxNode2->value());
			sleep(1);
		}

		// display the output with a connectivity widget

	} else if(ui->radioButtonDistribuition->isChecked()) {
		// compute distribuition
//		Graph::Distribuition distribuition = network->getDistribuition();
		sleep(1);

		// display the output with a distribuition widget
	}

	ui->statusBar->showMessage("complete", 5000);

	setInputEnabled(true);
}
