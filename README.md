#Events

*by Terry Mahaffey*

Events is a functional based event system - an alternative to the classical OO Observer pattern. Let's say you have a class, Foo. You can add an event like this

    class Foo
    {
    public:
        Event0<Foo> Changed;
    };

You can then subscribe to the Changed event like this:

    Foo f;
    int token = f.Changed.Register(Bar);

Where Bar can be any C++ functor (a function pointer, a functor object, a lambda if your compiler supports it, etc). The returned token can be used to Unregister later, if desired. If someone calls Fire on the Changed event, Bar is called.

The Fire method of the Event0 class is private (and Foo is granted friendship, so the Foo class can fire the events). If this isn't desired, you can use the PuclicEvent0 object instead:

    class Foo
    {
    public:
        PublicEvent0 Changed;
    };

This behaves just as before, except anyone can call the Fire method on the Changed object, not just the Foo class. Note that there is no template parameter in this version.

Events can also take parameters. There are different sets of objects for the various arities, in both normal and public versions. To delcare an event which takes and int, a char, and a float, you'd do this:

    class Foo
    {
    public:
        PublicEvent3<int,char,float> SomethingHappened;
    };

When you register for this event, you have to provide a functor which takes the appropriate arguements. When you fire the event, you have to provide the arguements.

Taking from C#, operator+= and operator-= have been overridden to basically alias Register and Unregister. So the following syntax is possible, if you prefer:

    Foo f;
    f.Changed += []() {
        std::cout << "Foo Changed!\n";
    });

This software is made available under the Boost license.
