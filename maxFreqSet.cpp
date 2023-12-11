#include<bits/stdc++.h>
using namespace std;

int getsupport(vector<vector<bool>> &transactions, set<char> st){
    int ct=0;
    for(vector<bool> &b: transactions){
        bool skip = false;
        for(auto it: st){
            if(!b[it-'A']) skip = true;
        }
        if(skip) continue;

        ct++;
    }
    return ct;
}
void apriori(vector<vector<bool>> &transactions, vector<set<char>> avail, int minsupport, int k) {

    if(avail.size()==1) return;

    set<set<char>> newavail;

    int n = avail.size();

    cout<<"Frequent "<<k<<" Item set:"<<endl;
    bool isok = false;
    for(int i=0;i<n;i++){
        set<char> curr = avail[i];
        for(int j=i+1;j<n;j++){
            set<char> temp = avail[j];

            for(char ch: curr) temp.insert(ch);
             int sup = getsupport(transactions, temp);

            if(sup >= minsupport){
                newavail.insert(temp);
                for(char ch: temp) cout<<ch;
                isok = true;
                cout<<"   -> "<<sup<<endl;
            }
        }
    }
    if(!isok) return;

    vector<set<char>> newa;
    for(auto it: newavail) newa.push_back(it);
    apriori(transactions, newa, minsupport, k+1);
}
int main() {

    vector<vector<bool>> transactions;

    ifstream fin("input.csv");
    string line, word;

    while(getline(fin, line)){

        stringstream ss(line);
        vector<bool> t(26,false);
        while(getline(ss, word, ',')){
            t[word[0]-'A'] = true;
        }
        transactions.push_back(t);
    }

    int support, n = transactions.size();
    cout<<"Enter minimum support: ";
    cin>>support;

    vector<set<char>> avail;

    cout<<"Frequent 1 item set: \n";
    for(char ch = 'A';ch<='Z';ch++){
        int ct=0;
        for(int i=0;i<n;i++){
            if(transactions[i][ch-'A']) ct++;
        }
        if(ct >= support){
            cout<<ch<<" -> "<<ct<<endl;
            avail.push_back({ch});
        }
    }


    apriori(transactions, avail, support, 2);



    return 0;
}
