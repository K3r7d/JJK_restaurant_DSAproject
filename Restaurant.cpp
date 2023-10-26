#include "main.h"

// extern int MAXSIZE;



class imp_res : public Restaurant
{
    class Queue{
        private:
            customer* head = nullptr;
            customer* tail = nullptr;
            int size = 0;  
        public:
            Queue(){head = nullptr; tail = nullptr; size = 0;}
            
            ~Queue(){
                customer* temp = head;
                while(temp != nullptr){
                    customer* next = temp->next;
                    delete temp;
                    temp = next;
                }
                head = nullptr;
                tail = nullptr;
                size = 0;
            }

            void enqueue(customer* c){
                customer* temp = new customer(c->name, c->energy, nullptr, nullptr);
                if(head == nullptr){
                    head = temp;
                    tail = temp;
                    size++;
                }
                else{
                    tail->next = temp;
                    temp->prev = tail;
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
                    temp->next = nullptr;
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
                //debug
                // customer* temp = head;
                // cout<<"[ ";
                // cout<<"head-> ";
                // while(temp != nullptr){
                //     cout<<temp->name<<":"<<temp->energy<<" -> ";
                //     temp = temp->next;
                // }
                // cout<<"tail ]"<<endl;
                customer* temp = head;
                for(int i = 0;i<size;i++){
                    temp->print();
                    temp = temp->next;
                }
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
            customer* prev = nullptr;

            while (temp != nullptr) {
                if (temp->name == name) {
                    if (temp == head) {
                        head = temp->next;
                    }
                    if (temp == tail) {
                        tail = prev;
                    }
                    if (prev != nullptr) {
                        prev->next = temp->next;
                    }
                    if (temp->next != nullptr) {
                        temp->next->prev = prev;
                    }
                    delete temp;
                    size--;
                    return;
                }
                prev = temp;
                temp = temp->next;
            }
        }

        

        void removeAll(bool positive) {
            if (tail == nullptr) return;

            customer* temp = tail;
            customer* next = nullptr;

            while (temp != nullptr) {
                next = temp->prev;
                if ((positive && temp->energy > 0) || (!positive && temp->energy < 0)) {
                    temp->print();
                    removebyname(temp->name);
                }
                temp = next;
            }
        }

        void removeAllnotCout(bool positive) {
            if (tail == nullptr) return;

            customer* temp = tail;
            customer* next = nullptr;

            while (temp != nullptr) {
                next = temp->prev;
                if ((positive && temp->energy > 0) || (!positive && temp->energy < 0)) {
                    removebyname(temp->name);
                }
                temp = next;
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

            bool isSmaller(int idx1, int idx2){
                customer* temp = head;
                for(int i = 0;i<idx1;i++){
                    temp = temp->next;
                }
                customer* temp2 = head;
                for(int i = 0;i<idx2;i++){
                    temp2 = temp2->next;
                }
                return abs(temp->energy) < abs(temp2->energy);
            }     

            void swapatIndex(int a,int b){
                customer* temp = head;
                for(int i = 0;i<a;i++){
                    temp = temp->next;
                }
                customer* temp2 = head;
                for(int i = 0;i<b;i++){
                    temp2 = temp2->next;
                }
                swapNameandEnergy(temp, temp2);
            }       

            void ShellSort(int n, int& countofshellsort) {
                customer * temp = head;
                for(int i = n/2;i>2;i/=2){
                    for(int j = 0;j<i;j++){
                        inssort2(countofshellsort, n-j, i);
                    }
                }
                inssort2(countofshellsort, n, 1);
            }

            void inssort2(int& countofshellsort, int n, int incr) {
                for(int i = incr;i<n;i+=incr){
                    for(int j = i;j>= incr && isSmaller(j-incr,j);j-=incr){
                        swapatIndex(j-incr,j);
                        countofshellsort++;
                    }
                }
            }


            int Purple(){
                if(head == nullptr) return 0;
                customer* temp = head;
                int max = INT32_MIN;
                customer* last = nullptr;
                int n = 0;
                for(int i = 0;i<size;i++){
                    if(abs(temp->energy) >= max){
                        max = abs(temp->energy);
                        last = temp;
                        n = i+1; 
                    }
                    temp = temp->next;
                }    
                int countofshellsort = 0;
                ShellSort(n, countofshellsort);
                return countofshellsort;
            }

            bool isInQueue(customer* c){
                customer* temp = head;
                for(int i = 0;i<size;i++){
                    if(temp->name == c->name){
                        return true;
                    }
                    temp = temp->next;
                }
                return false;
            }
            

    };
        private:
            customer* head;
            int size;
            customer* X;
            Queue eating;
            Queue waiting;
            Queue order;

        public:
        imp_res(){
            head = new customer("head", 0, nullptr, nullptr);
            size = 0;
            X = nullptr;
        }

        ~imp_res(){
            free();
            head = nullptr;
            X = nullptr;
            size = 0; 
        }

        void free(){
            customer* temp = head->next;
            for(int i = 0;i<size;i++){
                customer* next = temp->next;
                delete temp;
                temp = next;
            }
            head->next = nullptr;
        }


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
                        X = temp->energy > 0 ? temp->next : temp->prev;
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

        void insert(customer* c){
            customer* temp = new customer(c->name, c->energy, nullptr, nullptr);
            if(head->next == nullptr){
                head->next = temp;
                temp->next = temp;
                temp->prev = temp;
                size++;
            }
            else{
                temp->next = head->next;
                temp->prev = head->next->prev;
                head->next->prev->next = temp;
                head->next->prev = temp;
                size++;
            }
        }

        void inserttoorder(customer* c){
            if(order.isInQueue(c))return;
            else{
                order.enqueue(c);
                return;
            }
        }

        void RED(string name, int energy){
            customer* c = new customer(name, energy,nullptr,nullptr);
            if(isInList(name)|| energy == 0||(isFull() && waiting.isFull())) return;
            inserttoorder(c);
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
                return;
            }
            if(size>=MAXSIZE/2){
                customer* temp = X;
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
                temp = X;
                for(int i = 0;i<max_index;i++){
                    temp = temp->next;
                }
                int RES  = c->energy - temp->energy;
                X = temp;
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
        };

		void BLUE(int num){
            if (isEmpty()) return;
            if (num > size) num = size;
            for(int i = 0; i<num;i++){
                customer* temp = order.dequeue();
                // cout<<"remove "<<temp->name<<endl;
                removebyname(temp->name);
                
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
            if (countofshellsort) BLUE(countofshellsort % MAXSIZE);
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
            string name = X->name;
            Posreverse(X);
            Negreverse(X);
            changeX(name);
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
            min = INT32_MAX;
            customer* min_node = nullptr;
            int min_idx = 0;
            for(int i = 0;i<max_length;i++){
                if(temp->energy < min){
                    min = temp->energy;
                    min_idx = i;
                    min_node = temp;
                }
                temp = temp->next;
            }

            temp = min_node;
            for(int i = min_idx;i<max_length;i++){
                temp->print();
                temp = temp->next;
            }
            temp = StartOfSublist;
            for(int i = 0;i<min_idx;i++){
                temp->print();
                temp = temp->next;
            }
        };
		
		void DOMAIN_EXPANSION(){
            if(size<2) return;
            if (isEmpty()) return;
            //take sum
            int sorcerer = order.sumAllEnergy(true);
            int curse = order.sumAllEnergy(false);
            
            //check condition
            if(sorcerer >= abs(curse)){
                waiting.removeAllnotCout(false);
                order.removeAll(false);
                int count = size;
                customer* temp = X;
                for(int i = 0;i<count;i++){
                    customer* next = temp->next;
                    if(temp->energy < 0){
                        string name = temp->name;
                        removebyname(name);
                    }
                    temp = next;
                }

            }
            else{
                waiting.removeAllnotCout(true);
                order.removeAll(true);
                int count = size;
                customer* temp = X;
                for(int i = 0;i<count;i++){
                    customer* next = temp->next;
                    if(temp->energy > 0){
                        string name = temp->name;
                        removebyname(name);
                    }
                    temp = next;
                }
            }
            while(!waiting.isEmpty() && !isFull()){
                customer* temp = waiting.dequeue();
                RED(temp->name, temp->energy);
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
            else if(num < 0) {
                for (int i = 0; i < size; i++) {
                    temp->print();
                    temp = temp->prev;
                }
            }
            else {
                waiting.print();
            }

            // //DEBUGGGGG
            // cout<<"------------------------"<<endl;
            // cout<<"Ordered Queue: ";
            // order.print();
            // cout<<"X: "<<X->name<<endl;
            // cout<<"------------------------"<<endl;
            // cout<<"Waiting Queue: ";
            // waiting.print();
        }

};
