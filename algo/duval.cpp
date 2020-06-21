#include <iostream>
#include <vector>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

void printijk(const string &s, const int i, const int j, const int k) {
    printf("%s$\n", s.c_str());
    for(int ix = 0; ix <= s.size(); ++ix) {
        if (ix == i) printf("i");
        else if (ix == j || ix == k) printf("|");
        else printf(" ");
    }
    printf("\n");
    for(int ix = 0; ix <= s.size(); ++ix) {
        if (ix == j) printf("j");
        else if (ix == k) printf("|");
        else printf(" ");
    }
    printf("\n");
    for(int ix = 0; ix <= s.size(); ++ix) {
        if (ix == k) printf("k"); else printf(" ");
    }
    printf("\n");
}

vector<string> duval(string const& s) {
    int n = s.size();
    int i = 0;
    vector<string> factorization;
    while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k) {
            factorization.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}

// rator, rand
int ceildiv(int dand, int visor) {
    return (dand + (visor - 1))/visor;
}

void print2(const char *s, int j, int k) {
    printf("\n%s$\n", s);
    for(int ix = 0; ix <= strlen(s); ++ix) {
        if (ix == j) printf("j");
        else if (ix == k) printf("|");
        else printf(" ");
    }
    printf("\n");
    for(int ix = 0; ix <= strlen(s); ++ix) { if (ix == k) printf("k"); else printf(" "); }

}

void duval(const char *s, vector<char *> &ss) {
    const int n = strlen(s);
    if (n == 0) return;

    int s2len = 0, s3len = 1;
    // 1. this needs to be <=, because otherwise when we rotate, we will
    // have s3 eclipse s2.
    //
    // 2. 
    while(s2len < n) {
        if (s[s2len] > s[s3len]) printf("\nCRITICAL");
        print2(s, s2len, s3len);

        if(s[s2len] > s[s3len]) { break; }
        s2len = s[s2len] == s[s3len] ? s2len + 1 : 0;
        s3len++;
    }

    const int p = s3len - s2len;
    int i = 0;
    for(; i*p <= s2len; ++i) {
        char *dest = (char *)calloc(sizeof(char), p+1);
        strncpy(dest, s, p);
        ss.push_back(dest);
    }

    duval(s + i*p, ss); 
    //duval(s + ceildiv(s2len, p), ss); 
}

int main() {
    // 679
    // 8
    // 45
    // 123
    const char *s = "679845123";
    vector<char *> ss; duval(s, ss);

    for(auto t : ss) {
        cout << t << "; ";
    }

    cout << "\n";
    vector<string> ts = duval(string(s));
    for(auto t : ts) {
        cout << t << "; ";
    }

    return 0;
}
