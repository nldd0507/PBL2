
#include "publisher.h"
Publisher::Publisher(const std::string &i, const std::string &n) {
	id = i;
	name = n;
}

const std::string& Publisher::getId() const {
	return id;
}

const std::string& Publisher::getName()const {
	return name;
}

std::ostream& operator <<(std::ostream& o, const Publisher& p) {
	o << p.id << " " << p.name<<std::endl;
	return o;
}
void Publisher::saveToFile(std::ofstream& out) const {
	out << id << ";" << name << std::endl;
}