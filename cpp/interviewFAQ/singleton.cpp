#include <iostream>

using namespace std;

class Singleton {
    private:
        static Singleton *instance;
    public:
        Singleton(void)
        {
            cout << "Singleton constructor invoked\n";
        }

        static Singleton* getInstance(void)
        {
            if (!instance) {
                instance = new Singleton();
            }
            return instance;
        }

        static void deleteInstance(void) { delete instance; cout << "Destructor called \n"; }

};

Singleton* Singleton::instance = nullptr;

int
main(void)
{
    Singleton *ptr1 = Singleton::getInstance();
    Singleton *ptr2 = Singleton::getInstance();
    cout << "ptr1 = " << ptr1 << ", ptr2 = " << ptr2 << "\n";
    Singleton::deleteInstance();
    return 0;

}
