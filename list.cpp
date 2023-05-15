#include <iostream>
#include <string>
using namespace std;
template <typename T>

class Double_list {
public:
	class iterator;
private:

	class Node {
		friend class Double_list;
	
	private:
		T value;
	public:
		Node* next = nullptr;
		Node* prev = nullptr;

		Node() {};
		Node(T _value) :value(_value) {};
	};
public:
	class iterator {
		friend class Double_list;

	private:
		Node* the_node;

	public:
		//конструкторы
		iterator() : the_node(nullptr) {};
		iterator(Node* n) : the_node(n) {};
		iterator(const iterator& it) : the_node(it.the_node) {};

		//переопределяем операторы
		iterator& operator=(const iterator& it)
		{
			the_node = it.the_node;
			return *this;
		}

		//два итератора указывают на один и тот же узел
		bool operator == (const iterator& it) const
		{
			return (the_node == it.the_node);
		}


		bool operator!=(const iterator& it) const
		{
			return !(it == *this);
		}

		//переводит итератор на следующий узел списка
		iterator& operator++()
		{
			if (the_node == nullptr)
				throw "incremented an empty iterator";
			if (the_node->next == nullptr)
				throw "tried to increment too far past the end";

			the_node = the_node->next;
			return *this;
		}

		//переводит итератор на предыдущий узел списка 
		iterator& operator--()
		{
			if (the_node == nullptr)
				throw "decremented an empty iterator";
			if (the_node->prev == nullptr)
				throw "tried to decrement past the beginning";

			the_node = the_node->prev;
			return *this;
		}

		//Возвращает значение данных
		T& operator*() const
		{
			if (the_node == nullptr)
				throw "tried to dereference an empty iterator";
			return the_node->value;
		}
		
	};


	// Указатели на начало и конец
	Node* head;
	Node* tail;
	//Итераторы
	iterator head_it; //всегда указывает на начало
	iterator tail_it;// на следующий за концом
public:
	Double_list()
	{
		head = tail = new Node;
		tail->next = nullptr;
		tail->prev = nullptr;

		//инициализирует итераторы
		head_it = iterator(head);
		tail_it = iterator(tail);
	}

	//Создать список, который содержит один элемент
	Double_list(T node_val)
	{
		head = tail = new Node;
		tail->next = nullptr;
		tail->prev = nullptr;

		head_it = iterator(head);
		tail_it = iterator(tail);
		push_front(node_val);
	}

	~Double_list()
	{
		Node* node_to_delete = head;
		for (Node* sn = head; sn != tail;)
		{
			sn = sn->next;
			delete node_to_delete;
			node_to_delete = sn;
		}

		delete node_to_delete;
	}
	// Методы контейнера

	void push_front(T _value) {
		Node* new_node = new Node(_value);
		new_node->next = head;
		new_node->prev = nullptr;
		head->prev = new_node;
		head = new_node;
		head_it = iterator(head);
	}
	void push_back(T _value) {
		if (head == tail) {
			push_front(_value);
			return;
		}
		Node* new_node = new Node(_value);
		new_node->prev = tail->prev;
		new_node->next = tail;
		tail->prev->next = new_node;
		tail->prev = new_node;
		tail_it = iterator(tail);
	}
	void insert(T _value, iterator& it) {
		for (Node* dn = head; dn != tail; dn = dn->next)
		{
			//Найден ли узел для заданного итератора
			if (dn == it.the_node)
			{
				Node* node_to_add = new Node(_value);
				node_to_add->prev = dn;
				node_to_add->next = dn->next;
				dn->next->prev = node_to_add;
				dn->next = node_to_add;

			}
		}
	}

	iterator find(T _value) {
		for (iterator it = head_it; it != tail_it; ++it) {
			if (it.the_node->value == _value)
				return it;
		}
	}

	T remove_front() {
		
		Node* node_to_del = head;
		head = head->next;
		head->prev = nullptr;
		T return_val = node_to_del->value;
		delete node_to_del;
		head_it = iterator(head);
		return return_val;
	}

	T remove_back() {
		
		Node* node_to_del = tail->prev;
		tail->prev = tail->prev->prev;
		tail->prev->next = tail;
		T return_val = node_to_del->value;
		delete node_to_del;
		tail_it = iterator(tail);
		return return_val;
	}



	void remove_it(iterator& it) {
		
		if (it == head_it) {
			remove_front();
			it=head_it;
			return;
		}
		iterator new_tail_it = tail_it;
		if (it == --new_tail_it) {
			remove_back();
			new_tail_it = tail_it;
			it = --new_tail_it;
			return;
		}
		Node* node = it.the_node;
		++it;
		for (iterator for_it = head_it; for_it != tail_it; ++for_it) {
			if (for_it == it) {
				node->prev->next = node->next;
				node->next->prev = node->prev;
				delete node;
				
			}
				

		}
	}

	int size() {
		int count = 0;
		for (iterator it = head_it; it != tail_it; ++it) {
			count++;
		}
		return count;
	}


	iterator front_it() {
		return head_it;
	}

	iterator back_it() {
		return tail_it;
	}
};




class Human_class {
private:
	string name;
	int age;

public:
	Human_class() :name("Undefined"), age(0) {};
	Human_class(string _name, int _age) : name(_name), age(_age) {};
	Human_class(Human_class& hum) {
		name = hum.getName();
		age = hum.getAge();
	}
	string getName() {
		return name;
	}
	int getAge() {
		return age;
	}
	void setName(string new_name) {
		name = new_name;
	}
	void setAge(int new_age) {
		age = new_age;
	}
	void print_info() {
		cout << "Name: " << name << " Age: " << age << endl;
	}

	bool operator == ( Human_class& h) const
	{
		return ((name == h.getName())&& (age == h.getAge()));
	}
};


int main() {
	//Создаем контейнер
	Double_list<Human_class> the_list;
	Double_list<Human_class>::iterator list_it;
	string human_names[] = { "John", "Jesse", "Alan","Hank"};
	int size = sizeof(human_names) / sizeof(string);
	////Добавляем вперед
	for (int i = 1; i < 6; i++) {
		the_list.push_front(*new Human_class(human_names[rand()%size],rand()%60));
	}
	cout << "push_front:" << endl;
	for (list_it = the_list.front_it(); list_it != (the_list.back_it()); ++list_it) {
			(*list_it).print_info();
	}

	//Добавляем назад
	for (int i = 6; i < 11; i++) {
		the_list.push_back(*new Human_class(human_names[rand() % size], rand() % 60));
	}
	cout << "push_back:" << endl;
	for (list_it = the_list.front_it(); list_it != (the_list.back_it()); ++list_it) {
		(*list_it).print_info();
	}

	// Удаляем спереди
	cout << "remove_front " << endl;
	the_list.remove_front().print_info(); //<< endl;

	// Удаляем сзади
	cout << "remove_back " << endl; 
	the_list.remove_back().print_info();
	cout << endl;
	for (list_it = the_list.front_it(); list_it != (the_list.back_it()); ++list_it) {
		(*list_it).print_info();
	}

	Human_class hum("Alan", 55);
	bool flag = false;
	for (list_it = the_list.front_it(); list_it != (the_list.back_it()); ++list_it ) {
		cout << "Searching " << hum.getName() << " " << hum.getAge() << " age..." << endl;
		if ((list_it) == the_list.find(hum)) {
			cout << "Found!" << endl;
			flag = true;
			(*list_it).print_info();
			the_list.remove_it(list_it);
		}
		
	}
	if (!flag)
		cout << "Not found!" << endl;

	

	return 0;
};