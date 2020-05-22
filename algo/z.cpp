const int N = 1000;
int z[N];
char s[N] = "hello, world";
int n;

// s[0..z[i]] = s[i..z[i]] | z[i] largest
void mkz() {
}

int main() {
    n = strlen(s);
    mkz();
    for(int i = 1; i <= n; ++i) { printf("%3d", i); }
    for(int i = 0; i < n; ++i) {
        printf("%3c", s[i]);
    }
    for(int i = 0; i < n; ++i) { printf("%3d", z[i]); }
    printf("\n");
}

