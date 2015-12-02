#include "distribuitiondialog.h"
#include "qcustomplot.h"
#include "ui_distribuitiondialog.h"

DistribuitionDialog::DistribuitionDialog(const Network::Graph::Distribuition& distribuition, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DistribuitionDialog)
{
	ui->setupUi(this);

	QCPBars *barsPlot = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
	ui->plot->addPlottable(barsPlot);

	// the count of pairs of nodes that can't be disconnected is in the last item of the distribuition
	ui->labelValue->setText(QString::number(distribuition[distribuition.size() - 1]));

	// the X axis will represent the connectivities
	QVector<double> connectivities;
	// the Y axis will represent the counts of each connectivity
	QVector<double> connectivityCounts;
	// the higher connectivity with a count greater then zero is the max connectivity
	unsigned maxConnectivity = 0;

	unsigned maxCount = 0;

	// get the information above from teh distribuition
	for(unsigned connectivity = 0; connectivity < distribuition.size() - 1; connectivity++) {
		unsigned count = distribuition[connectivity];

		connectivities << connectivity;
		connectivityCounts << count;

		if(count > 0 && connectivity > maxConnectivity) {
			maxConnectivity = connectivity;
		}

		if(count > maxCount) {
			maxCount = count;
		}
	}

	// setup the X Axis
	ui->plot->xAxis->setAutoTicks(false);
	ui->plot->xAxis->setTickVector(connectivities);
	ui->plot->xAxis->setSubTickCount(0);
	ui->plot->xAxis->grid()->setVisible(true);
	ui->plot->xAxis->setRange(-1, maxConnectivity + 1);

	// setup the Y Axis
	ui->plot->yAxis->setAutoTicks(false);
	ui->plot->yAxis->setTickVector(connectivityCounts);
	ui->plot->xAxis->setSubTickCount(0);
	ui->plot->yAxis->setTickLength(0, 1);
	ui->plot->yAxis->grid()->setVisible(true);
	ui->plot->yAxis->setRange(0, maxCount + 1);

	barsPlot->setData(connectivities, connectivityCounts);
	ui->plot->replot();

//	this->adjustSize();
}

DistribuitionDialog::~DistribuitionDialog()
{
	delete ui;
}
