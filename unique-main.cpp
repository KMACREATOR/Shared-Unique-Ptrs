#include <stdio.h>
#include <iostream>


using namespace std;

template<class T>
class MyUnique
{
    T * p=nullptr;
public:
    MyUnique(T *p){
		this->p = p;
	}
	
	//конструктор копирования
	MyUnique(MyUnique& mu) : p(mu.p){}
	//передаем адрес ссылки
	
	//конструктор перемещения
	MyUnique(MyUnique&& mu) : p(mu.p){
		mu.p = nullptr; //передаем и обнуляем
	}
	
	
	//деструктор
    ~MyUnique(){
		delete p;
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
	
	
	//запрет создания копий объектов
	MyUnique(const MyUnique&) = delete;
	MyUnique& operator=(const MyUnique&) = delete;
	
	//перемещение
	MyUnique& operator=(MyUnique&& other) noexcept {
    if (this != &other) {
      delete p;
      p = other.p;
      other.p = nullptr;
    }
    return *this;
  }
};


template<typename T, typename...Args>
T* MakeMyUnique(const Args& ... args)
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
	MyUnique<Package> pP1 = MakeMyUnique<Package>(120.3, 240.6, 13.7, 230.6);
	pP1->print();
	}	
