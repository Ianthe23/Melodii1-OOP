#include "domain.h"

vector<string> splitLine(const string& linie, char delimitator) {
	vector<string> atribute;
	stringstream stream(linie);
	string obiect;

	while (getline(stream, obiect, delimitator)) {
		atribute.push_back(obiect);
	}
	return atribute;
}

istream& operator>>(istream& input, Melodie& melodie) {
	string linie;
	getline(input, linie);

	if (linie.empty()) {
		return input;
	}

	vector<string> atribute = splitLine(linie, ',');
	melodie.setId(stoi(atribute[0]));
	melodie.setTitlu(atribute[1]);
	melodie.setArtist(atribute[2]);
	melodie.setRank(stoi(atribute[3]));

	return input;
}

bool Melodie::operator==(const Melodie& melodie) noexcept {
	return this->id == melodie.id && this->titlu == melodie.titlu && this->artist == melodie.artist && this->rank == melodie.rank;
}

ostream& operator<<(ostream& output, const Melodie& melodie) {
	output << melodie.getId() << "," << melodie.getTitlu() << "," << melodie.getArtist() << "," << melodie.getRank() << "\n";
	return output;
}

bool cmpRank(const Melodie& melodie1, const Melodie& melodie2) {
	if (melodie1.getRank() < melodie2.getRank()) {
		return true;
	}
	return false;
}