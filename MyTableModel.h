#pragma once

#include <QAbstractTableModel>
#include <QAbstractItemView>
#include <vector>

#include "domain.h"
using std::vector;

class MyTableModel :public QAbstractTableModel {
	vector<Melodie> melodii;
	vector<int> ranks;
public:
	MyTableModel(const vector<Melodie>& melodii, const vector<int> ranks) : melodii(melodii), ranks(ranks) {

	};

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override {
		return melodii.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex{}) const override {
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			const Melodie& m = melodii[index.row()];
			switch (index.column()) {
			case 0:
				return QString::number(m.getId());
			case 1:
				return QString::fromStdString(m.getTitlu());
			case 2:
				return QString::fromStdString(m.getArtist());
			case 3:
				return QString::number(m.getRank());
			case 4:
				return QString::number(ranks[m.getRank()]);
			}
		}

		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return "ID";
			case 1:
				return "Titlu";
			case 2:
				return "Artist";
			case 3:
				return "Rank";
			case 4:
				return "Cu acelasi rank";
			default:
				return QString("");
			}
		}
		return QVariant();
	}

	void setMelodii(const vector<Melodie> melodii, vector<int> ranks) {
		this->melodii = melodii;
		this->ranks = ranks;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topLeft, bottomRight); // notify ca la observer
	}
};
