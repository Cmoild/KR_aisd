#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <chrono>
using namespace std;

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
	static constexpr double rehash_size = 0.75;
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
	HashTable<int, int> h;

	int choise;
	fstream f;
	int n = 50000;
	float* time = new float[n];
	float* key = new float[n];
	random_device dev;
	mt19937 rng(dev());
	cout << "1. Graph\n2. Manual input\n";
	cin >> choise;
	switch (choise) {
	case 1:
		f.open("graph.py", ios::out);
		f << "from matplotlib import pyplot as plt" << endl << endl;
		f << "import numpy as np" << endl;
		for (int i = 0; i < n; i++) {
			uniform_int_distribution<std::mt19937::result_type> dist6(1, 1000000);
			int x = dist6(rng);
			h.Add(x, x);
			key[i] = x;
		}
		for (int i = 0; i < n; i++) {
			uniform_int_distribution<std::mt19937::result_type> dist6(0, n - 1);
			int x = dist6(rng);
			auto start = chrono::steady_clock::now();
			h.search(key[x]);
			auto end = chrono::steady_clock::now();
			chrono::duration<double> tm = end - start;
			time[i] = tm.count();
		}
		f << "x = [";
		for (int i = 0; i < n; i++) {
			if (i != n - 1) f << time[i] << ',';
			else f << time[i] << ']';
		}
		f << endl << "z = [";
		for (int i = 0; i < n; i++) {
			if (i != n - 1) f << i + 1 << ',';
			else f << i + 1 << ']';
		}
		f << "\nplt.xlabel(\"Number of test\")\nplt.ylabel(\"Time\")";
		f << endl << "plt.scatter(z,x, c='red', s = 0.3)";
		f << endl << "plt.show()";
		f.close();
		system("python graph.py");
		break;
	case 2:
		cout << "Enter the number of elements: ";
		cin >> n;
		for (int i = 0; i < n; i++) {
			int k;
			int d = 0;
			cout << "Enter key: ";
			cin >> k;
			cout << "Enter data: ";
			cin >> d;
			h.Add(k, d);
		}
		h.print();
		break;
	}
	
}