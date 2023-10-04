#include "main.h"

class imp_res : public Restaurant
{
private:
	customer* table;
	customer* lastChange;

	int count = 0;

#pragma region customPrivateMethods
	void lastChange_reset() {//Delete ghost node
		if (lastChange->energy == 0) {
			lastChange->prev->next = lastChange->next;
			lastChange->next->prev = lastChange->prev;
			delete lastChange;
		}
	}
#pragma endregion

#pragma region customSubClasses
	//TODO NameBST
	class NameBST {
		class BSTNode;
	private:
		BSTNode* bst;
		int maxsize;
		int count;

		class BSTNode {
		public:
			BSTNode *left, *right;
			string name;

			BSTNode() {
				left = right = nullptr;
				name = "";
			}
			BSTNode(string name) {
				left = right = nullptr;
				this->name = name;
			}
			~BSTNode() { delete left; delete right; }
		};
	public:
		NameBST() : bst(nullptr), maxsize(0), count(0) {}
		NameBST(int SIZE) : bst(nullptr), maxsize(SIZE), count(0) {}
		~NameBST() {
			delete bst;
		}


	};
#pragma endregion


public:	
	imp_res() {
		table = lastChange = nullptr;
	};

	void RED(string name, int energy)
	{
		if (energy == 0) return;//Deny

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
			lastChange_reset();
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