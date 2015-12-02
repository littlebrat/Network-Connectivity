#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace Network {
class Graph;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onButtonLoadClicked();
	void onRadioButtonConnectivityToggled(bool checked);
	void onCheckBoxClicked(bool checked);

private:
	Ui::MainWindow *ui;
	Network::Graph* network; // loaded network

	void setOperationsInputEnabled(bool enabled);
	void setConnectivityInputEnabled(bool enabled);
};

#endif // MAINWINDOW_H
