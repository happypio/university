#include<iostream>
#include <type_traits>

using namespace std;

class Myclass{
	public:
		int n = 0;
		Myclass(int n){
			this->n = n;
		}
};

template <typename T1, typename T2,
	typename = enable_if_t< is_convertible< remove_pointer_t<T1> ,T2>::value >
	>
void move_impl(const T1 val1, T2 &val2, true_type) {
	cout<<"An argument was a pointer!"<<endl;
	val2 = *val1;
}


template <typename T1, typename T2,
	typename = enable_if_t< is_convertible<T1,T2>::value >
	>
void move_impl (const T1 val1, T2 &val2, false_type,){
	cout<<"An argument was not a pointer!"<<endl;
	val2 = val1;
}


template<typename T1, typename T2,
	typename = enable_if_t< is_convertible< remove_pointer_t<T1> ,T2>::value >
	>
void move(const T1 val1, T2 &val2) {
	//if (is_convertible<T1,T2>::value or is_convertible<decltype(*val1) , T2>::value)
	move_impl(val1, val2, is_pointer<T1>());
}

int main()
{
	Myclass c1 (1);
	Myclass c2 (2);
	cout<<"Before move(c1,c2)"<<endl;
	cout<< "c1: "<<c1.n << " c2: " << c2.n << endl;
	move(c1,c2);
	cout<<"After move(c1,c2)"<<endl;
	cout<< "c1: "<<c1.n << " c2: " << c2.n << endl;
	c1.n = 1;
	c2.n = 2;
	cout<<endl<<endl<<"Before move(&c1,c2)"<<endl;
	cout<< "c1: "<<c1.n << " c2: " << c2.n << endl;
	Myclass * c3 = new Myclass(3);
	//move(c3,c2);
	move(&c1,c2);
	cout<<"After move(&c1,c2)"<<endl;
	cout<< "c1: "<<c1.n << " c2: " << c2.n << endl;

	return 0;
}