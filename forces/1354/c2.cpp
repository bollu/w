#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;
using f = double;
#define SINCOS sincos
const f INFTY = 42 * 10000;

inline void polygon(int m, f theta, f &minx, f &miny, f &maxx, f &maxy) {
    minx = miny = INFTY; maxx = maxy = -INFTY;
    
    // (m-2) . 180 = internal_angle * m
    // internal_angle = (m-2)/(m*180)
    //
    // 2 * sin(half_internal_angle/2) = diagonal length

    const f internal_angle = (((f)m-2.0) * M_PI) / (f)m;
    const f half_internal_angle = 0.5 * internal_angle;
    // const f diagonal_len = 2.0 * sin(half_internal_angle);
    // const f half_diagonal_len = diagonal_len / 2.0;
    const f half_diagonal_len = 0.5 * tan(half_internal_angle); 

    // cout << "internal angle: " << internal_angle << "\n";
    // cout << "diagonal len: " << diagonal_len << "\n";
    for(int i = 0; i < 2*m; ++i) {
        f px, py;
        // sincos(theta + i*2*M_PI/m, &px, &py);
        SINCOS(theta + i*2*M_PI/(2*m), &px, &py);
        px *= half_diagonal_len; py *= half_diagonal_len;
        // const f px = half_diagonal_len * cos(theta + i * 2 * M_PI / m);
        // const f py = half_diagonal_len * sin(theta + i * 2 * M_PI / m);
        // cout << "i = " << i << " | " << px << " " << py << "\n";

        if (px < minx) minx = px;
        if (px > maxx) maxx = px;
        if (py < miny) miny = py;
        if (py > maxy) maxy = py;
    }
};

f sidelen(int m, f theta) {
    f minx, miny, maxx, maxy;
    polygon(m, theta, minx, miny, maxx, maxy);
    return max(maxx - minx, maxy - miny);
}

/*
f optim(int m) {
    f cur_angle = 0;
    f best_val = sidelen(m, 0);
    f temp = 5;
    unsigned short xsubi[3];

    for(int i = 0; i < 1e4; ++i) {
        temp = max<f>(1, temp * 0.9);
        f next_angle = cur_angle + (0.5 - erand48(xsubi));
        f next_val = sidelen(m, next_angle);

        if (next_val < best_val) { next_angle = cur_angle; best_val = next_val; }
        else {
            f r = erand48(xsubi);
            if (log(r) < log(next_val) - log(best_val)) {
                cur_angle = next_angle;
            }
        }

    }
    return best_val;
}
*/

f analytic(int m) {
    f best = -INFTY;
    for(int i = 0; i < m; ++i) {
        best = max(best, sidelen(m, (M_PI*(double)i)/(double)m));
    }
    return best;
}

int main() {
    srand(0);
    int t; cin >> t;
    while(t--) {
        // int n; cin >> n; const int m = 2*m;
        // cout << 2 * asin( (m – 2) * 180/2 *m) << "\n";
        // int n; cin >> n; const double m = 2*n;
        // cout << 2 * 1 * sin((m-2) *180.0 / (2 * m)) << "\n";
        
        // double minx, miny, maxx, maxy;
        // polygon(4, M_PI/4, minx, miny, maxx, maxy);
        // cout << minx << " " << maxx << " " << miny << " " << maxy << "\n";
        // cout << maxx - minx << " " << maxy - miny << "\n";
        int n; scanf("%d", &n); const int m = 2*n;
        printf("%f\n", analytic(m));
        // printf("%d:  %f | %f\n", m,  optim(m), analytic(m));
        // printf("%d:  %f | %f\n", m,  optim(m), analytic(m));

    }
    // cout << "optim: " << optim(4) << "\n";
    return 0;
}

