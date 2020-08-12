#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <stack>
using namespace std;


struct node{
    int value;
    node *left;
    node *right;
    string action="";
    bool isLeaf;
};
struct Root {
    string result;
    node* left;
    node* right;
    bool isLeaf;
};
Root * buildRoot(){
    string result ="";
    Root* trie = new Root;
    trie->left = nullptr;
    trie->right = nullptr;
    return trie;
}
node* buildNode(){
    string result="";
    node* trie = new node;
    trie->left = nullptr;
    trie->right = nullptr;
    return trie;
}
class btree{
public:
    btree();
    ~btree();
    node *left;
    node *right;
    node *search(int key);
    void destroy_tree();
    void inorder_print();
    void postorder_print();
    void preorder_print();
    void ADD(vector<string> info, node* tree);

private:
    void destroy_tree(node *leaf);
    node *search(int key, node *leaf);
    void inorder_print(node *leaf);
    void postorder_print(node *leaf);
    void preorder_print(node *leaf);

    node *root;
};


btree::btree(){
    node* root = new node();

}

btree::~btree(){
    destroy_tree();
}

void btree::destroy_tree(node *leaf){
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
void ADD(vector<string> info, Root* trie, string prefix) {
    int first, second, third, four, submask;
    char nekoda;
    string prefixToAdd = prefix;
    istringstream k(prefixToAdd);
    k >> first >> nekoda >> second >> nekoda >> third >> nekoda >> submask;
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
    node* position;
    if(arrOfBinary[0] == "0"){
        if(trie->left == nullptr){
            trie->left = buildNode();
        }
        position = trie->left;
    }
    else{
        if(trie->right == nullptr){
            trie->right = buildNode();
        }
        position = trie->right;
    }
    for(int i=1;i<submask;i++){
        if(arrOfBinary[i] == "0"){
            if(position->left == nullptr){
                position->left = buildNode();
            }
            position = position->left;
        }
        else{
            if(position->right == nullptr){
                position->right = buildNode();
            }
            position = position->right;
        }
    }
    position->action = info[1];
    position->isLeaf = true;
    cout<<"Added " << info[0] << " "<< info[1];
}
node *btree::search(int key, node *leaf){
    if(leaf != NULL){
        if(key == leaf->value){
            return leaf;
        }
        if(key < leaf->value){
            return search(key, leaf->left);
        }else{
            return search(key, leaf->right);
        }
    }else{
        return NULL;
    }
}

node *btree::search(int key){
    return search(key, root);
}

void btree::destroy_tree(){
    destroy_tree(root);
}

void btree::inorder_print(){
    inorder_print(root);
    cout << "\n";
}

void btree::inorder_print(node *leaf){
    if(leaf != NULL){
        inorder_print(leaf->left);
        cout << leaf->value << ",";
        inorder_print(leaf->right);
    }
}

void btree::postorder_print(){
    postorder_print(root);
    cout << "\n";
}

void btree::postorder_print(node *leaf){
    if(leaf != NULL){
        inorder_print(leaf->left);
        inorder_print(leaf->right);
        cout << leaf->value << ",";
    }
}

void btree::preorder_print(){
    preorder_print(root);
    cout << "\n";
}

void btree::preorder_print(node *leaf){
    if(leaf != NULL){
        cout << leaf->value << ",";
        inorder_print(leaf->left);
        inorder_print(leaf->right);
    }
}

int main(int argc, char**argv){

    //btree tree;
    Root *trie = buildRoot();
    string line;
    ifstream inputFile;
    inputFile.open(argv[1]);
    if(inputFile.is_open()){
        while(getline(inputFile,line)) { // run until the line end
            vector<string> info;
            istringstream re(line);
            for (string s; re >> s;) {
                info.push_back(s);
                cout<<s<<endl;
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
            }
        }
        inputFile.close();
        cout<<"Success opening the file!"<<endl;
    }else
        cout<<"Failed open the file!"<<endl;
   // tree->insert(10);
   // tree->insert(6);
  //  tree->insert(14);
    //tree->preorder_print();

    //delete tree;

}