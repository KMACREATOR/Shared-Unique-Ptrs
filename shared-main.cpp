#include <stdio.h>
#include <iostream>


using namespace std;

template<class T>
class MyShared
{
    T * p=nullptr;
	//для MyShared необходим счетчик созданных указателей
	int* count = nullptr;
	
	
public:

	//конструктор по "сырому" указателю
    MyShared(T *p){
		this->p = p;
		this->count = new int(1);
	}
		
	//конструктор копирования
	MyShared(const MyShared& mu) : p(mu.p), count(mu.count) {
        ++(*count);
    }
	
	//конструктор перемещения
	MyShared(MyShared&& mu) noexcept : p(mu.p), count(mu.count) {
        mu.p = nullptr;
        mu.count = nullptr;
    }
	
	
	//здесь в деструкторе нужно уничтожать счетчик
    ~MyShared() {
        if (--(*count) == 0) {
            delete p;
            delete count;
            cout << "Destruct" << endl;
        }
    }
	
	//get() метод	
    T * get() const{
		return p;
	}
	
	//перегрузка "*"
    T & operator*(){
		return *p;
	}
	
	//перегрузка "->"
    T * operator->(){
		return p;
	}	
	
	//перегрузка "=" для копирования 
	MyShared& operator=(const MyShared& mu) {
        if (this != &mu) {
            if (--(*count) == 0) {
                delete p;
                delete count;
            }
            p = mu.p;
            count = mu.count;
            ++(*count);
        }
        return *this;
    }

	
	
	//перегрузка "=" для перемещения
	MyShared& operator=(MyShared&& mu) noexcept {
		if (this != &mu) {
			delete p;
			p = mu.p;
			mu.p = nullptr;
		}
		return *this;
		}
};


template<typename T, typename...Args>
T* MakeMyShared(const Args& ... args)
{
	return new T(args...);
}



class Package{
	public:
	float width;
	float height;
	float depth;
	float mass;
	Package(float w, float h, float d, float m) : width(w), height(h), depth(d), mass(m){}
	void print(){
		cout << "Width:\t" << width << "\nHeight:\t" << height << "\nDepth:\t" << depth << "\nMass:\t" << mass << endl;
		}
	
	};
	
int main(){
	MyShared<Package> pP1 = MakeMyShared<Package>(120.3, 240.6, 13.7, 230.6);
	//реализация копирования
	auto pP2 = pP1;
	pP1->print();
	pP2->print();
	}	
