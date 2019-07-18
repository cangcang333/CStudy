#include <iostream>
#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost;

int main()
{
	shared_ptr<int> p(new int(10));
	weak_ptr<int> w(p);
	while (!w.expired()) {
		std::cout << w.use_count() << std::endl;
		shared_ptr<int> t = w.lock();
		std::cout << *t << std::endl;
		std::cout << w.use_count() << std::endl;
		if (w.use_count() == 2) {
			break;
		}
	}

	w.reset();
	std::cout << "w " << (w.expired() ? "is" : "is not") << " expired" <<  std::endl;


	return 0;
}
