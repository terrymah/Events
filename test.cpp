#include "events.h"
#include <iostream>

using namespace mahaffey::events;

class Test
{
public:
    Event0<Test> ItemMoved;
    void Move() { ItemMoved.Fire(); }

    // Other random events..
    PublicEvent0 EventA;
    Event1<Test,int> EventB;
    PublicEvent1<int> EventC;
    Event2<Test,int,int> EventD;
    PublicEvent2<int,int> EventE;
    Event3<Test,int,int,int> EventF;
    PublicEvent3<int,int,int> EventG;
};

void Hi0()
{
    std::cout << "Hi0!\n";
}

void Hi1(int x)
{
    std::cout << "Hi1! " << x << "\n";
}

void Hi2(int x, int y)
{
    std::cout << "Hi2! " << x << " " << y << "\n";
}

void Hi3(int x, int y, int z)
{
    std::cout << "Hi3! " << x << " " << y << " " << z << "\n";
}

int main()
{
    Test t;

    // Register a callback when the ItemMoved event is fired
    int mine = t.ItemMoved += Hi0;
    // Same as above
    // int mine = t.ItemMoved.Register(Hi0); 

    // This line doesn't compile, Fire is a private method
    //t.ItemMoved.Fire();

    // Should print out "Hi0!"
    t.Move();

    // Unregister
    t.ItemMoved -= mine; 
    // Same as above
    // t.ItemMoved.Unregister(mine);

    // You can call Fire directly on public events
    t.EventA.Fire();

    // You can pass parameters to Events
    t.EventC += Hi1;
    t.EventC.Fire(42);

    t.EventE += Hi2;
    t.EventE.Fire(4, 20);

    t.EventG += Hi3;
    t.EventG.Fire(1, 2, 3);
}

