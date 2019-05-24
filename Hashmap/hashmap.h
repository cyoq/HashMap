#pragma once

typedef unsigned long long u64;


const u64 prime1 = 37;
const u64 prime2 = 545911;
const u64 prime3 = 1034233;


template<typename K, size_t tableSize>
struct KeyHash {
	u64 operator()(const K& key) const {
		u64 hash = prime1;
		unsigned char* bit = (unsigned char*)&key;
		for (int i = 0; i < sizeof(key); i++) {
			hash = (hash * prime2) ^ ((u64)bit[i] * prime3);
		}
		return hash % tableSize;
	}
};


template<typename K, typename V, size_t tableSize, typename F = KeyHash<K, tableSize>>
class HashMap {

public:

	HashMap() {
		_table = new HashNode<K, V> *[tableSize]();
	}

	~HashMap() {
		for (int i = 0; i < tableSize; i++) {
			HashNode<K, V>* entry = _table[i];
			while (entry != nullptr) {
				HashNode<K, V>* prev = entry;
				entry = entry->getNext();
				delete prev;
			}
			_table[i] = nullptr;
		}
		delete[] _table;
	}

	bool get(const K& key, V &value) {
		u64 hashValue = _hashFunc(key);
		HashNode<K, V>* entry = _table[hashValue];

		while (entry != nullptr) {
			if (entry->getKey() == key) {
				value = entry->getValue();
				return true;
			}
			entry = entry->getNext();
		}
		return false;
	}

	void put(const K& key, const V& value) {
		u64 hashValue = _hashFunc(key);
		HashNode<K, V>* prev = nullptr;
		HashNode<K, V>* entry = _table[hashValue];

		while (entry != nullptr && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == nullptr) {
			entry = new HashNode<K, V>(key, value);
			if (prev == nullptr) {
				_table[hashValue] = entry;
			} else {
				prev->setNext(entry);
			}
		} else {
			entry->setValue(value);
		}
	}

	void remove(const K& key) {
		u64 hashValue = _hashFunc(key);
		HashNode<K, V>* prev = nullptr;
		HashNode<K, V>* entry = _table[hashValue];

		while (entry != nullptr && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == nullptr) {
			return;
		}
		else {
			if (prev == nullptr) {
				_table[hashValue] = entry->getNext();
			} else {
				prev = entry->getNext();
			}
			delete entry;
		}
	}

	void showTableFilling() {
		for (int i = 0; i < tableSize; i++) {
			int bucketFilling = 0;
			HashNode<K, V>* entry = _table[i];
			while (entry != nullptr) {
				entry = entry->getNext();
				bucketFilling++;
			}
			std::cout << i << " bucket has: " << bucketFilling << " elements" << "\n";
		}
	}

	V operator[](const K& key) {
		V value{};
		this->get(key, value);
		return value;
	}


private:
	template<typename Key, typename Value>
	class HashNode {

	public:
		HashNode(const Key& key, const Value& value) {
			this->_key = key;
			this->_value = value;
			this->_next = nullptr;
		};

		Key getKey() const {
			return _key;
		}

		Value getValue() const {
			return _value;
		}

		void setValue(const Value& value) {
			this->_value = value;
		}

		HashNode* getNext() const {
			return _next;
		}

		void setNext(HashNode* next) {
			this->_next = next;
		}

	private:
		Key _key;
		Value _value;
		HashNode<Key, Value>* _next; //next item in a bucket 
	};

	HashNode<K, V> **_table;
	F _hashFunc;
};