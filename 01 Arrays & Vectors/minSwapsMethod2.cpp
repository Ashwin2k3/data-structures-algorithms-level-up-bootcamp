#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int minSwaps(vector<int>a ,int N){
    vector<pair<int,int>> v(N);
    for(int i=0;i<N;i++){
        v[i]={a[i],i};

    }
    sort(v.begin(),v.end());

    int swaps=0;
    for(int i=0;i<N;i++){
        if (v[i].second==i) {
            continue;
        }
        else{
            ++swaps;
            swap(v[i],v[v[i].second]);
            i--;
        }
    }
    return swaps;
}

int main(){
    vector<int> a{5,4,3,2,1};
    int N = a.size();
    cout<<minSwaps(a,N);

    return 0;
}

