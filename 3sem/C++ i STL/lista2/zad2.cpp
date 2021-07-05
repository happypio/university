#include <iostream>
#include<memory>
#include<fstream>

using namespace std;

class LineWriter
{
	public:
		ofstream* o;
		LineWriter()
		{
			o = new ofstream("tekst.txt",ofstream::app);
		}
		virtual ~LineWriter()
		{
			cout<<"usuwamy obiekt i zamykamy strumien"<<endl;
			o->close();
			delete o;
		}
		void write(string message)
		{
			*o<<message<<endl;
		}

};

int main()
{
	shared_ptr<LineWriter> l1(new LineWriter());
	//move(l1);
	shared_ptr<LineWriter> l2 = l1;
	shared_ptr<LineWriter> l3 = l1;
	shared_ptr<LineWriter> l4 = l1;
	shared_ptr<LineWriter> l5 = l1;

	l1->write("wskaznik numer 1");
	l3->write("wskaznik numer 3");
	l2->write("wskaznik numer 2");
	l4->write("wskaznik numer 4");
	l5->write("wskaznik numer 5");
	return 0;
}