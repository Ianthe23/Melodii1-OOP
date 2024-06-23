#include "repo.h"

void Repo::loadFile() {
	ifstream f(path);
	Melodie melodie{};

	while (f >> melodie) {
		melodii.push_back(melodie);
	}
	f.close();
}

void Repo::saveFile() {
	ofstream g(path);
	for (const auto& melodie : melodii) {
		g << melodie;
	}
	g.close();
}

void Repo::stergeRepo(const Melodie& melodie) {
	int nr = 0;
	for (const auto& m : getAll()) {
		if (m.getArtist() == melodie.getArtist()) {
			nr++;
		}
	}
	if (nr >= 2) {
		auto it = find(melodii.begin(), melodii.end(), melodie);
		if (it != melodii.end()) {
			melodii.erase(it);
			saveFile();
		}
	}
	else {
		throw RepoException("Melodia nu poate fi stearsa!\n");
	}
}

void Repo::modificaRepo(int id, const string& titlu, int rank) {
	int ok = 0;
	for (auto& m : getAll()) {
		if (m.getId() == id) {
			m.setTitlu(titlu);
			m.setRank(rank);
			saveFile();
			ok = 1;
			break;
		}
	}
	if (!ok) {
		throw RepoException("Melodia nu exista!\n");
	}
}

