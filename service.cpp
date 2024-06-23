#include "service.h"

vector<Melodie> Service::sortRank() {
	vector<Melodie> sortat = repo.getAll();
	std::sort(sortat.begin(), sortat.end(), cmpRank);
	return sortat;
}

void Service::sterge(int id) {
	for (const auto& m : repo.getAll()) {
		if (m.getId() == id) {
			repo.stergeRepo(m);
		}
	}
}

void Service::modifica(int id, const string& titlu, int rank) {
	repo.modificaRepo(id, titlu, rank);
}

vector<int> Service::frecvente_rank() {
	vector<int> frecv;
	for (int i = 0; i <= 10; ++i) {
		int nr = 0;
		for (auto& m : getMelodii()) {
			if (m.getRank() == i) {
				nr++;
			}
		}
		frecv.push_back(nr);
	}
	return frecv;
}