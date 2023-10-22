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

            customer* getTail() const{
                return tail;   
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
                delete temp;
                return sum;
            }

        void removebyname(string name) {
            customer* temp = head;
            if (head == nullptr) {
                return;
            }
            else {
                for (int i = 0; i < size; i++) {
                    if (temp->name == name) {
                        if(temp == head){
                            head = temp->next;


                        }
                        if(temp == tail){
                            tail = temp->prev;
                        }
                        if(temp->next != nullptr){
                            temp->next->prev = temp->prev;
                        }
                        if(temp->prev != nullptr){
                            temp->prev->next = temp->next;
                        }
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
            

            void removeAll(bool positive){
                if(head == nullptr) return;
                customer* temp = head;
                int count = size;
                for(int i = 0;i<count;i++){
                    if(positive){
                        if(temp->energy > 0){
                            cout<<"Remove "<<temp->name<<endl;
                            string name = temp->name;
                            temp = temp->next;
                            removebyname(name);
                        }
                    }
                    else{
                        if(temp->energy < 0){
                            cout<<"Remove "<<temp->name<<endl;
                            string name = temp->name;
                            temp = temp->next;
                            removebyname(name);
                        }
                    }
                }
            }

            void swapNameandEnergy(customer* a, customer* b){
                string temp_name = a->name;
                int temp_energy = a->energy;
                a->name = b->name;
                a->energy = b->energy;
                b->name = temp_name;
                b->energy = temp_energy;
            }

            void ShellSort(customer* last, int& countofshellsort) {
                int gap = size / 2;
                while (gap > 0) {
                    customer* temp = head;
                    while (temp != last) {
                        customer* temp2 = temp;
                        for (int i = 0; i < gap; i++) {
                            if (temp2->next == nullptr) break;
                            temp2 = temp2->next;
                        }
                        if (temp->energy > temp2->energy) {
                            swapNameandEnergy(temp, temp2);
                            countofshellsort++;
                        }
                        temp = temp->next;
                    }
                    gap /= 2;
                }
            }


            int Purple(){
                if(head == nullptr) return 0;
                customer* temp = head;
                int max = INT32_MIN;
                customer* last = nullptr;
                for(int i = 0;i<size;i++){
                    if(temp->energy >= max){
                        max = temp->energy;
                        last = temp;
                    }
                    temp = temp->next;
                }    
                int countofshellsort = 0;
                ShellSort(last, countofshellsort);
                return countofshellsort;
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

        int sumofSublist(customer* c,int cap){
            int sum = 0;
            customer* temp = c;
            for(int i = 0;i<cap;i++){
                sum += temp->energy;
                temp = temp->next;
            }
            return sum;
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
                    int RES = abs(temp->energy-c->energy);
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
                int RES  = c->energy - temp->energy;
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
            X = c;
            eating.enqueue(c);
        };

		void BLUE(int num){
            if (isEmpty()) return;
            if (num > size) num = size;
            for(int i = 0; i<num;i++){
                customer* temp = eating.dequeue();
                removebyname(temp->name);
                if(X ==nullptr && !eating.isEmpty()){
                    changeX(eating.getTail()->name);
                }
            }
            int count = waiting.getSize();
            for(int i = 0; i < count;i++){
                customer* temp = waiting.dequeue();
                RED(temp->name, temp->energy);
            }
        };


        void PURPLE(){
            if (isEmpty()) return;
            int countofshellsort = waiting.Purple();
            if (countofshellsort) BLUE(countofshellsort);
        };
		
        void swapNameandEnergy(customer* a, customer* b){
            string temp_name = a->name;
            int temp_energy = a->energy;
            a->name = b->name;
            a->energy = b->energy;
            b->name = temp_name;
            b->energy = temp_energy;
        }

        void Posreverse(customer* c) {
            customer* a = c;
            customer* b = c->next;
            
            do {
                if(a->energy > 0 && b->energy <0) 
                    b = b->next;

                else if(a->energy < 0 && b->energy > 0)
                    a = a->prev;

                else if (a->energy > 0 && b->energy > 0) {
                    swapNameandEnergy(a, b);
                    b = b->next;
                    a = a->prev;
                } else if (a->energy < 0 && b->energy < 0){
                    a = a->next;
                    b = b->prev;
                }
            } while (b != a && b != a->next);
        }

        void Negreverse(customer* c) {
            customer* a = c;
            customer* b = c->next;

            do{
                if(a->energy > 0 && b->energy <0) 
                    a = a->prev;

                else if(a->energy < 0 && b->energy > 0)
                    b = b->next;

                else if (a->energy < 0 && b->energy < 0) {
                    swapNameandEnergy(a, b);
                    b = b->next;
                    a = a->prev;
                } else if (a->energy > 0 && b->energy > 0){
                    a = a->prev;
                    b = b->next;
                }
            }while(b != a && b != a->next);
        }


		void REVERSAL(){
            if(head->next == nullptr) return;
            Posreverse(X);
            Negreverse(X);
            changeX(eating.getTail()->name);
        };
		
		void UNLIMITED_VOID(){
            if(size<4) return;
            int length = 4;
            int min = INT32_MAX;
            int max_length = 4;
            customer* StartOfSublist = X;
            while(length <= size){    
                customer* temp = X;
                while(temp->next != X){
                    int sum = sumofSublist(temp,length);
                    if(sum < min){
                        min = sum;
                        max_length = length;
                        StartOfSublist = temp;
                    }
                    if(sum == min && length > max_length){
                        max_length = length;
                        StartOfSublist = temp;
                    }
                    temp = temp->next;
                }
                length++;
            }
            customer* temp = StartOfSublist;
            for(int i = 0;i<max_length;i++){
                temp->print();
                temp = temp->next;
            }
        };
		
		void DOMAIN_EXPANSION(){
            if (isEmpty()) return;
            //take sum
            int sorcerer = eating.sumAllEnergy(true) + waiting.sumAllEnergy(true);
            int curse = eating.sumAllEnergy(false) + waiting.sumAllEnergy(false);
            
            //check condition
            if(sorcerer >= abs(curse)){
                eating.removeAll(false);
                waiting.removeAll(false);
                int count = size;
                for(int i = 0;i<count;i++){
                    customer* temp = head->next;
                    if(temp->energy < 0){
                        string name = temp->name;
                        removebyname(name);
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
                int count = size;
                for(int i = 0;i<count;i++){
                    customer* temp = head->next;
                    if(temp->energy > 0){
                        string name = temp->name;
                        removebyname(name);
                    }
                    temp = temp->next;
                }
                if(X == nullptr){
                    changeX(eating.getTail()->name);
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
            // cout<<"------------------------"<<endl;
            // cout<<"Ordered Queue: ";
            // eating.print();
            // cout<<"X: "<<X->name<<endl;
            // cout<<"------------------------"<<endl;
            // cout<<"Waiting Queue: ";
            // waiting.print();
        }

};
