#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

using namespace boost;

class testWeak : public enable_shared_from_this<testWeak> {
public:
	int i;
	testWeak(int num) : i(num) {}
	void print() {
		std::cout << i << std::endl;
	}
};

int main()
{
	shared_ptr<testWeak> sp = make_shared<testWeak>(100);
	shared_ptr<testWeak> tw = sp->shared_from_this();
	tw->print();
}
