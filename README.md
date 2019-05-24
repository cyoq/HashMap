## HashMap
A simple hash map with simple hash function which can only get, put and remove value.

## How to use it?

Hashmap has such template parameters:
```C++
HashMap<keyType, valueType, tableSize, hashFunction> hmap;
```

Initialize a hashmap with default hash function:
```C++
const size_t tableSize = 10;

HashMap<std::string, int, tableSize> hmap;
```

To create your own hash function, create a struct or a class which overloads round brackets operator:
```C++
struct MyKeyHash {
	unsigned long operator()(const int& key) const {
		return key % 10;
	}
}
```

Initialize a hash map with your own hash function:
```C++
const size_t tableSize  = 10;

HashMap<int, std::string, tableSize, MyKeyHash> hmap;
```

## HashMap functionality
In order to put key and value into hash map, use:
```C++
hmap.put(key, value);
```

In order to get value from key, use:
```C++
hmap.get(key, getValue);
```
**getValue** - temporary variable which gets value from associated key

or alternative option:
```C++
valueType getValue = hmap[key];
```

In order to remove value, use:
```C++
hmap.remove(key);
```

Function `showTableFilling()` shows how buckets of hash map are filled. 
