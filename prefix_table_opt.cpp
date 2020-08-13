#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <stack>
using namespace std;
bool flag = false;
struct node{
    string value;
    node *left;
    node *right;
    string action="";
    bool isLeaf;
    int depth;
    int totalInsertNode;
    node* parent;
private:
    void destroy_tree(node *leaf);

};

node* newNode(){
    //string result="";
    node* trie = new node;
    trie->left = nullptr;
    trie->right = nullptr;
    trie->depth =0;
    trie->parent = nullptr;
    trie->isLeaf=false;
    trie->totalInsertNode=0;
    return trie;
}

void node::destroy_tree(node *leaf){
    if(leaf != NULL){
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}
std::string toBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}
void optimization(node* &position,node* &trie,int &submask){ // we enter here if all the requeniment applay
    position = position->parent;
    delete (position->left);
    delete (position->right);
    position->left = position->right = nullptr;
    trie->totalInsertNode -= 2;
    submask--;
}
void ADD(vector<string> info, node* trie, string prefix) {
    int first, second, third, four, submask;
    char nekoda;
    string prefixToAdd = prefix;
    istringstream k(prefixToAdd);
    k >> first >> nekoda >> second >> nekoda >> third >> nekoda >> four >> nekoda>> submask;
    string arrOfBinary[32] = {"0"};
    string str = toBinary(first);
    int index;
    for(int i=0;i<str.length();i++){
        arrOfBinary[i] = str[i];
        index =i;
    }
    str = toBinary(second);
    for(int i=0;i<str.length();i++){
        arrOfBinary[index+1] = str[i];
        index++;
    }
    str = toBinary(third);
    for(int i=0;i<str.length();i++){
        arrOfBinary[index+1] = str[i];
        index++;
    }
    if(four == 0){
        arrOfBinary[index+1] = "0";
    }else {
        str = toBinary(four);
        for (int i = 0; i < str.length(); i++) {
            arrOfBinary[index + 1] = str[i];
            index++;
        }
    }

    node* position;
    if(arrOfBinary[0] == "0"){
        if(trie->left == nullptr){
            trie->left = newNode();
            trie->left->value = arrOfBinary[0];
            trie->left->depth = trie->depth+1;
            trie->totalInsertNode++;
        }
        position = trie->left;
    }
    else{
        if(trie->right == nullptr){
            trie->right = newNode();
            trie->right->value = arrOfBinary[0];
            trie->right->depth = trie->depth+1;
            trie->totalInsertNode++;
        }
        position = trie->right;
    }

    for(int i=1 ; i< submask;i++){
        cout<<arrOfBinary[i]<< " ";

        if(arrOfBinary[i].compare("0")==0){
            if(position->left == nullptr){
                position->left = newNode();
                position->left->depth = position->depth+1;
                trie->totalInsertNode++;
                position->left->parent = position;
            }
            position = position->left;
        }

        else{
            if(position->right == nullptr){
                position->right = newNode();
                position->right->depth=position->depth+1;
                trie->totalInsertNode++;
                position->right->parent = position;
            }
            position = position->right;
        }
    }
    position->action = info[1];
    position->isLeaf = true;

    if(position->parent!= nullptr){
        if(position->parent->left!= nullptr && position->parent->right!= nullptr ){
            if (position->parent->left->isLeaf == true && position->parent->right->isLeaf == true) {
                if (position->parent->left->action == position->parent->right->action) {
                    optimization(position,trie,submask); //perform optimization
                }
            }
        }
    }
    position->action = info[1];
    position->isLeaf = true;

    cout<<"Added " << info[0] << " "<< info[1]<< " at the depth "<<position->depth <<", total nodes : " << trie->totalInsertNode<<endl;
}

void FIND(vector<string>info, node* trie,string prefix){
    int first, second, third, four, sub;
    char nekoda;
    string prefixToFind = prefix;
    istringstream k(prefixToFind);
    k >> first >> nekoda >> second >> nekoda >> third >> nekoda >> four >> nekoda>> sub;
    string arrOfBinary[32] = {"0"};
    int size = 32; // for later, size of arrOfBinary
    string str = toBinary(first);
    int index;
    for(int i=0;i<str.length();i++){
        arrOfBinary[i] = str[i];
        index =i;
    }
    str = toBinary(second);
    for(int i=0;i<str.length();i++){
        arrOfBinary[index+1] = str[i];
        index++;
    }
    str = toBinary(third);
    for(int i=0;i<str.length();i++){
        arrOfBinary[index+1] = str[i];
        index++;
    }
    str = toBinary(four);
    for(int i=0;i<str.length();i++){
        arrOfBinary[index+1] = str[i];
        index++;
    }
    string tempAction = "";
    int tempActionDepth;
    if(sub>0) {
        node *position;
        if (arrOfBinary[0] == "0") {
            if (trie->left == nullptr) {
                cout << "Cannot find that" << endl;
                return;
            }
            position = trie->left;
        } else {
            if (trie->right == nullptr) {
                cout << "Cannot find that" << endl;
                return;
            }
            position = trie->right;
        }

        for (int i = 1; i < size; i++) { // 32 size of arrOfBinary
            if (position->isLeaf == true) {
                tempAction = position->action;
                tempActionDepth = position->depth;
            }
            if (arrOfBinary[i] == "0") {
                if (position->left == nullptr) {
                    if (!(tempAction.empty())) {
                        flag = true;
                        cout << "Found " << info[0] << " " << tempAction << " at the depth " << tempActionDepth << endl;
                        return;
                    } else {
                        cout << "Cannot find that" << endl;
                        return;
                    }
                }
                position = position->left;
            } else {

                if (position->right == nullptr) {
                    if (!tempAction.empty()) {
                        flag = true;
                        cout << "Found " << info[0] << " " << tempAction << " at the depth " << tempActionDepth << endl;
                        return;
                    } else {
                        cout << "Cannot find that " << endl;
                        return;
                    }
                }

                position = position->right;
            }
        }
    }
    else{
        cout<<"subnet is under or equal to 0 - there no need to find anything"<<endl;
    }
}
bool isFind(vector<string>info, node* trie,string prefix){
    int first, second, third, four, sub;
    char nekoda;
    string prefixToFind = prefix;
    istringstream k(prefixToFind);
    k >> first >> nekoda >> second >> nekoda >> third >> nekoda >> four >> nekoda>> sub;
    string arrOfBinary[32] = {"0"};
    int size = 32; // for later, size of arrOfBinary
    string str = toBinary(first);
    int index;
    for(int i=0;i<str.length();i++){
        arrOfBinary[i] = str[i];
        index =i;
    }
    str = toBinary(second);
    for(int i=0;i<str.length();i++){
        arrOfBinary[index+1] = str[i];
        index++;
    }
    str = toBinary(third);
    for(int i=0;i<str.length();i++){
        arrOfBinary[index+1] = str[i];
        index++;
    }
    str = toBinary(four);
    for(int i=0;i<str.length();i++){
        arrOfBinary[index+1] = str[i];
        index++;
    }
    string tempAction = "";
    int tempActionDepth;
    if(sub>0) {
        node *position;
        if (arrOfBinary[0] == "0") {
            if (trie->left == nullptr) {
                // cout << "Cannot find that" << endl;
                return false;
            }
            position = trie->left;
        } else {
            if (trie->right == nullptr) {
                //  cout << "Cannot find that" << endl;
                return false;
            }
            position = trie->right;
        }

        for (int i = 1; i < size; i++) { // 32 size of arrOfBinary
            if (position->isLeaf == true) {
                tempAction = position->action;
                tempActionDepth = position->depth;
            }
            if (arrOfBinary[i] == "0") {
                if (position->left == nullptr) {
                    if (!(tempAction.empty())) {
                        flag = true;
                        // cout << "Found " << info[0] << " " << tempAction << " at the depth " << tempActionDepth << endl;
                        return true;
                    } else {
                        // cout << "Cannot find that" << endl;
                        return false;
                    }
                }
                position = position->left;
            } else {

                if (position->right == nullptr) {
                    if (!tempAction.empty()) {
                        flag = true;
                        // cout << "Found " << info[0] << " " << tempAction << " at the depth " << tempActionDepth << endl;
                        return true;
                    } else {
                        // cout << "Cannot find that " << endl;
                        return true;
                    }
                }

                position = position->right;
            }
        }
    }
    else{
        cout<<"subnet is under or equal to 0 - there no need to find anything"<<endl;
    }
}
void REMOVE(vector<string> info,node* trie, string prefix){
    int first, second, third, four, submask;
    char nekoda;
    string prefixToRemov = prefix;
    istringstream k(prefixToRemov);
    k >> first >> nekoda >> second >> nekoda >> third >> nekoda >> four >> nekoda>> submask;
    string arrOfBinary[32] = {"0"};
    string str = toBinary(first);
    int index;
    for(int i=0;i<str.length();i++){
        arrOfBinary[i] = str[i];
        index =i;
    }
    str = toBinary(second);
    for(int i=0;i<str.length();i++){
        arrOfBinary[index+1] = str[i];
        index++;
    }
    str = toBinary(third);
    for(int i=0;i<str.length();i++){
        arrOfBinary[index+1] = str[i];
        index++;
    }
    str = toBinary(four);
    for(int i=0;i<str.length();i++){
        arrOfBinary[index+1] = str[i];
        index++;
    }
    node* position;
    if(arrOfBinary[0] == "0"){
        if(trie->left == nullptr){
            cout<<"There nothing to delete"<<endl;
            return;
        }
        position = trie->left;
    }
    else{
        if(trie->right == nullptr){
            cout<<"There nothing to delete"<<endl;
            return;
        }
        position = position->right;
    }
    if(isFind(info,trie,prefixToRemov) == true){
        // didnt know how to implement..
    }
}

int main(int argc, char**argv){

    //btree tree;
    node *trie = newNode();
    string line;
    ifstream inputFile;
    inputFile.open(argv[1]);
    if(inputFile.is_open()){
        while(getline(inputFile,line)) { // run until the line end
            vector<string> info;
            istringstream re(line);
            for (string s; re >> s;) {
                info.push_back(s);
            }
            string act = info[0];
            int actNum;
            if(act == "ADD"){
                actNum = 1;
            }else if (act == "FIND"){
                actNum = 2;
            }
            else{
                actNum = 3;
            }
            switch (actNum) {
                case 1:
                    info.erase(info.begin()); // delete the act
                    ADD(info,trie,info[0]);
                    break;
                case 2:
                    info.erase(info.begin());
                    FIND(info,trie,info[0]);
                    break;
                case 3:
                    info.erase(info.begin());
                    REMOVE(info,trie,info[0]);
            }
        }
        inputFile.close();
        //cout<<"Success opening the file!"<<endl;
    }else
        cout<<"Failed open the file!"<<endl;
}
