#pragma once

#include <vector>
#include <fstream>

#include "domain.h"
#include "exceptions.h"

class Repo {
private:
	vector<Melodie> melodii;
	string path;
	void loadFile();
	void saveFile();
public:
	Repo(const string& p) : path(p) {
		loadFile();
	}

	Repo(Repo& other) = delete;

	void stergeRepo(const Melodie& melodie);
	void modificaRepo(int id, const string& titlu, int rank);

	vector<Melodie>& getAll() {
		return this->melodii;
	}
};
