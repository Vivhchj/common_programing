/*
在证明数素无穷性时，使用了一个表达式 N＝2＊3＊5＊7＊11＊……＊P + 1，其中 P 为一个素数，N 是 2 到 P 中所有素数的乘积加 1，
若 P 为最大的素数，可以反证出 N 也是素数，从而证明素数是无穷多的。
但有人因此认为，所有的 N 都是素数。如N0 = 3 为 素数，N1 = 7 为素数，N2 = 31 为素数。
请判断第 i 个 N 是否为素数。
*/

#include<iostream>
#include<vector>
#include<cmath>
 
using namespace std;
 
//判断num是否为素数，只需判断[2, sqrt(num)]内的整数能否被num整除
bool isPrime(long long int num){
    if(num<2){
        return false;
    }
    //注意i<=sqrt(num)
    for(int i = 2; i<=sqrt(num); ++i){
        if(num%i==0){
            return false;
        }
    }
    return true;
}
 
int main(){
    int n;
    cin >> n;
    vector<int> prime{2};
    int temp;
    //向prime数组中增加n个素数
    while(n>0){
        temp = prime.back()+1;
        while(!isPrime(temp)){
            ++temp;
        }
        prime.push_back(temp);
        --n;
    }
    long long int res = 1;
    for(int p : prime){
        res *= p;
    }
    ++res;
    if(isPrime(res)){
        cout << res << " is a prime" << endl;
    }
    else{
        cout << res << " is not a prime" << endl;
    }
    return 0;
}
