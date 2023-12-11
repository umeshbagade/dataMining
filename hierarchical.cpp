#include<bits/stdc++.h>
using namespace std;

void mergeClusters(map<string , map<string,int>   > &matrix){

    if(matrix.size()==1) return;
    int mini = INT_MAX;
    string from, to;

    for(auto it: matrix){
        
        for(auto itr: it.second)
            if(itr.second < mini){
                mini = itr.second;
                from = it.first;
                to = itr.first;
            }
    }

    cout<<"merging "<<from<<" and "<<to<<" as their distance is "<<mini<<" which is minimum:\n";

    for(auto it: matrix){
        if(it.first==from ){

            for(auto itr: it.second){
                matrix[it.first][itr.first] = min(itr.second, matrix[to][itr.first]); 
            }


        }
    }

    //deleting to
    matrix.erase(to);
    for(auto &it: matrix){
       it.second.erase(to);
    }


    map<string, map<string,int>> newMatrix;

    string newname = from+to;
    for(auto &it: matrix){
        
        map<string,int> row;

        for(auto &itr: it.second){
            if(itr.first==from)
                row[newname] = itr.second;
            else row[itr.first] = itr.second;
        }

        if(it.first==from){
            newMatrix[newname] = row;
        }else{
            newMatrix[it.first] = row;
        }
    }
    bool initial = true;
    cout<<"    ";
    for(auto it: newMatrix){
        if(initial){
            for(auto name : it.second){
                cout<<name.first<<"   ";
                break;
            }
            initial = false;
        }
        cout<<it.first<<"   ";
    }
    cout<<endl;
    for(auto it: newMatrix){
        cout<<it.first<<"   ";
        for(auto itr: it.second){
            cout<<itr.second<<"   ";
        }
        cout<<endl;
    }

    matrix.clear();
    mergeClusters(newMatrix);

}
int main() {

    ifstream fin("input.csv");

    string line, word;

    map<string , map<string,int>   > matrix;



    getline(fin, line);
    stringstream ss(line);
    getline(ss,word,',');
    vector<string> attributes;
    while(getline(ss, word,',')){
        attributes.push_back(word);
    }
    int row=0;
    while(getline(fin, line)){

        stringstream stss(line);
        getline(stss, word,',');
        int col=0;
        while (getline(stss, word,',')){
            matrix[attributes[row]][attributes[col]] = stoi(word);
            col++;
        }
        row++;
    }

    for(auto it: matrix){
        cout<<it.first<<"-"<<endl;
        for(auto itr: it.second)
            cout<<itr.first<<" "<<itr.second<<endl;
    }
    mergeClusters(matrix);
    fin.close();
    return 0;
}
