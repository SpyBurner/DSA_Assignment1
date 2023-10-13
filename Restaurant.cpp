#include "main.h"

class imp_res : public Restaurant
{
private:
	customer* lastChange;
	int count = 0;
	int swapCount = 0;

#pragma region customSubClasses
	//TODO Queue
	class QueueModified {
	public:
		class Node;
	private:
		Node* head;
		Node* tail;
		int count;
		int maxSize;

		int joinTime;
	public:

		QueueModified(int MAXSIZE) {
			head = tail = nullptr;
			count = joinTime = 0;
			maxSize = MAXSIZE;
		}

		bool push(customer* target) {
			customer* cus = new customer(target->name, target->energy, nullptr, nullptr);
			if (count == 2 * maxSize) return false;
			if (!head) {
				head = tail = new Node(cus, joinTime++);
			}
			else {
				tail->next = new Node(cus, joinTime++);
				tail = tail->next;
			}

			count++;
			return true;
		}//Push deep copy

		bool pop() {
			if (!head) return false;

			Node* delNode = head;
			head = head->next;

			delNode->next = nullptr;
			delete delNode;
			count--;
			return true;
		}
		bool removeAt(int index) {
			if (index < 0 || index >= count) return false;

			if (index == 0) return pop();//Delete head

			Node* p = head;
			Node* pPre = nullptr;
			int i = index;
			while (i++) {//Delete mid
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

		//TIMEQUEUE ONLY
		void blueHelper(int num, imp_res* restaurant) {
			Node* p = head;
			int i = 0;
			for (; p != nullptr; ++i, p = p->next) {

			}
		}

		Node* front() {
			return head;
		}
		int indexOf(customer* target) {
			Node* p = head;
			int i = 0;
			while (p && i < count) {
				if (p->data->name == target->name) return i;
				i++;
				p = p->next;
			}
			return -1;
		}
		Node* get(int index) {
			Node* p = head;
			int i = 0;
			while (p && i < index) {
				i++;
				p = p->next;
			}
			return p;
		}
		Node* get(customer* target) {
			Node* p = head;
			int i = 0;
			while (p->data->name != target->name && i < count) {
				i++;
				p = p->next;
			}
			return p;
		}


		int getSize() {
			return count;
		}
		bool empty() {
			return count == 0;
		}

		int findMaxAbsIndex() {
			Node* p = head;
			int resIndex = 0;
			Node* resNode = head;

			int i = 0;
			for (; i < count; i++, p = p->next) {
				bool choose = false;
				if (p->getData()->energy == resNode->getData()->energy) {
					if (p->getJoinTime() > resNode->getJoinTime()){
						choose = true;
					}
				}
				else if (p->getData()->energy > resNode->getData()->energy) {
					choose = true;
				}
				if (choose) {
					resNode = p;
					resIndex = i;
				}
			}

			return resIndex;
		}

	public:
		class Node {
		private:
			customer* data;
			Node* next;
			int joinTime;

		public:
			bool isInTable;
			friend class QueueModified;
			Node(customer* data, int joinTime = 0, Node* next = nullptr) {
				this->data = new customer(*data);
				this->joinTime = joinTime;
				this->next = next;
				isInTable = false;
			}
			customer* getData() {
				return data;
			}
			int getJoinTime() {
				return joinTime;
			}

			bool operator<(Node* other) {
				if (other->data->energy == this->data->energy) {
					return this->joinTime > other->joinTime;
				}
				else {
					return this->data->energy < other->data->energy;
				}
			}
			static void swap(Node* nodei, Node* nodej) {//Only swap data
				customer* cusTemp = nodei->data;
				nodei->data = nodej->data;
				nodej->data = cusTemp;
			}
		};
	};
#pragma endregion

	QueueModified* waitQueue;
	QueueModified* timeQueue;

public:	
	imp_res() {
		lastChange = nullptr;
		waitQueue = new QueueModified(MAXSIZE);
		timeQueue = new QueueModified(2 * MAXSIZE);
	};

	customer* findHighRES(int energy) {
		//FROM LAST CHANGE POSITION
		customer* CusHighRES = lastChange;

		int maxRES = abs(abs(energy) - abs(lastChange->energy));
		int i = 0;

		for (customer* p = lastChange; i != count; ++i, p = p->next) {
			int diff = abs(energy - p->energy);//FORUM
			if (maxRES < diff) {
				maxRES = diff;
				CusHighRES = p;
			}
		}

		return CusHighRES;
	}
	void addToTable(customer* cus) {
		count++;

		if (!lastChange) { // Table empty
			lastChange = cus;
			lastChange->next = lastChange->prev = lastChange; //Cycle
			return;
		}

		if (count >= int(MAXSIZE / 2)) lastChange = findHighRES(cus->energy);

		if (cus->energy >= lastChange->energy) { //Add right
			cus->next = lastChange->next;
			cus->prev = lastChange;
			lastChange->next = cus;
		}
		else {	//Add left
			cus->prev = lastChange->prev;
			cus->next = lastChange;
			lastChange->prev = cus;
		}

		lastChange = cus;
		timeQueue->get(cus)->isInTable = true;
	}
	void RED(string name, int energy){
		customer* cus = new customer(name, energy, nullptr, nullptr);

		if (energy == 0) return;//Deny normies
		if (timeQueue->indexOf(cus) != -1) return;//Check name
		if (waitQueue->getSize() == MAXSIZE) return;//Fully full

		timeQueue->push(cus);//Always add to timeline

		if (count == MAXSIZE) {
			waitQueue->push(cus);
			return;
		}
		addToTable(cus);
	}

	bool tableRemove(customer* target){
		if (!lastChange) return;
		
		customer* p = lastChange;
		int i = 0;

		for (int i = 0; i < count; ++i, p = p->next) {
			if (p->name == target->name) break;
		}

		if (p) {
			count--;
			//SET NEW LASTCHANGE
			if (count == 0) lastChange = nullptr;
			else {
				if (p->energy > 0) lastChange = p->next;
				else lastChange = p->prev;
			}

			p->next->prev = p->prev;
			p->prev->next = p->next;
			p->next = p->prev = nullptr;
			delete p;
				
			return true;
		}
		return false;
	}
	void BLUE(int num)
	{
		timeQueue->blueHelper(num, this);

		while (!waitQueue->empty() && count < MAXSIZE) {
			customer* p = waitQueue->front()->getData();
			customer* cus = new customer(p->name, p->energy, nullptr, nullptr);
			addToTable(cus);//BY PASS RED CHECK
			waitQueue->pop();
		}
	}


#pragma region shellsort

	void inssort2(int n, int incr) {
		for (int i = incr; i < n; i += incr)
			for (int j = i; (j >= incr); j -= incr) {
				//Stop when j-incr <= j
				QueueModified::Node* nodej = waitQueue->get(j);
				QueueModified::Node* nodejsubIncr = waitQueue->get(j - incr);

				if (!(nodej < nodejsubIncr)) break;
				swapCount++;
				QueueModified::Node::swap(nodej, nodejsubIncr);
			}
	}

	int shellSort() {
		swapCount = 0;

		int n = waitQueue->findMaxAbsIndex() + 1;

		for (int i = n / 2; i > 2; i /= 2) // For each increment
			for (int j = 0; j < i; j++) // Sort each sublist
				inssort2(n - j, i);
		inssort2(n, 1);

		return swapCount;
	}
#pragma endregion

	void PURPLE()
	{
		int N = shellSort();

		BLUE(N);
	}

	void REVERSAL()
	{
		if (count <= 1) return;

		QueueModified* sorcerers = new QueueModified(MAXSIZE);
		QueueModified* spirits = new QueueModified(MAXSIZE);
		customer* p = lastChange;
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

	void tablePrint() {
		
	}
};