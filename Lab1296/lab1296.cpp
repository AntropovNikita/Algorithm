#include <iostream>
#include <stdint.h>

using namespace std;


int main()
{
    uint16_t n;
    int32_t p;
    cin >> n;

    int64_t max_grav = 0; // маскимальный гравитационный потенциал
    int64_t cur_grav = 0; // текущий гравитационный потенциал
    while(n-- != 0)
    {
        cin >> p;
        cur_grav = max((int64_t)0, cur_grav + p);
        max_grav = max(max_grav, cur_grav);
    }

    cout << max_grav;

    return 0;
}