#include <iostream>
#include <cmath>
#include<queue>
using namespace std;

// Concepts to Cover: 
// 
// Done - constructor, destructor
// Done - operator overloading, function overloading
// Done - base initialization for constructors
// - virtual functions, pure virtual functions
// - inheritance
// - stl functions: stack, queue, hash table, tree.
// - this pointer
// - inner classes
// - memory management - new, delete, where does memory reside?, virtual functions (vtable), etc
// Done - namespaces
// - scope
// - copy constructor

class Car
{
    // default is private
    string carName;
    int *ptr;

    public:
    Car() : carName("Accord"), ptr(new int) { *ptr = 11; }

    // Car(string inCar = "Tesla")
    // {

    // }

    Car(string inCar, int inVal = 5)
    {
        carName = inCar;

        ptr = new int;
        *ptr = inVal;
    }

    ~Car() {
        cout << "Obj ptr: " << this << endl;
        delete ptr;
        ptr = NULL;
    }

    // Operator Overloading (Polymorphism)
    Car operator + (Car &b) {
        Car c;
        *(c.ptr) = *(ptr) + *(b.ptr);
        return c;
    }

    // Function Overloading (Polymorphism)
    void setCarName(string inCar)
    {
        carName = inCar;
    }

    void setCarName(string inCar, int inVal)
    {
        carName = inCar;
        *ptr = inVal;
    }

    string getCarName()
    {
        return carName;
    }

    int getPtrVal()
    {
        return *ptr;
    }
};

int main()
{
    int iter = 19;
    queue<Car *> carq;

    // create reference
    int &myRef = iter;

    cout << "Hello: " << myRef << endl;
    myRef = 20;

    Car myCar("Camaro");
    //myCar.setCarName("Camaro");
    cout << "My car name is: " << myCar.getCarName() << " and Val is: " << myCar.getPtrVal() << "\n";

    Car *mySecondCar = new Car;
    mySecondCar->setCarName("Camry", myRef);
    cout << "mySecondCar is: " << mySecondCar->getCarName() << " and Val is: " << mySecondCar->getPtrVal() << "\n";

    Car myThirdCar = myCar + *mySecondCar;
    cout << "myThirdCar is: " << myThirdCar.getCarName() << " and Val is: " << myThirdCar.getPtrVal() << "\n";

    carq.push(&myCar);
    //carq.push(*mySecondCar);
    //carq.push(myThirdCar);

    carq.pop();
    // carq.pop();
    //carq.pop();

    carq.front

    mySecondCar->~Car();
    //delete mySecondCar;

    return 10;
}