#include <iostream>
#include <string>
using namespace std;

template<typename T, typename Y>
class HashTable {
public:
	class Node {
		T key;
		Y data;
		bool state;
		Node(T k, Y d) {
			key = k;
			data = d;
			state = true;
		}
	};
private:
	Node* arr;
	int size;
	int buffer_size;
	int size_all_non_nullptr;
public:
	int hash_func(string s) {
		int h = 0, n = 0;
		for each (char c in s) {

		}
		return 0;
	}

	int hash_func(int k) {
		return 0;
	}

};

int main() {
	
}