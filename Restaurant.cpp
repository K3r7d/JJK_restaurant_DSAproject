#include "main.h"



class imp_res : public Restaurant
{
	private:
		//circle doubly linked list
		customer *head;
		customer *tail;
		static int MAXSIZE;
		int size;
		customer *X;
	
	class Queue
    {
    private:
        customer *c;
        int MAXSIZE;
        int size;
        customer *front;
        customer *rear;

    public:
        Queue()
        {
            this->MAXSIZE = imp_res::MAXSIZE;
            this->c = nullptr;
            this->front = nullptr;
            this->rear = nullptr;
            size = 0;
        }
        ~Queue()
        {
            while (!isEmpty())
            {
                dequeue();
            }
        }
        bool isEmpty() const {return size == 0;}
        int getSize() const {return size;}

        void enqueue(customer *newCustomer)
        {
            if (size < MAXSIZE)
            {
                if (isEmpty())
                {
                    front = rear = newCustomer;
                }
                else
                {
                    rear->next = newCustomer;
                    newCustomer->prev = rear;
                    rear = newCustomer;
                }
                size++;
            }
        }
        customer *dequeue()
        {
            if (!isEmpty())
            {
                customer *removedCustomer = front;
                front = front->next;
                if (front)
                {
                    front->prev = nullptr;
                }
                removedCustomer->next = nullptr;
                size--;
                return removedCustomer;
            }
            else
            {
                return nullptr;
            }
        }
    };





	public:	
		imp_res() {};

		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
			if(cus->energy == 0 || cus->name == X->name) return;
			
			if(head == nullptr)
			{
				head = cus;
				tail = cus;
				cus->next = head;
				cus->prev = tail;
				size++;
				X = cus;
				return;
			}
			else if (size >= MAXSIZE/2){
				int RES = abs(X->energy - cus->energy);

			}
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