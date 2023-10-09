#include "main.h"

class imp_res : public Restaurant
{
private:
	customer* table;
	customer* lastChange;
	int count = 0;

#pragma region customSubClasses
	//TODO Queue
	template<class T>
	class QueueModified {
	public:
		class Node;
	private:
		Node* head;
		Node* tail;
		int count;

	public:
		int maxSize;

		QueueModified() : head(nullptr), tail(nullptr), maxSize(0), count(0) {}
		bool push(T name) {
			if (count == maxSize) return false;
			if (!head) {
				head = tail = new Node(name);
			}
			else {
				tail->next = new Node(name);
				tail = tail->next;
			}

			count++;
			return true;
		}
		bool pop() {
			if (!head) return false;

			Node* delNode = head;
			head = head->next;

			delete delNode;
			count--;
			return true;
		}
		bool removeAt(int index) {
			if (index < 0 || index >= count) return false;

			if (index == 0) return pop();//Delete head

			Node* p = head;
			Node* pPre = nullptr;
			while (index--) {//Delete mid
				pPre = p;
				p = p->next;
			}
			if (pPre) {
				pPre->next = p->next;
			}

			if (index == count - 1) tail = pPre;//Delete tail

			p->next = nullptr;
			delete p;
			count--;

			return true;
		}
		T front() {
			return head->data;
		}
		int indexOf(T item) {
			Node* p = head;
			int i = 0;
			while (p) {
				if (p->data == item) return i;
				i++;
				p = p->next;
			}
			return -1;
		}

	public:
		class Node {
		private:
			T data;
			Node* next;
		public:
			friend class QueueModified;
			Node(T data, Node * next = nullptr) {
				this->data = data;
				this->next = next;
			}
		};
	};
#pragma endregion

	QueueModified<string>* queue;
	QueueModified<string>* joinOrder;

public:	
	imp_res() {
		table = lastChange = nullptr;
		queue = new QueueModified<string>();
		joinOrder = new QueueModified<string>();
		queue->maxSize = MAXSIZE;
		joinOrder->maxSize = 2 * MAXSIZE;
	};

	void RED(string name, int energy)
	{
		if (energy == 0) return;//Deny normies

		customer *cus = new customer (name, energy, nullptr, nullptr);

		if (!table) { //Table empty
			table = cus;
			cus->next = cus->prev = cus; //Cycle, needed?
			lastChange = cus;
			return; 
		}

		//TODO check for name

		//If count > MAXSIZE/2
		if (count >= MAXSIZE) {
			
			customer* p = table;
			customer* target = table;
			int res = cus->energy - table->energy;

			for (int i = 0; i < count; ++i) {
				if (abs(p->energy - cus->energy) > abs(res)) {
					res = p->energy - cus->energy;
					target = p;
				}
				p = p->next;
			}

			lastChange = target;
		}

		//Insert right
		if (lastChange->energy <= cus->energy) {
			cus->prev = lastChange;
			cus->next = lastChange->next;
			lastChange->next = cus;
		}
		else {//Insert left
			cus->next = lastChange;
			cus->prev = lastChange->prev;
			lastChange->prev = cus;
		}

		lastChange_reset();
		lastChange = cus;
		count++;
	}
	void BLUE(int num)
	{
		cout << "blue "<< num << endl;
	}
	void PURPLE()
	{
		cout << "purple"<< endl;
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
	}
	void LIGHT(int num)
		{
			cout << "light " << num << endl;
		}
};