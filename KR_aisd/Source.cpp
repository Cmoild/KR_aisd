#include <iostream>
#include <string>
using namespace std;

static const double rehash_size = 0.75;

template<typename T, typename Y>
class HashTable {
public: 
	class Node {
	public:
		T key;
		Y data;
		Node* next = nullptr;
		Node(T k, Y d) {
			key = k;
			data = d;
			next = nullptr;
		}
	};
private:
	static const int default_size = 10;
	Node** arr;
	int size;
	int buffer_size;

	int hash_func(string s) {
		long h = 0, n = 0;
		for (int i = 0; i < s.length(); i++) {
			h += (((long long int)s[i] - (int)'a' + 1) * (long long int)pow(7, n)) % buffer_size;
			n++;
		}
		return h % buffer_size;
	}

	int hash_func(int k) {
		return k % buffer_size;
	}

	void Resize() {
		int past_buffer_size = buffer_size;
		buffer_size *= 2;
		size = 0;
		Node** arr2 = new Node * [buffer_size];
		for (int i = 0; i < buffer_size; ++i)
			arr2[i] = nullptr;
		swap(arr, arr2);
		for (int i = 0; i < past_buffer_size; ++i)
		{
			if (arr2[i]) {
				Node* cur = arr2[i];
				while (cur) {
					Add(cur->key, cur->data);
					cur = cur->next;
				}

			}
		}
		for (int i = 0; i < past_buffer_size; ++i)
			if (arr2[i])
				delete arr2[i];
		delete[] arr2;
	}

public:

	int get_size() {
		return size;
	}

	HashTable()
	{
		buffer_size = default_size;
		size = 0;
		arr = new Node*[buffer_size];
		for (int i = 0; i < buffer_size; ++i)
			arr[i] = nullptr;
	}

	bool Add(T k, Y d) {
		if (size + 1 > (int)(rehash_size * buffer_size)) Resize();
		int hash = hash_func(k);
		if (arr[hash] == nullptr)
			arr[hash] = new Node(k, d);
		else {
			Node* cur = arr[hash];
			if (cur->key == k) return false;
			while (cur->next) {
				if (cur->next->key == k) return false;
				cur = cur->next;
			}
			cur->next = new Node(k, d);
		}
		size++;
		return true;
	}

	Node* search(T k) {
		int hash = hash_func(k);
		if (arr[hash]) {
			Node* cur = arr[hash];
			while (cur) {
				if (cur->key == k) return cur;
				cur = cur->next;
			}
		}
		return nullptr;
	}

	void print() {
		cout << endl;
		for (int i = 0; i < buffer_size; i++) {
			if (arr[i]) {
				Node* cur = arr[i];
				while (cur) {
					cout << cur->key << " ";
					cur = cur->next;
				}
				cout << endl;
			}
		}
		cout << endl;
	}

	void del(T k) {
		int hash = hash_func(k);
		if (arr[hash]) {
			Node* cur = arr[hash];
			if (cur->key == k and cur->next == nullptr) {
				arr[hash] = nullptr;
				size--;
				return;
			}
			if (cur->key == k and cur->next) {
				arr[hash] = cur->next;
				size--;
				return;
			}
			while (cur) {
				if (cur->next->key == k) {
					cur->next = cur->next->next;
					size--;
					return;
				}
				cur = cur->next;
			}
		}
		return;
	}

};



int main() {
	HashTable<int, string> h;
	h.Add(1, "sodibhj");
	h.Add(2, "sodibhj");
	h.Add(3, "sodibhj");
	
	h.Add(1436, "sodibhj");
	h.Add(34624356, "aieufgh");
	h.Add(6, "edrh");
	h.Add(9, "sodibhj");
	h.Add(10, "sodibhj");
	h.Add(11, "sodibhj");
	h.Add(12, "sodibhj");
	h.Add(13, "sodibhj");
	h.Add(14, "sodibhj");
	h.print();
	cout << endl << h.get_size();
	h.del(1436);
	h.print();
	cout << endl << h.get_size();
}