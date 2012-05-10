#include <iostream>
#include <ctime>
#include <vector>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition_variable.hpp>

using namespace std;

typedef int DT;
typedef void (*CallBack)(DT);

template <typename T>
class Wrapper {
	public:
		inline Wrapper(const T &_value) : value(_value) {

		}

		inline operator T&() {
			return value;
		}

		inline void onChange(CallBack flowTo) {
			callThese.push_back(flowTo);
		}

		inline void operator=(T newValue) {
			value = newValue;
			for(unsigned int i = 0; i < callThese.size(); i++) {
				callThese[i](newValue);
			}
		}

		inline void set(T newValue) {
			value = newValue;
		}

	private:
		T value;
		;
		//boost::condition_variable cond;
		//boost::mutex mut;
		vector<CallBack> callThese;
};

// Compiler added vars
Wrapper<DT> *ptrA = 0;
Wrapper<DT> *ptrB = 0;
DT *ptrSum = 0;

void aChanged(DT newA) {
	cout << "Recalc c based on new value of a." << endl;
	ptrA->set(newA);
	(*ptrSum) = newA + (*ptrB);
}

void bChanged(DT newB) {
	cout << "Recalc c based on new value of b." << endl;
	ptrB->set(newB);
	(*ptrSum) = (*ptrA) + newB;
}

DT main(DT argc, char *argv[]) {
	//x.setRecalcFunc();
	//y.setRecalcFunc(&recalcY);
	//z.setRecalcFunc(&recalcZ);

	/* a = 0
	 * b = 0
	 * a + b -> sum
	 */

	cout << "Init 1" << endl;
	Wrapper<DT> a = 0;
	Wrapper<DT> b = 0;
	DT sum = 0;

	cout << "Init 2" << endl;
	ptrA = &a;
	ptrB = &b;
	ptrSum = &sum;

	cout << "Init 3" << endl;
	a.onChange(&aChanged);
	b.onChange(&bChanged);

	cout << "Init 4" << endl;
	a = 7;
	b = 14;

	/*
	Wrapper<DT> x = a + b;
	Wrapper<DT> y = c - d;
	DT z = x * y;
	*/

	// 462
	// 336
	cout << "Init 5" << endl;
	cout << sum << endl;
	// gettimeofday(&startTime, 0);
	/*seconds  = endTime.tv_sec  - startTime.tv_sec;
	useconds = endTime.tv_usec - startTime.tv_usec;
	mtimeMT = ((seconds) * 1000 + useconds/1000.0) + 0.5;*/
}
