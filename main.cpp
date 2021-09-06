#include <bits/stdc++.h>
using namespace std;

//function prototype
int take_input(int &idx1,int &idx2);

//Essential variables
int counter = 0;
int counter2 = 0;
int play_state;
bool stack1 = true,stack2 = false;

//Essential Data Structures (containers)
int arr[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
int freq[13] = {0};
stack<int> st1;
stack<int> st2;
vector<int> v;

//Node Structure
struct Node{
    int data;
    Node *left, *right;
};

//Main node
Node* root;

void print_tree(vector<int>grid){
    int i = 0;
    for (int level = 1; level <= 5; ++level) {
        switch (level) {
            case 1:
                cout<<"                                     "<<grid[i++]<<"\n\n";
                break;
                case 2:
                    cout<<"                      "<<grid[i++]<<"                               "<<grid[i++]<<"\n\n";
                    break;
                    case 3:
                        cout<<"              "<<grid[i++]<<"               "<<grid[i++]<<"                 "<<grid[i++]<<"              "<<grid[i++]<<"\n\n";
                        break;
                        case 4:
                            cout<<"\t  "<<grid[i++]<<"       "<<grid[i++]<<"       "<<grid[i++]<<"       "<<grid[i++]<<"       "<<grid[i++]<<"       "<<grid[i++]<<"      "<<grid[i++]<<"       "<<grid[i++]<<"\n\n";
                            break;
                            case 5:
                                cout<<"        "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"  "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"   "<<grid[i++]<<"\n\n";
                                break;
        }
    }
    cout<<"------------------------------------"<<endl;
    if(st2.size() == 0){
        cout<<st1.top()<<" "<<"EMPTY"<<endl;
    }
    else if(st1.size() == 0)
        cout<<"EMPTY"<<"  "<<st2.top()<<endl;
    else
        cout<<st1.top()<<"  "<<st2.top()<<endl;
}

Node* newNode(int data)
{
    Node* temp = new Node();
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

Node* InsertNode(Node* root, int data)
{
    if (root == NULL) {
        root = newNode(data);
        return root;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        if (temp->left != NULL)
            q.push(temp->left);
        else {
            temp->left = newNode(data);
            return root;
        }
        if (temp->right != NULL)
            q.push(temp->right);
        else {
            temp->right = newNode(data);
            return root;
        }
    }
}

//functions that randomize the cards
void random_elements(){
    v.clear();
    srand(time(0));
    int idx;
    while(counter != 31){
        do{
            idx = rand() % 13;
        }
        while(freq[idx] == 4);
        root = InsertNode(root,arr[idx]);
        v.push_back(arr[idx]);
        freq[idx]++;
        counter++;
    }
}

void random_stack(){
    while (!st1.empty()){
        st1.pop();
    }
    while (!st2.empty()){
        st2.pop();
    }
    counter = 0;
    int idx;
    while(counter != 21){
        do{
            idx = rand() % 13;
        }
        while(freq[idx] == 4);
        st1.push(arr[idx]);
        freq[idx]++;
        counter++;
    }
}

//function that shuffle the values between stacks
void shuffle(){
    if(stack1){
        st2.push(st1.top());
        st1.pop();
    } else{
        st1.push(st2.top());
        st2.pop();
    }
    if(st1.empty()){
        stack1 = false;
        stack2 = true;
    }
    else if(st2.empty()){
        stack1 = true;
        stack2 = false;
    }
}

//function that returns the selected node
Node* Curr_Node_Selected(int idx) {
    queue<Node*> curr_Nodes;
    counter2 = 0;
    Node* curr;
    if (root == NULL)
        return NULL;
    // starting with the root of the binary tree
    curr_Nodes.push(root);
    counter2++;
    if(counter2 == idx){
        return root;
    }
    // iterate on the nodes till reach the selected node in the binary tree
    while (counter2 < idx) {
        // dequeue the front node and make it curr
        curr = curr_Nodes.front();
        curr_Nodes.pop();
        if (curr->left != NULL){
            curr_Nodes.push(curr->left);
            counter2++;
        }
        if(counter2 == idx){
            return curr->left;
        }
        // enqueue the right child
        if (curr->right != NULL && counter2 < idx){
            curr_Nodes.push(curr->right);
            counter2++;
        }
        if(counter2 == idx){
            return curr->right;
        }
    }
}

//functions that takes and validates the input
bool valid_input_Tree_Tree(int idx1, int idx2){
    if(idx1 < 0 || idx1 > 30 || idx2 < 0 || idx2 > 30){
        return false;
    }

    Node* Leaf1 = Curr_Node_Selected(idx1+1);
    Node* Leaf2 = Curr_Node_Selected(idx2+1);

    if((Leaf1->data + Leaf2->data == 13) && ((Leaf1->left == NULL && Leaf1->right == NULL) || (Leaf1->left->data == 0 && Leaf1->right->data == 0)) && ((Leaf2->left == NULL && Leaf2->right == NULL) || (Leaf2->left->data == 0 && Leaf2->right->data == 0))){
        return true;
    }

    return false;
}

//case 1
int Tree_Tree(int &idx1,int &idx2){
    do {
        cout<<"LEAF 1 : ";
        cin>>idx1;
        cout<<"LEAF 2 : ";
        cin>>idx2;
    } while (!valid_input_Tree_Tree(idx1,idx2) && idx1 != -1 && idx2 != -1);
    if(idx1 == -1 && idx2 == -1){
        return take_input(idx1,idx2);
    }
    return play_state;
}

bool valid_input_Tree_Stack(int idx, int StackNo){
    if(idx < 0 || idx > 30 || StackNo < 0 || StackNo > 1){
        return false;
    }
    Node* Leaf = Curr_Node_Selected(idx+1);

    if(StackNo == 0){
        if(!st1.empty() && (Leaf->data + st1.top() == 13) && ((Leaf->left == NULL && Leaf->right == NULL) || (Leaf->left->data == 0 && Leaf->right->data == 0))){
            return true;
        }
    } else{
        if(!st2.empty() && (Leaf->data + st2.top() == 13) && ((Leaf->left == NULL && Leaf->right == NULL) || (Leaf->left->data == 0 && Leaf->right->data == 0))){
            return true;
        }
    }

    return false;
}

//case 2
int Tree_Stack(int &idx,int &StackNo){
    do {
        cout<<"LEAF : ";
        cin>>idx;
        cout<<"STACK : ";
        cin>>StackNo;
    } while (!valid_input_Tree_Stack(idx,StackNo) && idx != -1 && StackNo != -1);
    if(idx == -1 && StackNo == -1){
        return take_input(idx,StackNo);
    }
    return play_state;
}

bool valid_input_Stack_Stack(int StackNo1, int StackNo2){
    if(StackNo1 == StackNo2){
        return false;
    }
    if(StackNo1 < 0 || StackNo1 > 1 || StackNo2 < 0 || StackNo2 > 1){
        return false;
    }
    if(st1.empty() || st2.empty()){
        return false;
    } else if(st1.top()+st2.top() != 13){
        return false;
    }
    return true;
}

//case 3
int Stack_Stack(int &StackNo1,int &StackNo2){
    do {
        cout<<"STACK 1 : ";
        cin>>StackNo1;
        cout<<"STACK 2 : ";
        cin>>StackNo2;
    } while (!valid_input_Stack_Stack(StackNo1,StackNo2) && StackNo1 != -1 && StackNo2 != -1);
    if(StackNo1 == -1 && StackNo2 == -1){
        return take_input(StackNo1,StackNo2);
    }
    return play_state;
}

//main input function
int take_input(int &idx1,int &idx2){
    do{
        cout<<"Enter play status : 1)T->T OR 2)T->S OR 3)S->S OR 4)SHUFFLE :- \n";
        cin>>play_state;
    }
    while (play_state > 5 && play_state < 1);

    switch (play_state) {
        case 1:
            return Tree_Tree(idx1,idx2);
            break;
            case 2:
                return Tree_Stack(idx1,idx2);
                break;
                case 3:
                    return Stack_Stack(idx1,idx2);
                    break;
                    case 4:
                        shuffle();
                        print_tree(v);
                        return take_input(idx1,idx2);
                        break;
    }
}

//function that delete cards according to current play state
void delete_leaf(int idx1, int idx2, int play_state){
    Node* Leaf;
    switch (play_state) {
        case 1:
            Leaf = Curr_Node_Selected(idx1+1);
            Leaf->data = 0;
            v[idx1]=0;
            Leaf = Curr_Node_Selected(idx2+1);
            Leaf->data = 0;
            v[idx2]=0;
            break;
            case 2:
                Leaf = Curr_Node_Selected(idx1+1);
                Leaf->data = 0;
                v[idx1]=0;
                if(idx2 == 0){
                    st1.pop();
                }
                else{
                    st2.pop();
                }
                break;
                case 3:
                    st1.pop();
                    st2.pop();
                    break;
    }
}

//function that detects if there is a win state
bool check_win(){
    for (const auto &item : v) {
        if(item!=0){
            return false;
        }
    }
    if(st1.empty() && st2.empty()){
        return true;
    }
}

//main play function
void play(){
    while (true){
        print_tree(v);
        int idx1,idx2;
        int play_state = take_input(idx1,idx2);
        delete_leaf(idx1,idx2,play_state);
        if(check_win()){
            cout<<"Woah!! Winning State!!"<<endl;
            break;
        }
    }
}

//main function
int main()
{
    char Selection;
    do{
        random_elements();
        random_stack();
        play();
        cout<<"Do You Want To Play Again (Y/y - N/n) : ";
        cin>>Selection;
    } while (Selection != 'N' || Selection != 'n');
}