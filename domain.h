#pragma once

#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> splitLine(const string& linie, char delimitator);

class Melodie {
private:
	int id;
	string titlu;
	string artist;
	int rank;

public:
	Melodie() {
		id = 0;
		titlu = "";
		artist = "";
		rank = -1;
	}

	Melodie(int id, const string& titlu, const string& artist, int rank) {
		this->id = id;
		this->titlu = titlu;
		this->artist = artist;
		this->rank = rank;
	}

	Melodie& operator=(const Melodie& other) = default;

	//getters
	const int getId() const{
		return id;
	}
	const string& getTitlu() const {
		return titlu;
	}
	const string& getArtist() const {
		return artist;
	}
	const int getRank() const {
		return rank;
	}

	//setters
	void setId(int id) {
		this->id = id;
	}
	void setTitlu(const string& titlu) {
		this->titlu = titlu;
	}
	void setArtist(const string& artist) {
		this->artist = artist;
	}
	void setRank(int rank) {
		this->rank = rank;
	}

	bool operator==(const Melodie& melodie) noexcept;
	friend istream& operator>>(istream& input, Melodie& melodie);
	//string print() const;
};

ostream& operator<<(ostream& output, const Melodie& melodie);
bool cmpRank(const Melodie& melodie1, const Melodie& melodie2);