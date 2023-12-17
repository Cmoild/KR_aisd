#include <iostream>
#include <string>
using namespace std;

static const double rehash_size = 0.75;

template<typename T, typename Y>
class HashTable {
public: 
	class Node {
	friend class HashTable;
	private:
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
		int h = 0, n = 0;
		for (int i = 0; i < s.length(); i++) {
			h += (((long long int)s[i] - (int)'a' + 1) * (long long int)pow(23, n)) % buffer_size;
			n++;
		}
		h = (h * 2 + 1) % buffer_size;
		return h;
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
				Add(arr2[i]->key, arr2[i]->data);
				if (arr2[i])
			}
				//Add(arr2[i]->value);
		}
		// удаление предыдущего массива
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
		//resize
		//rehash
		if (size + 1 > (int)(rehash_size * buffer_size)) Resize();
		int hash = hash_func(k);
		if (arr[hash] == nullptr)
			arr[hash] = new Node(k, d);
		else {
			Node* cur = arr[hash];
			while (cur->next) {
				//одинаковые элементы - исправить, не обработано
				cur = cur->next;
			}
			cur->next = new Node(k, d);
		}
		size++;
		return true;
	}

};



int main() {
	HashTable<string, string> h;
	h.Add("a", "some info1");
	h.Add("k", "some info2");
	h.Add("u", "some info3");
	h.Add("b", "some info3");
	h.Add("c", "some info3");
	h.Add("d", "some info3");
	h.Add("e", "some info3");
	//h.Add("f", "some info3");
	//h.Add("g", "some info3");
	//h.Add("h", "some info3");
	//h.Add("i", "some info3");
	//h.Add("k", "some info3");
	//h.Add("l", "some info3");
	cout << h.get_size();
}