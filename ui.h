#pragma once

#include "service.h"
#include "MyTableModel.h"

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include <QSlider>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>

#include <utility>

class Painter : public QWidget {
private:
	vector<int> ranks;
public:
	explicit Painter(vector<int> ranks) : ranks(ranks) {
		this->repaint();
	}
	void paintEvent(QPaintEvent* ev) override;
};

class AppGUI :public QWidget {
public:
	AppGUI(Service& service) : srv(service) {
		initGUI();
		loadTabel(srv.getMelodii(), srv.frecvente_rank());
		connectSignals();
		this->repaint();
	}
private:
	Service& srv;
	MyTableModel* model = nullptr;
	QTableView* table_view = new QTableView;

	QPushButton* btn_modifica = new QPushButton{ "&Update" };
	QPushButton* btn_sterge = new QPushButton{ "&Delete" };
	QLineEdit* txt_titlu = new QLineEdit;
	QSlider* sld_rank = new QSlider(Qt::Horizontal);

	void initGUI();
	void loadTabel(const vector<Melodie>& melodii, const vector<int> frecv);
	void connectSignals();
	void paintEvent(QPaintEvent* ev) override;
};
