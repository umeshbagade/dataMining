#include<bits/stdc++.h>
using namespace std;
double getMean(vector<double> &v){
    double sum =0;
    for(double d: v) sum += d;
    return sum/v.size();
}
double standardDeviation(vector<double> &v){
    double mean = getMean(v);

    double sum=0;
    for(double d: v){
        sum += (d-mean)*(d-mean);
    }
    sum /= (v.size()-1);

    double sd = sqrt(sum);

    return sd;


}
int main(){

    ifstream fin("input.csv");

    string line, word;

    getline(fin, line);

    vector<double> a,b;
    while(getline(fin, line)){

        stringstream ss(line);
        getline(ss, word, ',');

        a.push_back(stod(word));
        getline(ss, word,',');
        b.push_back(stod(word));


    }

    double meana = getMean(a),meanb=getMean(b);

    int n = a.size();
    double aa= standardDeviation(a);
    double bb = standardDeviation(b);
    
    double correlation = 0;
    for(int i=0;i<n;i++){
        correlation += (a[i]-meana)*(b[i]-meanb);
    }
    
    correlation = correlation /( (n-1)*aa*bb);
    cout<<"Correlation Coefficient is : ";
    cout<<correlation<<endl;

    return 0;
}
