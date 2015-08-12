#include<string>
#include<vector>
#include<climits>
#include<iostream>

// Entry node of chain
struct Entry {
  std::string key;
  std::string value;
  Entry* next;
  Entry(const std::string &k, const std::string &v): key(k), value(v), next(NULL){}
};


class HashTable {
 private:
  int size;
  std::vector<Entry*> table;

 public:
  HashTable(int n): size(n) {
    table.reserve(n);
    for (int i = 0; i < size; i++)
      table.push_back(NULL);
  }

  /**
   * hash string to int
   * refer to
   * https://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
   */
  int hash(const std::string &key) {
    unsigned long int hashval = 0;
    int i = 0;

    // string to integer
    while (i < key.length()) {
      hashval = hashval * 101 + key[i++];
    }
    return hashval % size;
  }

  void put(const std::string &key, const std::string &value) {
    int index = hash(key);
    std::cout << key << " index is " << index << std::endl;
    
    Entry *cur = table[index];
    if (cur == NULL) {
      Entry *ptr = new Entry(key, value);
      // the chain is empty
      table[index] = ptr;
    }

    // try to find key and move cur ptr to end of chain
    while (cur != NULL && cur->key != key) {
      cur = cur->next;
    }

    if (cur != NULL) {
      // find key in HashTable
      cur->value = value;
    } else {
      // can not find it, then insert key to head of chain
      Entry *ptr = new Entry(key, value);
      ptr->next = table[index]->next;
      table[index]->next = ptr;
    }
  }

  int get(const std::string &key, std::string &value) {
    int index = hash(key);
    Entry *cur = table[index];
    while (cur != NULL && cur->key != key) {
      cur = cur->next;
    }
    if (cur == NULL) {
      return -1;
    } else {
      value = cur->value;
      return 0;
    }
  }
};


void print(HashTable &hashtable, const std::string &key) {
  std::string value;
  if (hashtable.get(key, value) == 0) {
    std::cout << key << " => " << value << std::endl;
  } else {
    std::cout << "can not find key: " << key << std::endl;
  }
}

int main() {

  HashTable hashtable(65536);
  
  hashtable.put("key1", "value1");
  hashtable.put("key2", "value2");
  hashtable.put("key3", "value3");
  hashtable.put("key4", "value4");
  print(hashtable, "key1");
  print(hashtable, "key2");
  print(hashtable, "key3");
  print(hashtable, "key4");

  // modify value
  hashtable.put("key1", "value9");

  print(hashtable, "key1");
  print(hashtable, "key2");
  print(hashtable, "key3");
  print(hashtable, "key4");

	return 0;
}
