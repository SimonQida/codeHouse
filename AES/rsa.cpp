#include<iostream>
#include<vector>
using namespace std;

vector<int> Prime;

/*
int getPrime()
{
    return 61;
}

int getPrime_()
{
    return 53;
}
*/

int get_e(int fai_n)        //get double-prime e
{

    int e;
    while(1){
        e = Prime.at(random()%Prime.size());
        if(fai_n/e)
            break;
    }

    return e;
}

int get_d(int e,int fai_n)      //get d by ed=1(mod fai_n)
{
    int d  ;
    double d_d;
    for(int k=0;d_d !=(int)d_d;++k){        //get the integer num of all result
         d_d=(k*fai_n+1)/double(e);
    }
    d = d_d;
    return d;
}

pair<pair<int,int>,pair<int,int>> all(vector<int> Prime)
{

    int p = Prime.at(0);
    int q = Prime.at(1);
    int n = p*q;
    int fai_n = (p-1)*(q-1);

    int e = get_e(fai_n);
    int d = get_d(e,fai_n);
    
    return make_pair(make_pair(n,e),make_pair(n,d));
    
}

int main()
{
    srand(time(0));
    const int edge = 1000;
    bool dex[edge] = {1,1};

    for(int i=2;i<edge;++i){
        for(int j=2;i*j<edge;++j){
            dex[i*j] = 1;
        }
    }
    int count =0;
    for(int i=0;i<edge;++i){
        if(!dex[i])
            Prime.push_back(i);
    }
    vector<int> v;
    while(count<2){         //get two Prime
        int x= 0;
        int dueprime = Prime.at(random()%Prime.size());
        if(x == dueprime)
            continue;

        ++count;
        v.push_back(dueprime);
        x = dueprime;
    }

    auto x =all(v);
    cout<<"public key : "<<x.first.first<<" "<<x.first.second<<endl<<"private key : "<<x.second.first<<" "<<x.second.second;
}
