#include <functional>
#include <vector>
#include <iostream>
#include <queue>
#include <assert.h>
using namespace std;

template<typename T, int N> struct cqueue {
    T arr[N];
    int head = 0; int len = 0;
    int size() const { return len; }
    void push(T val) { arr[(head + len++)%N] = val; }
    void pop() { head++; len--; }
    T front() { return arr[head%N]; }
};

void test_queue() {
    cqueue<int, 100> cq;
    queue<int> q;

    for(int i = 0; i < 10; ++i) {
        int n = rand() % 100;
        for(int j = 0; j < n; ++j) {
            int r = rand() % 100;
            q.push(r);
            cq.push(r);
        }

        while(1) {
            assert(q.size() == cq.size());
            if (q.size() == 0) { break; }
            assert(q.front() == cq.front());
            q.pop(); (void)cq.pop();
            
        }
    }
}

template<typename T, int N, int INFTY=1000000000> struct cpriorityq {
    int a[N]; int len = 0; // heap starts at index 1.

    void swapix(int i, int j) { int t = a[i]; a[i] = a[j]; a[j] = t; }
    void print(int ix = 0) const {
        cerr << "(len=" << len << ")[";
        for(int i = 1; i < 1+len; ++i) {
            if (i == ix) cerr << ">" << i << ":" << a[i]  << "< ";
            else cerr << i << ":" << a[i] << " ";
        }
        cerr << "]\n";
    }
    
    void bot2top(int i) {
        while(i > 1 && a[i] < a[i/2]) { print(i); swapix(i, i/2); i = i/2; }
    }

    void top2bot(int i) {
        int small = i;
        if (i*2 < len && a[i*2] < a[small]) { small = i*2; }
        if (i*2+1 < len && a[i*2+1] < a[small]) { small = i*2+1; }
        if (small == i) { return; }
        swapix(i, small); top2bot(small);
    }

    void push(T val) { print(1+len); int i = 1+len; a[i] = val; bot2top(i); len++; }
    void pop() { print(1); swapix(1, 1+len-1); top2bot(1); len--; }

    int size() const { return len; }
    T top() const { return a[1]; }
    // aliases for top()
    T head() { return top(); } T front() { return top(); }
};

void test_priority_queue() {
    priority_queue<int, vector<int>, greater<int>> q;
    cpriorityq<int, 100> cq;

    int counter = 0;

    for(int i = 0; i < 10; ++i) {
        int n =  rand() % 100;

        for(int j = 0; j < n; ++j) {
            int r = rand() % 100;
            cerr << counter++ << ".push(" << r << ")\n";
            q.push(r);
            cq.push(r);
        }

        while(1) {
            assert(q.size() == cq.size());
            if (q.size() == 0) { break; }
            cerr << counter++ << ". q.top():" << q.top() << " | cq.top(): " << cq.top() << "\n";
            assert(q.top() == cq.top());
            cerr << counter++ << ". pop()" << "\n";
            q.pop(); (void)cq.pop();
            
        }
    }
}

int main() {
    cout << "testing queue...\n";
    test_queue();
    cout << "queue succeeded\n";

    cout << "testing proprity queue (heap)...\n";
    test_priority_queue();
    cout << "priority queue succeeded\n";

    return 0;
}
