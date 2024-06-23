#pragma once

#include "repo.h"
#include <algorithm>

class Service {
private:
	Repo& repo;
public:
	Service(Repo& r) : repo(r) {

	};

	Service(Service& other) = delete;

	vector<Melodie>& getMelodii() {
		return this->repo.getAll();
	}

	void sterge(int id);
	void modifica(int id, const string& titlu, int rank);

	vector<int> frecvente_rank();

	vector<Melodie> sortRank();
};