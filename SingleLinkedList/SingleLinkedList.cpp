#include <iostream>
#include <concepts>


template<typename T>
struct Node
{
	explicit Node(T data) : Data(data) {}
	Node<T>* Next = nullptr;
	T Data;
};



template<typename T>
class LinkedList
{
public:

	LinkedList() = default;
	template<typename U>
	requires std::same_as<T, U>
	LinkedList(U data) {
		Head = new Node<U>(data);
	}

	template<typename U>
	requires std::same_as<T, U>
	LinkedList(std::initializer_list<U> args) {
		for (const auto& arg : args) {
			this->PushBack(arg);
		}
	}


	~LinkedList() {
		while (Head) {
			auto Temp = Head;
			Head = Temp->Next;
			delete Temp;
		}
	}

	template<typename U>
	requires std::same_as<T, U>
	void PushBack(U data) {
		Node<U>* NewNode = new Node<U>(data);
		if (Head == nullptr) {
			Head = new Node<U>(data);
		}
		else if (Head->Next == nullptr)	{
			Head->Next = NewNode;
			Tail = NewNode;
		}
		else {
			Tail->Next = NewNode;
			Tail = NewNode;
		}
	}



	// ITERATORS
	class Iterator
	{
	public:
		Node<T>* Current;

		Iterator(Node<T>* node) : Current(node)	{ }

		T& operator*() {
			return Current->Data;
		}

		Iterator operator++ () {
			Current = Current->Next;
			return *this;
		}

		Iterator operator++ (int) {
			Iterator Temp = *this;
			Current = Current->Next;
			return Temp;
		}

		bool operator!=(const Iterator& rhs) const {
			return Current != rhs.Current;
		}

		bool operator==(const Iterator& rhs) const {
			return Current == rhs.Current;
		}
	};

	class ConstIterator
	{
	public:

	};


	Iterator begin() {
		return Iterator(Head);
	}
	Iterator end() {
		return Iterator(nullptr);
	}

private:
	Node<T>* Head = nullptr;
	Node<T>* Tail = nullptr;
};






int main()
{
	LinkedList<int> List(1);
	List.PushBack(2);
	List.PushBack(3);
	List.PushBack(4);
	List.PushBack(5);

	LinkedList<float> List2{ 1.0f, 2.2f, 3.3f, 4.4f, 5.5f };

	for (auto& l : List)
	{
		std::cout << l << "\n";
	}

	for (auto& l : List2)
	{
		std::cout << l << "\n";
	}



	return 0;
}
