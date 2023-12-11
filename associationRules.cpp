#include<bits/stdc++.h>
using namespace std;
 vector<vector<bool>> transactions;
vector<vector<set<char>>> frequent;
int getsupport(set<char> st){
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
void getRule(set<char> s, int confidence){
    set<char> news =s;

    double aUb = getsupport(s);
    for(char ch: s){
        news.erase(ch);
        //checking news --> ch

        double a = getsupport(news);

        
        double conf = aUb*100/a;

        if(conf >= confidence) {
            for(char ch: news) cout<<ch;
            cout<<"--->"<<ch<<"   "<<conf<<endl;
        }
        news.insert(ch);
    }
}
void generateRules(int confidence){

    for(vector<set<char>> &v: frequent){
        for(set<char> &s: v){
            getRule(s, confidence);
        }
    }


}

void apriori(vector<set<char>> avail, int minsupport) {

    if(avail.size()==1) return;

    set<set<char>> newavail;

    int n = avail.size();
    bool isok = false;
    for(int i=0;i<n;i++){
        set<char> curr = avail[i];
        for(int j=i+1;j<n;j++){
            set<char> temp = avail[j];

            for(char ch: curr) temp.insert(ch);
             int sup = getsupport(temp);
            // cout<<sup<<endl;
            if(sup >= minsupport){
                newavail.insert(temp);
                isok = true;
            }
        }
    }
    if(!isok) return;
    vector<set<char>> newa;
    for(auto it: newavail) newa.push_back(it);

    frequent.push_back(newa);
    apriori(newa, minsupport);
}
int main() {

   

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

    int support, n = transactions.size(), confidence;
    cout<<"Enter minimum support: ";
    cin>>support;
    cout<<"Enter the confidence in %:";
    cin>>confidence;

    vector<set<char>> avail;

    for(char ch = 'A';ch<='Z';ch++){
        int ct=0;
        for(int i=0;i<n;i++){
            if(transactions[i][ch-'A']) ct++;
        }
        if(ct >= support){
            avail.push_back({ch});
        }
    }


    apriori(avail, support);

 
    generateRules( confidence);

    return 0;
}
