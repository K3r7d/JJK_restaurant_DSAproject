#include "main.h"

extern int MAXSIZE;


class imp_res : public Restaurant
{
	private:
		//circle doubly linked list
		customer *head;
		int size;
		customer *X;
    public:
    int getSize(){return size;} 

	class Queue
    {
    private:
        customer *c;
        int size_queue;
        customer *front;
        customer *rear;
        customer *curr;

    public:
        Queue() 
        {
            this->c = nullptr;
            this->front = nullptr;
            this->rear = nullptr;
            curr= nullptr;
            size_queue = 0;
        }
        ~Queue()
        {
            while (!isEmpty())
            {
                dequeue();
            }
        }
        bool isEmpty() const {return size_queue == 0;}
        bool isFull() const {return size_queue==MAXSIZE;}
        int getSize() const {return size_queue;}
        void DeleteTemp(){
            customer *temp = curr;
            if(curr == front){
                front = front->next;
                temp->next = nullptr;
                temp->prev = nullptr;
                size_queue--;
                return;
            }
            else{
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                curr->next = nullptr;
                curr->prev = nullptr;
                size_queue--;
                return;
            }
        }

        void deletebyEnergy(bool positive){
            if(isEmpty()) return;
            if (positive){
                curr = front;
                for(int i = 0;i<size_queue;i++){
                    if(curr->energy > 0){
                        curr->print();
                        DeleteTemp();
                    }
                    curr = curr->next;
                }
            }
            else
            {
                curr = front;
                for(int i = 0;i<size_queue;i++){
                    if(curr->energy < 0){
                        curr->print();
                        DeleteTemp();
                    }
                    curr = curr->next;
                }
            }
        }

        int sumEnergy(bool positive){
            int sum = 0;
            if(isEmpty()) return 0;
            if (positive){
                customer *temp = front;
                for(int i = 0;i<size_queue;i++){
                    if(temp->energy > 0){
                        sum += temp->energy;
                    }
                    temp = temp->next;
                }
            }
            else
            {
                customer *temp = front;
                for(int i = 0;i<size_queue;i++){
                    if(temp->energy < 0){
                        sum += temp->energy;
                    }
                    temp = temp->next;
                }
            }
            return abs(sum);
        }

        void enqueue(customer *newCustomer)
        {
            customer* temp = new customer(newCustomer->name, newCustomer->energy, nullptr, nullptr);
            if (isEmpty())
            {
                front = temp;
                rear = temp;
            }
            else
            {
                rear->next = temp;
                temp->prev = rear;
                rear = temp;
            }
            size_queue++;
        }
        customer *dequeue()
        {
            if (isEmpty())
            {
                return nullptr;
            }
            else
            {
                customer *temp = front;
                front = front->next;
                temp->next = nullptr;
                size_queue--;
                return temp;
            }
        }
        void QueuePrint()
        {
            customer *temp = front;
            for(int i = 0; i<size_queue;i++){
                temp->print();
                temp = temp->next;
            }
        }
    };



    private:
    Queue res_queue;
    Queue eating;
	public:	

		imp_res():  res_queue() , eating(), X(nullptr) {
            head = new customer("", 0, nullptr, nullptr);
        };


        void deleteByName(string name) {
            customer *temp = head->next;
            for(int i = 0;i<size;i++){
                if(temp->name == name){
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    temp->next = nullptr;
                    temp->prev = nullptr;
                    size--;
                    return;
                }
                temp = temp->next;
            }
        }


        bool isFull(){return size==MAXSIZE;};

		void RED(string name, int energy);

		void BLUE(int num);
		
        void PURPLE();
		
		void REVERSAL();
		
		void UNLIMITED_VOID();
		
		void DOMAIN_EXPANSION();
		
		void LIGHT(int num);
};
//region[rgba(255,0, 0, 0.16)]
void imp_res::RED(string name, int energy)
{
			
    customer *cus = new customer (name, energy, nullptr, nullptr);
	//precheck
    if(head->next == nullptr)
	{
        head->next = cus;
        cus->prev = head;
        cus->next = head;
        head->prev = cus;
        X = cus;
        size++;
        eating.enqueue(cus);
        return;
	}
    if(cus->energy == 0 || cus->name == X->name) return;
	if(isFull() && res_queue.isFull()) return;
    if(isFull()) {res_queue.enqueue(cus); return;}
    

	
	if (size >= MAXSIZE/2){
	    customer *temp = head->next;
        int max = INT32_MIN;
        int max_index = 0;
        for(int i = 0;i<size;i++){
            int RES = abs(cus->energy) - abs(temp->energy);
            if(RES > max){
                max = RES;
                max_index = i;
            }
            temp = temp->next;
        }
        temp = head->next;
        for(int i = 0;i<max_index;i++){
            temp = temp->next;
        }
        temp->prev = cus;
        cus->next = temp;
        cus->prev = temp->prev;
        temp->prev->next = cus;
        size++;
	}
    else
    {
        if(cus->energy >= X->energy){
            cus->next = X->next;
            X->next->prev = cus;
            cus->prev = X;
            X->next = cus;
            size++;
        }
        else
        {
            cus->prev = X->prev;
            X->prev->next = cus;
            cus->next = X;
            X->prev = cus;
            size++;
        }
        eating.enqueue(cus);
    }  
}
//endregion
//region[rgba(10,100,225,0.2)]
void imp_res::BLUE(int num){
    for(int i = 0;i<num;i++){
        if(eating.isEmpty()) return;
        customer *temp = eating.dequeue();
        deleteByName(temp->name);
    }
    for(int i = 0;i<num;i++){
        if(res_queue.isEmpty()) return;
        customer *temp = res_queue.dequeue();
        RED(temp->name, temp->energy);
    }
}
//endregion
//region[rgba(200,0,255,0.2)]
void imp_res::PURPLE(){

}
//endregion
//region[rgba(0,255,0,0.2)]
void imp_res::REVERSAL(){

}
//endregion
//region[rgba(0,0,0,1)]
void imp_res::UNLIMITED_VOID(){

}
//endregion
//region[rgba(200,200,200,0.3)]
void imp_res::DOMAIN_EXPANSION(){
    // int soccerer = eating.sumEnergy(true) + res_queue.sumEnergy(true);
    // int cursed = eating.sumEnergy(false) + res_queue.sumEnergy(false);
    // if(soccerer>=cursed){
    //     eating.deletebyEnergy(false);
    //     res_queue.deletebyEnergy(false);
    // }else
    // {
    //     eating.deletebyEnergy(true);
    //     res_queue.deletebyEnergy(true);
    // }
    eating.QueuePrint();
    cout<<"-----"<<endl;
    LIGHT(9);
    eating.deletebyEnergy(true);
}
//endregion
//region[rgba(225,225,255,0.08)]
void imp_res::LIGHT(int num)
{
    customer* temp = head->next;
    if(num>0){
        for(int i = 0; i<size;i++){
            temp->print();
            temp = temp->next;
        }
    }else if(num<0){
        for(int i = 0; i<size;i++){
            temp->print();
            temp = temp->prev;
        }
    }
    else {
        while(!eating.isEmpty()){
            temp = eating.dequeue();
            temp->print();
        }
    }
	// eating.QueuePrint();
	// cout<<"------------------"<<endl;
    // eating.dequeue();
	// eating.dequeue();
    // eating.QueuePrint();
    
}
