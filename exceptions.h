#pragma once

#include <exception>
#include <string>
#include <utility>

using std::string;
using std::exception;

class RepoException :public exception {
	string mesaj;
public:
	explicit RepoException(string mesaj) noexcept :mesaj{ move(mesaj) } {};
	string get_mesaj() { return this->mesaj; }
};