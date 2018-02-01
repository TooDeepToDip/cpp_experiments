==Covariant types==

If you using OOP and programming with interfaces, you can face with dynamic casting need. Sad but true. Specially if you are not so good architector.

But in some cases you can define type on the spot even if using common base class. For example, you have hierarchically depended objects of different classes. And for visualisation, you inherit them from base node. But in other part of code each object knows what is its "parent".
It's time to covariant types! Each of objects can return base node and really parent at once. Almost.

===Simple (degenerate) case===

Inheritance and dependency schemes match.

For scheme (inheritance and dependency):
```
[ A ]
  ^
  |
[ B ]
  ^
  |
[ C ]
```
you can write something like this:
```
C c;
B& parentOfC = c.parent();
// using B:: members
// or
A& parentOfC = c.parent();
// and using base functionality
```

===Normal case===

For inheritance scheme:
```
      [ A ]
      ^ ^ ^
     /  |  \
[ B ] [ D ] [ E ]
```
and dependency scheme:
```
[ B ]
  ^
  | (parent)
[ D ]
  ^
  | (parent)
[ E ]
```
you can write something like this:
```
E e;
D& parentOfE = e.parent();
// using D:: members
// or
A& parentOfE = e.parent();
// and using base node functionality
```
