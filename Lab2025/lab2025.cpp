#include <iostream>

using namespace std;

uint32_t fight_count(uint32_t n, uint32_t k);

int main()
{
    size_t T;
    cin >> T;
    
    for(size_t i=0; i < T; i++)
    {
        uint32_t n, k;
        cin >> n >> k;
        cout << fight_count(n, k) << "\n";
    }

    return 0;
}

uint32_t fight_count(uint32_t n, uint32_t k)
{
    uint32_t div = n/k;

    return (n*n + div*div*k - 2*div*n - n + div*k)/2;
}