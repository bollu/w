#include <vector>
#include <stdio.h>
#include <math.h>
using namespace std;

int results[1000000000];

void sito_delta( int delta, std::vector<int> &res)
{

    for(int i = 0; i <= delta; ++i)
        results[i] = 1;

    int pierw = sqrt(delta);
    for (int j = 2; j <= pierw; ++j)
    {
        if(results[j])
        {
            for (int k = 2*j; k <= delta; k+=j)
            {
                results[k]=0;
            }
        }
    }

    for (int m = 2; m <= delta; ++m)
        if (results[m])
        {
            res.push_back(m);
            printf("%d\n", m);
        }
};
void sito_segment(int n,std::vector<int> &fiPri)
{
    int delta = sqrt(n);

    if (delta>10)
    {
        sito_segment(delta,fiPri);
        // COmpute using fiPri as primes
        // n=n,prime = fiPri;
        std::vector<int> prime=fiPri;
        int offset = delta;
        int low = offset;
        int high = offset * 2;
        while (low < n)
        {
            if (high >=n ) high = n;
            int mark[offset+1];
            for (int s=0;s<=offset;++s)
                mark[s]=1;

            for(int j = 0; j< prime.size(); ++j)
            {
                int lowMinimum = (low/prime[j]) * prime[j];
                if(lowMinimum < low)
                    lowMinimum += prime[j];

                for(int k = lowMinimum; k<=high;k+=prime[j])
                    mark[k-low]=0;
            }

            for(int i = low; i <= high; i++)
                if(mark[i-low])
                {
                    fiPri.push_back(i);
                    printf("%d\n", i);;
                }
            low=low+offset;
            high=high+offset;
        }
    }
    else
    {

        std::vector<int> prime;
        sito_delta(delta, prime);
        //
        fiPri = prime;
        //
        int offset = delta;
        int low = offset;
        int high = offset * 2;
        // Process segments one by one 
        while (low < n)
        {
            if (high >= n) high = n;
            int  mark[offset+1];
            for (int s = 0; s <= offset; ++s)
                mark[s] = 1;

            for (int j = 0; j < prime.size(); ++j)
            {
                // find the minimum number in [low..high] that is
                // multiple of prime[i] (divisible by prime[j])
                int lowMinimum = (low/prime[j]) * prime[j];
                if(lowMinimum < low)
                    lowMinimum += prime[j];

                //Mark multiples of prime[i] in [low..high]
                for (int k = lowMinimum; k <= high; k+=prime[j])
                    mark[k-low] = 0;
            }

            for (int i = low; i <= high; i++)
                if(mark[i-low])
                {
                    fiPri.push_back(i);
                    printf("%d\n", i);
                }
            low = low + offset;
            high = high + offset;
        }
    }
};

int main()
{
    std::vector<int> fiPri;
    sito_segment(1000000000,fiPri);
}
