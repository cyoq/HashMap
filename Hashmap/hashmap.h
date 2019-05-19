#pragma once

typedef unsigned long u64;

const u64 TABLE_SIZE = 10000;


template<typename K>
struct KeyHash {
	u64 operator()(const K &key) const {
		return static_cast<u64>(key) % TABLE_SIZE;
	}
};


template<typename K, typename V, typename F = KeyHash<K>>
class HashMap {

public:

	HashMap() {
		_table = new HashNode<K, V> * [TABLE_SIZE]();
	}

	~HashMap() {
		for (int i = 0; i < TABLE_SIZE; i++) {
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

	V operator[](const K& key) {
		V value{};
		this->get(key, value);
		return value;
	}


private:
	template<typename K, typename V>
	class HashNode {

	public:
		HashNode(const K& key, const V& value) {
			this->_key = key;
			this->_value = value;
			_next = nullptr;
		};

		K getKey() const {
			return _key;
		}

		V getValue() const {
			return _value;
		}

		void setValue(V value) {
			this->_value = value;
		}

		HashNode* getNext() const {
			return _next;
		}

		void setNext(HashNode* next) {
			this->_next = next;
		}

	private:
		K _key;
		V _value;
		HashNode<K, V>* _next; //next item in a bucket 
	};

	HashNode<K, V> **_table;
	F _hashFunc;
};