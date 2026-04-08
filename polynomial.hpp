#pragma once

#include<iostream>  
#include<cmath>  
using namespace std;  
  
class Polynomial {  
protected:  
      
  
    class Term {  
    public:  
  
        int exponent;  
        int coefficient;  
        Term* next;  
  
        Term(int exp, int coeff, Term* n) {  
            exponent = exp;  
            coefficient = coeff;  
            next = n;  
  
        }  
  
        friend class Polynomial;  
    };  
  
    Term* head;  
    Term* end;  
  
public:  
  
    Polynomial() {  
        //Term* p = nullptr;  
        head = nullptr;  
        end = nullptr;  
    }  
  
    Polynomial(const Polynomial& p) {  
          
        Term* n = p.head;  
  
        while (n != nullptr) {  
            addTerm(n->exponent, n->coefficient);  
            n = n->next;  
        }  
    }  
  
    ~Polynomial() {  
  
          
        while(head != nullptr) {  
            Term* n = head;  
            head = head->next;  
            n->next = nullptr;  
            delete n;  
        }  
  
        
    }  
  
    Polynomial& operator =(const Polynomial& p) { 
          
        Term* n = head;  
  
        while (head != nullptr) {  
            Term* n = head;  
            head = head->next;  
            n->next = nullptr;  
            delete n;  
        }  
        n = p.head;  
  
        while (n != nullptr) {  
            addTerm(n->exponent, n->coefficient);  
                n = n->next;  
        }  
        return *this;  
    }  
  
  
  
    void addTerm(int expon, int coeff) {  
          
        if (head == nullptr) {  
              
            head = new Term (expon, coeff, nullptr);  
            end = head;  
        }  
        else {  
              
            Term* p = head;  
  
            while (p != end) {  
                if (p->exponent == expon) {  
                    p->coefficient += coeff;   
                    p =nullptr;  
                    return;  
                }  
                p=p->next;   
            }  
  
            if (p->exponent == expon) {  
                p->coefficient += coeff;  
                p = nullptr;  
                return;  
            }  
  
              
                end = new Term (expon, coeff, nullptr);  
                p->next = end;  
        }  
    }  
  
    double evaluate(double x){  
          
        double sum= 0;  
        Term* n = head;  
  
        while (n != nullptr) {  
            sum += (n->coefficient) * pow(x, n->exponent);  
            n = n->next;  
        }  
  
        return sum;  
    }  
  
    friend Polynomial operator+ (const Polynomial& p, const Polynomial& q) {  
          
        Polynomial n;  
        Term* a = p.head;  
  
        while (a != nullptr) {  
            n.addTerm(a->exponent, a->coefficient);  
            a = a->next;  
        }  
  
        a = q.head;  
  
        while (a != nullptr) {  
            n.addTerm(a->exponent, a->coefficient);  
            a = a->next;  
        }  
  
        return n;  
  
    }  
  
    friend Polynomial operator *(const Polynomial& p, const Polynomial& q) {  
  
        Polynomial n;  
  
        Term* a = p.head;  
        //Term* b = q.head;  
  
        while (a != nullptr) {  
              
            Term* b = q.head;  
  
            while (b != nullptr) {  
                  
                n.addTerm(a->exponent + b->exponent, a->coefficient * b->coefficient);  
                b = b->next;  
            }  
            a = a->next;  
        }  
  
        return n;  
  
    }  
  
    friend ostream& operator << (ostream& out, const Polynomial& p) {  
      
        int maxexp=0;  
        Term* n = p.head;  
        bool saveme = true;  
        bool foundsmt=false;  
        while(n!=nullptr){  
            if (n->exponent > maxexp && n->coefficient != 0) maxexp = n->exponent; foundsmt = true;  
            n = n->next;  
        }  
        if (!foundsmt) { cout << 0; return out; }  
  
        n = p.head;  
          
        while (n != nullptr && n->exponent != maxexp) { n = n->next; }  
        if (maxexp == 0 && n != nullptr)if (n->coefficient >= 0) cout << n->coefficient; else cout << "- " << abs(n->coefficient);  
        else if (maxexp == 1 && n != nullptr) {  
            if (n->coefficient > 1) { cout << n->coefficient << "x"; }  
            if (n->coefficient == 1) { cout << "x"; }  
            if (n->coefficient < -1) { cout << "- " << abs(n->coefficient) << "x"; }  
            if (n->coefficient == -1) { cout << "- " << "x"; }  
            saveme = false;  
        }  
        else if (n != nullptr) {  
            if (n->coefficient > 1) { cout << n->coefficient << "x^" << n->exponent; }  
            if (n->coefficient == 1) { cout << "x^" << n->exponent; }  
            if (n->coefficient < -1) { cout << "- " << abs(n->coefficient) << "x^" << n->exponent; }  
            if (n->coefficient == -1) { cout << "- " << "x^" << n->exponent; }  
            /*else if (n == nullptr)cout << 0;*/  
        }  
        else if (n == nullptr) {  
            cout << 0; return out;  
        }  
  
  
  
  
            if (maxexp >= 1) {  
                for (int i = maxexp - 1; i >= 2; i--) {   // edo mporei nna thelei i=maxexp-1  
                    n = p.head;  
                    while (n != nullptr && n->exponent != i) { n = n->next; }  
                    if (n != nullptr && n->exponent == i) {  
                        if (n->coefficient > 1) { cout << " + " << n->coefficient << "x^" << n->exponent; }  
                        if (n->coefficient == 1) { cout << " + " << "x^" << n->exponent; }  
                        if (n->coefficient < -1) { cout << " - " << abs(n->coefficient) << "x^" << n->exponent; }  
                        if (n->coefficient == -1) { cout << " - " << "x^" << n->exponent; }  
                    }  
                }  
  
                n = p.head;  
  
                while (n != nullptr && n->exponent != 1 ) { n = n->next; }  
                if (n != nullptr && n->exponent == 1 && saveme) {  
                    if (n->coefficient > 1) { cout << " + " << n->coefficient << "x"; }  
                    if (n->coefficient == 1) { cout << " + " << "x"; }  
                    if (n->coefficient < -1) { cout << " - " << abs(n->coefficient) << "x"; }  
                    if (n->coefficient == -1) { cout << " - " << "x"; }  
                }  
  
                n = p.head;  
  
                while (n != nullptr && n->exponent != 0 ) { n = n->next; }  
                if (n != nullptr && n->exponent == 0) {  
                    if (n->coefficient > 1) { cout << " + " << n->coefficient; }  
                    if (n->coefficient == 1) { cout << " + 1"; }  
                    if (n->coefficient < -1) { cout << " - " << abs(n->coefficient); }  
                    if (n->coefficient == -1) { cout << " - 1"; }  
                }  
            }  
          
        return out;  
    }  
  
  
}; 