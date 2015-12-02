#ifndef DISTRIBUITIONDIALOG_H
#define DISTRIBUITIONDIALOG_H

#include <QDialog>
#include "backend/Graph.h"

namespace Ui {
class DistribuitionDialog;
}

class DistribuitionDialog : public QDialog
{
	Q_OBJECT

public:
	explicit DistribuitionDialog(const Network::Graph::Distribuition& distribuition, QWidget *parent = 0);
	~DistribuitionDialog();

private:
	Ui::DistribuitionDialog *ui;
};

#endif // DISTRIBUITIONDIALOG_H
