#include <iostream>
#include <stack>
#include <set>
#include <queue>
using namespace std;

bool in (char e, set <char> s) {
    if (s.find(e) != s.end())
        return true;
    return false;    
}

void print(queue <char> q) {
    while( !q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << "\n";
}

queue <char> shunting_yard (string infix) {
    char f[] = {'+', '-', '/', '*','^','%'}; // only ^ is rigth associative 
    char b[] = {'(', ')'};

    set <char> fs(f, f + 6) ;
    set <char> priority(f + 2, f + 6 );
    set <char> bs(b,b + 2);

    stack <char> functions;
    queue <char> rpn;
    for(int i = 0; i < infix.length(); i++) {
        if ( in(infix[i], fs) ) {
            if (!functions.empty()) {
                auto o{functions.top()};
                while (in(o, fs) && infix[i] != '^' &&
                (!in(infix[i], priority) || in(o, priority) ) ) {
                    rpn.push(o);
                    functions.pop();
                    if (functions.empty())
                        break;
                    o = functions.top();
                }
            }
            functions.push(infix[i]);
        }
        else {
            if ( in(infix[i], bs) ) {
                if (infix[i] == '(')
                    functions.push(infix[i]);
                else {
                    if (!functions.empty()){
                        auto o{functions.top()};
                        while (o != '(') {
                            rpn.push(o);
                            functions.pop();
                            if (functions.empty())
                                break;
                            o = functions.top();
                        }
                        functions.pop();
                    }
                }
            }
            else {
                rpn.push(infix[i]);
            }
        }
    }


    while(!functions.empty()) {
        rpn.push(functions.top());
        functions.pop();
    }
    return rpn;

}

int main() {
    queue <char> t1 = shunting_yard("2+3-(4^3^2*6)");
    queue <char> t2 = shunting_yard("3+4*2/(1-5)^2");
    queue <char> t3 = shunting_yard("(2+3%2)*(2^5)*80-2/3");
    queue <char> t4 = shunting_yard("(3/2^3%5*2)");
    cout << "testing : 2 + 3 - (4^5 * 6) \n";
    print(t1);
    cout << "testing : 3 + 4*2 / (1-5)^2 \n";
    print(t2);
    cout << "testing : (2 + 3%2) * (2^5) * 80 - 2/3 \n";
    print(t3);
    cout << "testing : (3/2^3 %5 *2) \n";
    print(t4);
    return 0;
}