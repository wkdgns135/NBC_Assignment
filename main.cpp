#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Animal abstract {
public:
	virtual void makeSound() abstract;
};

class Dog : public Animal {
	void makeSound() override {
        cout << "¸Û" << '\n';
	}
};

class Cat : public Animal {
	void makeSound() override {
        cout << "³É" << '\n';
	}
};

class Cow : public Animal {
	void makeSound() override {
        cout << "À½¸Ó" << '\n';
	}
};

class Zoo {
private:
    Animal* animals[10];
    int index = 0;
    
public:
    void addAnimal(Animal* animal) {
        if (index == 10) {
            cout << "addAnimal ºÒ°¡. ¹è¿­ÀÌ °¡µæ Ã¡½À´Ï´Ù." << '\n';
            return;
        }
        animals[index++] = animal;
    }

    void performActions() {
        for (int i = 0; i < index; i++) {
            animals[i]->makeSound();
        }
    }

    ~Zoo() {
        for (int i = 0; i < index; i++)delete animals[i];
    }
};

Animal* createRandomAnimal(){
    switch (rand() % 3) {
        case 0: return new Dog();
        case 1: return new Cat();
        case 2: return new Cow();
        default: return new Dog();
    }
}

int main() {
    srand((unsigned int)time(NULL));

    Zoo zoo;
    for (int i = 0; i < 10; i++) {
        zoo.addAnimal(createRandomAnimal());
    }
    zoo.addAnimal(createRandomAnimal());
    zoo.performActions();
}