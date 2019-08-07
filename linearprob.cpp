#include<iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#define ssi 100000
using namespace std;
int lpa[ssi]={-1};
void insert_lpa(int val)
{
    int hv = val % 10;
    int i=0;
    while(lpa[(hv+i)%ssi]!=-0&&i<ssi)
    {
        i++;

    }
    //cout<<hv+i;
    lpa[(hv+i)%ssi] = val;
    //cout<<"Placed"<<"\n";
}
int find_val(int val)
{
    int hv = val % 10;
    int i = 0,cnt=0;
    while(cnt<=ssi&&lpa[(hv+i)%ssi]!=val)
        {
            //cout<<hv+i<<"->"<<lpa[hv+i]<<"\n";
            i++,cnt++;
        }
    if(lpa[(hv+i)%ssi]==val)
        return 1;
    else
        return 0;
}
int main()
{
    int j=1;

    for(int i=0;i<ssi;i++,j+=10)
    {
        insert_lpa(j);
    }
    int val = 491,result;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0;i<ssi;i++)
        result = find_val(val);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds0 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    cout<<"TIME 0 : "<<microseconds0;
    cout<<"-->"<<result;

    return 0;
}
