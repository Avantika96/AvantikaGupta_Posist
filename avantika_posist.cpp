#include<bits/stdc++.h>
#include <string>
using namespace std;
static int curr_node_no=0;
int sum_left;
int curr_id=0;
struct node{
    time_t timestamp;
    char data;
    int nodeNumber;
    char nodeId[33];
    char referenceNodeId[33];
    char childReferenceNodeId[33];
    char genesisReferenceNodeId[33];
    string HashValue;
    node *left;
    node *right;
};
struct node *genesis_node;
struct node* newNode(struct node *parent,int key)
{
        struct node *temp;
        temp=new node();
        temp->timestamp=time(0);
        temp->data=(char)key;
        temp->nodeNumber=++curr_node_no;
        int dec=curr_id;
        char bin32[]  = "00000000000000000000000000000000";
        for (int pos = 31; pos >= 0; --pos)
        {
            if (dec % 2)
                bin32[pos] = '1';
            dec /= 2;
        }
        for(int i=0;bin32[i]!='\0';i++){
            temp->nodeId[i]=bin32[i];
        }
        curr_id++;
        strcpy(temp->referenceNodeId,parent->nodeId);
        strcpy(temp->genesisReferenceNodeId,genesis_node->nodeId);
        strcpy(parent->childReferenceNodeId,temp->nodeId);
        return temp;
};
void insert_into(struct node* temp, int key)
{
    if(sum_left<key){
        cout<<"This node cannot be inserted as the sum of values of nodes is greater than that of genesis node"<<endl;
        return;
    }
    else{
        sum_left=sum_left-key;
    }
    queue<struct node*> q;
    q.push(temp);

    while (!q.empty()) {
        struct node* temp = q.front();
        q.pop();

        if (!temp->left) {
            temp->left = newNode(temp,key);
            break;
        } else
            q.push(temp->left);

        if (!temp->right) {
            temp->right = newNode(temp,key);
            break;
        } else
            q.push(temp->right);
    }
}
void print_node_data(struct node *ptr){
    cout<<endl<<endl;
    cout<<"Timestamp:"<<ptr->timestamp<<endl;
    cout<<"Data:"<<ptr->data<<endl;
    cout<<"NodeNumber:"<<ptr->nodeNumber<<endl;
    cout<<"NodeId:"<<ptr->nodeId<<endl;
    cout<<"ReferenceNodeId:"<<ptr->referenceNodeId<<endl;
    cout<<"ChildReferenceNodeId:"<<ptr->childReferenceNodeId<<endl;
    cout<<"GenesisReferenceNodeId:"<<ptr->genesisReferenceNodeId<<endl;
}
void print_node_actualdata(struct node *ptr){
    cout<<endl<<endl;
    int value=ptr->data;
    cout<<"Timestamp:"<<ptr->timestamp<<endl;
    cout<<"Data:"<<value<<endl;
    cout<<"NodeNumber:"<<ptr->nodeNumber<<endl;
    cout<<"NodeId:"<<ptr->nodeId<<endl;
    cout<<"ReferenceNodeId:"<<ptr->referenceNodeId<<endl;
    cout<<"ChildReferenceNodeId:"<<ptr->childReferenceNodeId<<endl;
    cout<<"GenesisReferenceNodeId:"<<ptr->genesisReferenceNodeId<<endl;
}
void inorder(struct node* temp)
{
    if (!temp)
        return;

    inorder(temp->left);
    print_node_data(temp);
    inorder(temp->right);
}
void view(struct node* temp)
{
    if (!temp)
        return;

    inorder(temp->left);
    print_node_actualdata(temp);
    inorder(temp->right);
}
void create_genesis(){
    if(genesis_node==NULL){
        int value;
        cout<<"Enter the value of the node"<<endl;
        cin>>value;
        sum_left=value;
        genesis_node=new node();
        genesis_node->timestamp=time(0);
        genesis_node->data=(char)value;
        genesis_node->nodeNumber=++curr_node_no;
        int dec=curr_id;
        char bin32[]  = "00000000000000000000000000000000";
        for (int pos = 31; pos >= 0; --pos)
        {
            if (dec % 2)
                bin32[pos] = '1';
            dec /= 2;
        }
        for(int i=0;bin32[i]!='\0';i++){
            genesis_node->nodeId[i]=bin32[i];
        }
        curr_id++;
        strcpy(genesis_node->referenceNodeId,"No Parent");
        strcpy(genesis_node->genesisReferenceNodeId,genesis_node->nodeId);
    }
    else{
        cout<<"Genesis node exist"<<endl;
    }
}
void create_node(){
    int value;
    cout<<"Enter the value of the node"<<endl;
    cin>>value;
    insert_into(genesis_node,value);
}
int main(){
    int ch;
    cout<<"Choose from following options:"<<endl;
    cout<<"1.Create Genesis Node"<<endl;
    cout<<"2.Create New Node"<<endl;
    cout<<"3.Traversal of records"<<endl;
    cout<<"4.Owner wants to view records (Passkey: abcd)"<<endl;
    do{
        cout<<"Enter the option:"<<endl;
        int opt;
        cin>>opt;
        switch(opt){
        case 1:
            create_genesis();
            //print_node_data(genesis_node);
            break;
        case 2:
            create_node();
            break;
        case 3:
            inorder(genesis_node);
            break;
        case 4:
            char pass[5];
            cout<<"Enter passkey: "<<endl;
            char verify[]="abcd";
            cin>>pass;
            if(strcmp(verify,pass)==0){
                view(genesis_node);
            }
            else{
                cout<<"Invalid passkey"<<endl;
            }
            break;
        }
        cout<<"If you want to continue press 1 else 0"<<endl;
        cin>>ch;
    }while(ch);
}






