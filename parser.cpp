#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <stdexcept>
#include <stdio.h>

using namespace std;

const int N = 26;

void Error(int code)
{
    switch(code){
     case 1: throw std::invalid_argument("division by zero");
     case 2: throw std::invalid_argument(" ')' absent, sorry i can't continue process... bye");
     case 3: throw std::invalid_argument("this not a number, try again");
     case 4: throw std::invalid_argument(" '(' absent, sorry i can't continue process... bye");
     case 5: throw std::invalid_argument("expression is not available");
     case 6: throw std::invalid_argument(" '.' reiteration symbol - don't do that again please");
    }
}

void print(stack<string>& st_)
{
    int size = st_.size();
    for(int i = 0; i < size; i++, st_.pop()){
        cout<<st_.top()<<endl;
    }
}

double atos(string s)
{
    int len = s.size();
    int i = 0;
    double ans = 0;
    string sdiv;
    string smod;
    while(s[i] != '.' && i < len){
        sdiv += s[i];
        i++;
    }
    i++;
    while(i < len){
        smod += s[i];
        i++;
    }
    return ans = atoi(sdiv.c_str())+atoi(smod.c_str())/pow(10,smod.size());
}

//global variables
string tmp = " not found";
stack<string> stack_;
double var[N];

template<typename t>
void exp0_(t&);
template<typename t>
void exp1_(t&);
template<typename t>
void exp2_(t&);
template<typename t>
void exp3_(t&);
template<typename t>
void exp4_(t&);
template<typename t>
void exp5_(t&);
template<typename t>
void exp6_(t&);
template<typename t>
void exp7_(t&);

template<typename t>
t prvar(char s)
{
    if(isalpha(s)){
        return var[toupper(s)-'A'];
    }
    return 0.0;
}

//initial stack
void initial_stack(stack<string>&st_,string& s)
{
    s.erase(remove(s.begin(),s.end(),' '),s.end());
    s.erase(remove(s.begin(),s.end(),'\n'),s.end());
    s.erase(remove(s.begin(),s.end(),';'),s.end());
    reverse(s.begin(),s.end());
    auto end = s.end();
    for(auto iter = s.begin(); iter != end; ++iter){
        if(isdigit(*iter)){
                string num;
            while(isdigit(*iter)){
                num += *iter;
                ++iter;
                if(*iter == '.'){
                    num += *iter;
                    ++iter;
                    if(*iter == '.') Error(6);
                }
            }
            reverse(num.begin(),num.end());
            st_.push(num);
            if(iter == end) return;
        }

        if(isalpha(*iter)){
            string alpha;
            alpha = *iter;
            st_.push(alpha);
        }

        if(strchr("+-/*^=",*iter)){
            string bin;
            bin = *iter;
            st_.push(bin);
        }

        if(*iter == '(' || *iter == ')'){
           string bin;
           bin = *iter;
           st_.push(bin);
        }
    }
}

//call every time and pop top element
void getToken()
{
    if(stack_.empty()){
        tmp[0] = '\0';
        return;
    }
    tmp = stack_.top();
    stack_.pop();
}

//begin recursing process
template<typename t>
void exp0_(t& ans)
{
  getToken(); //get first element
  if(!tmp[0]){Error(5);return;} //if empty then end
  exp1_(ans);
  if(tmp[0] == ')')
    Error(4);
  cout<<"answer:"<<endl; //this ending if all ok
}

template<typename t>
void exp1_(t& ans)
{
    int slot;
    slot = toupper(tmp[0])-'A';
    getToken(); // " = "
    if(tmp[0] == '='){
     getToken(); // number
     exp2_(ans);
     var[slot] = ans;
    }
  if(isalpha(tmp[0]))
     exp1_(ans);
  else return;
}

template<typename t>
void exp2_(t& ans)
{
    char op = '\0';
    t left = 0;
    exp3_(ans);
    while((op = tmp[0]) == '+' ||op == '-'){
        getToken();
        exp3_(left);
        switch(op)
         {
            case '+': ans += left; break;
            case '-': ans -= left; break;
         }
    }
}

template<typename t>
void exp3_(t &ans)
{
    char op = '\0';
    t left = 0;
    exp4_(ans);
    while((op = tmp[0]) == '*' ||op == '/'){
        getToken();
        exp4_(left);
        switch(op)
         {
            case '*': ans *= left; break;
            case '/': if(!left) Error(1); ans /= left; break;
         }
    }
}

template<typename t>
void exp4_(t& ans)
{
    char op = '\0';
    t left = 0;
    exp5_(ans);
    while((op = tmp[0]) == '^'){
        getToken();
        exp5_(left);
        if(left == 0){
            ans = 1;
        }
        ans = pow(ans,left);
        break;
    }
}

//unary sign
template<typename t>
void exp5_(t& ans)
{
    char op = '\0';

    if((op = tmp[0])== '-'||op == '+'){
       getToken();
       exp6_(ans);
       if(op == '-')
         ans = -ans;
       return;
    }
    exp6_(ans);
}

template<typename t> //if lbrace or rbrace
void exp6_(t& ans)
{
    if(tmp[0] == '(')
        { //add empty number
            getToken();
            exp2_(ans);
            if(tmp[0] != ')')
                Error(2);
            getToken();
            return;
        }
    exp7_(ans);
}

template<typename t>
void exp7_(t& ans) //if number
{
    if(isalpha(tmp[0])){
        ans = var[toupper(tmp[0])-'A'];
        getToken();
        return;
    }
    if(isdigit(tmp[0]))
        {
            ans = atos(tmp);
            getToken();
            return;
        }
    else{
        Error(3); //if not number
    }
}

int main()
{

try
{
for(int i = 0; i < N; i++)
    var[i] = 0.0;
 string s ="a = 3; b = 3; c = a^2 + b^3;";
 double ans = 0;
 char* ptr = new char[10];
 ptr = "hello";
 initial_stack(stack_,s);
 //print(stack_);
 exp0_(ans);
 //cout<<prvar<double>('c')<<endl;
}

catch(std::invalid_argument& oop){
cout<<"exception:"<<oop.what()<<endl;
}

    return 0;
}
