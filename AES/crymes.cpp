#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include "../../../Downloads/cryptopp-CRYPTOPP_7_0_0/integer.h"
#include "../../../Downloads/cryptopp-CRYPTOPP_7_0_0/aes.h"

using namespace std;
using namespace CryptoPP;

class byte4{
    public:
        char w[4];
        byte4(char data[4]){
            memcpy(w,data,4);
        }
};

pair<char,char> getindexs(char c)
{
    char x = (c&0xf0)>>4;
    char y = c&0x0f;
    return pair<char,char>(x,y);
}

AESEncryption enc;
AESDecryption aesdec;
string xx1,xx2;

string file_str(string filename)
{
    string plaintextstr;
    ifstream fin;
    fin.open(filename);

    if(!fin.is_open()) {
        cout<<endl<<"file open error";
        abort();
    }

    while(fin){
        string t = "";
        getline(fin,t);
        plaintextstr += t;
        plaintextstr += '\n';
    }
    fin.close();
    return plaintextstr;
}

string file_str_ciper(string filename)
{
    string plaintextstr;
    ifstream fin;
    fin.open(filename);

    if(!fin.is_open()) {
        cout<<endl<<"file open error";
        abort();
    }

    char buf ;
    while(!fin.eof()){
        fin>>buf;
        plaintextstr.push_back(buf) ;
    }
    fin.close();
    return plaintextstr;
}

vector<string> getpiece(string p)
{
    const int len = 16;
    int size = p.size()/len;
    int end = p.size()%len;
    vector<string> vs;
    for(int i=0;i<size;++i){        //get all the full 16 blocks
        vs.push_back(string(&p[len*i],&p[len*(i+1)]));
    }

    if(end){                         //check if it has tail block not full
        string t (&p[len*size],&p[p.size()-1]);           //**unsolved** do not fill the last byte with '\0'
        for(int i =0;i<len-end+1;++i)
            t.push_back('\0');
        vs.push_back(t);
    }
    return vs;
}

string cryptopp (vector<string> piece){
    vector<string> cipervs;
    string ret;
    unsigned char cipertext[16];
    for(string s:piece){
        const char *plaintext_  =s.data();
        unsigned char *plaintext = (unsigned char*)plaintext_;
        enc.ProcessBlock(plaintext,cipertext);
        string ss = string(cipertext,cipertext+16);
        cipervs.push_back(ss);
        cout<<ss;
        ret +=ss;
    }
    return ret; 
}

void output_file(string filename,string content)
{
    ofstream fout;
    fout.open(filename);
    if(!fout.is_open()){
        cout<<"file "<<filename<<"open error"<<endl;
        abort();
    }
    fout<<content;
    fout.close();
}

int main()
{
    string keystr,plaintextstr,cipertextstr;
    plaintextstr = file_str("t");      //get the content of file

    vector<string> piece = getpiece(plaintextstr);

    plaintextstr = "qwerwer";

    cin>>keystr;
    const char *key_  =keystr.data();
    unsigned char *key = (unsigned char*)key_;
    enc.SetKey(key,16);


    string cipervs = cryptopp(piece);
    cout<<cipervs.size();

    output_file("t.ciper",cipervs);

    string str = file_str("t.ciper");

    vector<string> piece_ciper = getpiece(str);
    //cout<<piece_ciper.size();

    //decryptopp
    unsigned char result[16];
    vector<string> plaintextagainvs;
    aesdec.SetKey(key,16);

    string copy;
    for(auto x=piece_ciper.begin();x!=piece_ciper.end()-1;++x){
        const char *cipertext_  =x->data();
        unsigned char *cipertext = (unsigned char*)cipertext_;
        aesdec.ProcessBlock(cipertext,result);
        string ss = string(result,result+16);
        plaintextagainvs.push_back(ss);
        copy +=ss;
        cout<<ss;
    }

    output_file("t.copy",copy);
}

