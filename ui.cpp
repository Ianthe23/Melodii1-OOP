#include "ui.h"
#include <QDebug>

void Painter::paintEvent(QPaintEvent* ev) {
	/*QPainter p{ this };
	p.setPen(Qt::darkYellow);
	int rank = 0;
	for (auto& c : ranks) {
		int x = (rank + 1) * 50;
		p.drawLine(x, 0, x, x * c * 10);
		rank++;
	}*/
}

void AppGUI::paintEvent(QPaintEvent* ev) {
	QPainter p{ this };
	p.setPen(Qt::darkRed);
	int rank = 0;
	for (auto& c : srv.frecvente_rank()) {
		int x = (rank + 1) * 10;
		p.drawLine(x, p.device()->height(), x, p.device()->height() - c * 5);
		rank++;
	}
}

void AppGUI::initGUI() {
	QHBoxLayout* mainLayout = new QHBoxLayout;
	setLayout(mainLayout);

	QVBoxLayout* st = new QVBoxLayout;
	mainLayout->addLayout(st);

	QLabel* tabelLabel = new QLabel("Tabel melodii");
	tabelLabel->setAlignment(Qt::AlignCenter);
	st->addWidget(tabelLabel);

	table_view->resizeColumnsToContents();
	table_view->setMinimumSize(508, 350);
	st->addWidget(table_view, 2);
	st->addSpacing(40);

	QVBoxLayout* dr = new QVBoxLayout;
	mainLayout->addLayout(dr);

	QFormLayout* formLayout = new QFormLayout;
	dr->addLayout(formLayout);

	formLayout->addRow(new QLabel{ "Titlu: " }, txt_titlu);
	sld_rank->setMaximum(10);
	sld_rank->setMinimum(0);

	sld_rank->setTickInterval(1);
	sld_rank->setTickPosition(QSlider::TicksBelow);

	formLayout->addWidget(sld_rank);
	formLayout->addWidget(btn_modifica);
	dr->addWidget(btn_sterge);

}

void AppGUI::loadTabel(const vector<Melodie>& melodii, const vector<int> frecv) {
	model = new MyTableModel{ melodii, frecv };
	table_view->setSelectionMode(QAbstractItemView::SingleSelection);
	table_view->setModel(model);
}
 
void AppGUI::connectSignals() {
	QObject::connect(table_view, &QTableView::pressed, [this] {
		if (table_view->selectionModel()->selectedIndexes().isEmpty()) {
			txt_titlu->setText("");
			return;
		}
		else {
			auto row = table_view->selectionModel()->selectedIndexes().at(0).row();
			auto titlu = table_view->model()->data(table_view->model()->index(row, 1), Qt::DisplayRole).toString();
			txt_titlu->setText(titlu);
			qDebug() << titlu << '\n';
		}
		});

	QObject::connect(btn_modifica, &QPushButton::clicked, [this] {
		if (table_view->selectionModel()->selectedIndexes().isEmpty()) {
			return;
		}
		auto row = table_view->selectionModel()->selectedIndexes().at(0).row();
		auto id = table_view->model()->data(table_view->model()->index(row, 0), Qt::DisplayRole).toInt();

		auto titlu_nou = txt_titlu->text().toStdString();
		qDebug() << titlu_nou << '\n';
		auto rank_nou = sld_rank->value();
		try {
			srv.modifica(id, titlu_nou, rank_nou);
			repaint();
		}
		catch (RepoException& mesaj) {
			QMessageBox msg;
			msg.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
		}
		loadTabel(srv.getMelodii(), srv.frecvente_rank());
		txt_titlu->clear();
		sld_rank->setValue(0);
		});

	QObject::connect(btn_sterge, &QPushButton::clicked, [this] {
		if (table_view->selectionModel()->selectedIndexes().isEmpty()) {
			return;
		}
		auto row = table_view->selectionModel()->selectedIndexes().at(0).row();
		auto id = table_view->model()->data(table_view->model()->index(row, 0), Qt::DisplayRole).toInt();
		try {
			srv.sterge(id);
			repaint();
		}
		catch (RepoException& mesaj) {
			QMessageBox msg;
			msg.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
		}
		loadTabel(srv.getMelodii(), srv.frecvente_rank());
		});
}

