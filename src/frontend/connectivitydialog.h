#ifndef CONNECTIVITYDIALOG_H
#define CONNECTIVITYDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectivityDialog;
}

namespace Network {
class Connectivity;
}

class ConnectivityDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ConnectivityDialog(const Network::Connectivity& connectivity, QWidget *parent = 0);
	~ConnectivityDialog();

private:
	Ui::ConnectivityDialog *ui;
};

#endif // CONNECTIVITYDIALOG_H
