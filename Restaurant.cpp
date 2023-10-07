#include "main.h"

extern int MAXSIZE;



class imp_res : public Restaurant
{
    class Queue{
        private:
            customer* head = nullptr;
            customer* tail = nullptr;
            int size = 0;  
        public:
            Queue(){head = nullptr; tail = nullptr; size = 0;}
            

            void enqueue(customer* c){
                customer* temp = new customer(c->name, c->energy, nullptr, nullptr);
                if(head == nullptr){
                    head = temp;
                    tail = temp;
                    size++;
                }
                else{
                    tail->next = temp;
                    tail = temp;
                    size++;
                }
            }
            customer* dequeue(){
                if(head == nullptr){
                    return nullptr;
                }
                else{
                    customer* temp = head;
                    head = head->next;
                    size--;
                    return temp;
                }
            }
            bool isEmpty(){
                return size == 0;
            }
            bool isFull(){
                return size == MAXSIZE;
            }
            void print(){
                customer* temp = head;
                cout<<"[ ";
                cout<<"head-> ";
                while(temp != nullptr){
                    cout<<temp->name<<":"<<temp->energy<<" -> ";
                    temp = temp->next;
                }
                cout<<"tail ]"<<endl;
            }
            int getSize() const{
                return size;
            }
            customer* getHead() const{
                return head;
            }
            int sumAllEnergy(bool positive){
                customer* temp = head;
                int sum = 0;
                while(temp != nullptr){
                    if(positive){
                        if(temp->energy > 0){
                            sum += temp->energy;
                        }
                    }
                    else{
                        if(temp->energy < 0){
                            sum += temp->energy;
                        }
                    }
                    temp = temp->next;
                }
                return sum;
            }
            void removeAll(bool positive){
                customer* temp = head;
                while(temp != nullptr){
                    if(positive){
                        if(temp->energy > 0){
                            customer* temp2 = dequeue();
                            cout<<"Remove "<<temp2->name<<endl;
                            delete temp2;
                        }
                    }
                    else{
                        if(temp->energy < 0){
                            customer* temp2 = dequeue();
                            cout<<"Remove "<<temp2->name<<endl;
                            delete temp2;
                        }
                    }
                    temp = temp->next;
                }
            }
            

    };
    private:
        customer* head;
        int size;
        customer* X;
        Queue eating;
        Queue waiting;
    public:
    imp_res(){
        head = new customer("head", 0, nullptr, nullptr);
        size = 0;
        X = nullptr;
        eating = Queue();
        waiting = Queue();
    };
        void Addnext(customer* cus) {
            cus->next = X->next;
            X->next->prev = cus;
            cus->prev = X;
            X->next = cus;
            size++;
        }
        void changeX(string name){
            customer* temp = head->next;
            for(int i = 0; i < size; i++){
                if(temp->name == name){
                    X = temp;
                    return;
                }
                temp = temp->next;
            }
        }

        void addPrev(customer* cus) {
            cus->prev = X->prev;
            X->prev->next = cus;
            cus->next = X;
            X->prev = cus;
            size++;
        }


        void removebyname(string name) {
            customer* temp = head->next;
            if (head->next == nullptr) {
                return;
            }
            else {
                for (int i = 0; i < size; i++) {
                    if (temp->name == name) {
                        if(temp == head->next){
                            head->next = temp->next;
                        }
                        if(temp == X){
                            X = nullptr;
                        }
                        temp->prev->next = temp->next;
                        temp->next->prev = temp->prev;
                        temp->next = nullptr;
                        temp->prev = nullptr;
                        delete temp;
                        size--;
                        return;
                    }
                    temp = temp->next;
                }
            }
        }


        bool isEmpty(){
            return size == 0;
        }
        bool isFull(){
            return size == MAXSIZE;
        }

        bool isInList(string name){
            customer* temp = head->next;
            for(int i = 0; i < size; i++){
                if(temp->name == name){
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }

        

        void RED(string name, int energy){
            customer* c = new customer(name, energy,nullptr,nullptr);
            if(isInList(name)|| energy == 0||(isFull() && waiting.isFull())) return;
            if(isFull()){
            waiting.enqueue(c);
            return;    
            } 
            if(isEmpty()){
                c->next = c;
                c->prev = c;
                X = c;
                head->next = c;
                size++;
                eating.enqueue(c);
                return;
            }
            if(size>=MAXSIZE/2){
                customer* temp = head->next;
                int max = INT32_MIN;
                int max_index = 0;
                for(int i = 0;i<size;i++){
                    int RES = abs(abs(temp->energy)-abs(c->energy));
                    if(RES>max){
                        max = RES;
                        max_index = i;
                    }
                    temp = temp->next;
                }
                temp = head->next;
                for(int i = 0;i<max_index;i++){
                    temp = temp->next;
                }
                int RES  = abs(temp->energy)-abs(c->energy);
                if (RES < 0)
                addPrev(c);
                else 
                Addnext(c);
            }
            else
            {
                if(energy >= X->energy){
                    Addnext(c);

                }
                else{
                    addPrev(c);
                }
            }
            eating.enqueue(c);
        };

		void BLUE(int num){
            if (isEmpty()) return;
            for(int i = 0; i<size;i++){
                customer* temp = eating.dequeue();
                removebyname(temp->name);
                if(X ==nullptr){
                    changeX(eating.getHead()->name);
                }
            }
            for(int i = 0; i < waiting.getSize();i++){
                customer* temp = waiting.dequeue();
                RED(temp->name, temp->energy);
            }
        };
		
        void PURPLE(){};
		
		void REVERSAL(){};
		
		void UNLIMITED_VOID(){};
		
		void DOMAIN_EXPANSION(){
            if (isEmpty()) return;
            int soccerer = eating.sumAllEnergy(true) + waiting.sumAllEnergy(true);
            int curse = eating.sumAllEnergy(false) + waiting.sumAllEnergy(false);
            if(soccerer >= abs(curse)){
                eating.removeAll(false);
                waiting.removeAll(false);
                for(int i = 0;i<size;i++){
                    customer* temp = head->next;
                    if(temp->energy < 0){
                        removebyname(temp->name);
                    }
                    temp = temp->next;
                }
                if(X == nullptr){
                    changeX(eating.getHead()->name);
                }
            }
            else{
                eating.removeAll(true);
                waiting.removeAll(true);
                for(int i = 0;i<size;i++){
                    customer* temp = head->next;
                    if(temp->energy > 0){
                        removebyname(temp->name);
                    }
                    temp = temp->next;
                }
                if(X == nullptr){
                    changeX(eating.getHead()->name);
                }
            }
        };
		
		void LIGHT(int num) {
            if (isEmpty()) return;
            customer* temp = X;
            if (num > 0) {
                for (int i = 0; i < size; i++) {
                    temp->print();
                    temp = temp->next;
                }
            }
            else {
                for (int i = 0; i < size; i++) {
                    temp = temp->prev;
                    temp->print();
                }
            }
            cout<<"------------------------"<<endl;
            cout<<"Eating Queue: ";
            eating.print();
            cout<<"X: "<<X->name<<endl;
            cout<<"------------------------"<<endl;
            cout<<"Waiting Queue: ";
            waiting.print();
        }

};
