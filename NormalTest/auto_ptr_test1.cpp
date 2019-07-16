/*
 * Note: auto_ptr is deprecated in C++11
 *
 */

#include <iostream>
#include <memory>

using namespace std;

class A
{
	public:
		void show()
		{
			cout << "A::show()" << endl;
		}
};


int main()
{
	auto_ptr<A> p1(new A);
	p1->show();

	// return the memory address of p1
	cout << p1.get() << endl;

	// copty constructor called, this makes p1 empty
	auto_ptr<A> p2(p1);
	p2->show();

	// p1 is empty now
	cout << p1.get() << endl;

	// p1 gets copied in p2
	cout << p2.get() << endl;

	return 0;
}

