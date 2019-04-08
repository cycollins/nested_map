Basically just an example of a recursive definition of a complex container, using variadic templates in C++17. Just has some useful details. I'm saving it mostly for my own benefit.

nested_map_base allows a programmer to make a single object that is a multi-dimensional mapping - a mapping of a mappting of a mapping, etc. Each key for each dimension of the mapping can be chosen individually, such that

  nested_map<int, std::string, double, int> test_map;

creates a container that ints (the first type in the template parameters) indexed by a string, a real, and an another int. Similar to the std::unordered_map, the main interface is the operator[]. Ints are added, retrieved, or modified with code like -

  test_map["angus"][4.8][35] = 200;
  int &handle = test_map["angus"][4.8][35];
  handle = 49;  // updates the value at the triple reference

It would require a gread deal more effort to make it useful. I didn't even give it any delete functions or iterators, but that would just obscure the essential recursive relationships, that I want to keep handy for similar serious projects in the future.
