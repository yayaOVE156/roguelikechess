#ifndef BIMAP_H
#define BIMAP_H

#include <map>
#include <stdexcept>


template <typename Keytype, typename Valtype>

class Bimap {
public:

	//insertion
	void insert(const Keytype& key, const Valtype& value);
	

	//gets value from the key
	const Valtype& getVal(const Keytype& key) const;

	//gets key from the value
	const Keytype& getKey(const Valtype& value) const;



private:
	std::map<Keytype, Valtype> key2val;
	std::map<Valtype, Keytype> val2key;

};

// XZ, string
template <typename Keytype, typename Valtype>
void Bimap<Keytype, Valtype>::insert(const Keytype& key, const Valtype& value) {
	if (key2val.find(key) != key2val.end() || val2key.find(value) != val2key.end()) {
		throw std::invalid_argument("Duplicate key or value.");
	}
	key2val[key] = value;
	val2key[value] = key;
}

// Implementation of getValue method
template <typename Keytype, typename ValType>
const ValType& Bimap<Keytype, ValType>::getVal(const Keytype& key) const {
	return key2val.at(key);
}

// Implementation of getKey method
template <typename Keytype, typename Valtype>
const Keytype& Bimap<Keytype, Valtype>::getKey(const Valtype& value) const {
	return val2key.at(value);
}
#endif // BIMAP_H
