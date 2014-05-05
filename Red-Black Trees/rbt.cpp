#include<iostream>
#include<conio>
using namespace std;

struct node{
    int data;
    bool color;     //0 for black and 1 for red
    node * left;
    node * right;
    node * parent;
};

class rbt{
    node * root;
    int noOfNodes, noOfRedNodes;
    void insertRBT(int);
    void display();
};

node * findPos(int tbi,node * temp){
    if(tbi > temp->data){
        //If there is a right node recurse at that node or else return this node
        if(temp->right!=NULL)       return findPos(tbi,temp->right);
        else        return temp;
    } else {
        if(temp->left!=NULL)        return findPos(tbi,temp->left);
        else        return temp;
    }
}

void rotateLL(node * gp,int z){
    node * ggp = gp->parent;
    node * pp = gp->left;
    if(z==1)    ggp->right = pp;
    else        ggp->left = pp;
    gp->parent = pp;
    gp->left = pp->right;
}

void rotateRR(node * gp,int z){
    node * ggp = gp->parent;
    node * pp = gp->right;
    if(z==1)    ggp->right = pp;
    else        ggp->left = pp;
    gp->parent = pp;
    gp->right = pp->left;
}

void rotateLR(node * gp,int z){
    node * ggp = gp->parent;
    node * p = gp->left->right;
    if(z==1)    ggp->right = p;
    else        ggp->left = p;
    gp->left->right = gp->left->right->left;
    gp->left->parent = p;
    gp->left = gp->left->right->right;
    gp->parent = gp;
}

void rotateRL(node * gp,int z){
    node * ggp = gp->parent;
    node * p = gp->left->right;
    if(z==1)    ggp->right = p;
    else        ggp->left = p;
    gp->right->left = gp->right->left->right;
    gp->right->parent = p;
    gp->right = gp->right->left->left;
    gp->parent = gp;
}

void checkRotation(node * temp){
    //-----------------------------------Finding the defect location-----------------------------------//
    node * temp2 = temp;
    while(temp->parent!=NULL){
        if(temp->color==1){
            if(temp->parent->color==1){
                temp2 = temp;
                break;
            }
        }
    }
    //Now we have the defect location
    if(temp->parent==NULL)      return;
    else {
        //-----------------------------------Finding the rotation type-----------------------------------//
        int x,y,r;  //x,y (0 for left and 1 for right)  and r (0 for black and 1 for red)
        node * p,pp,gp,t;
        p = temp2;
        pp =  p->parent;
        gp = pp->parent;
        //Now we have to find XY
        if(pp->data > gp->data)     x = 1;
        else    x = 0;
        if(p->data > pp->data)      y = 1;
        else    y = 0;
        //Now we have to find r
        if(x=1){
            t = gp->left;
            if(t->color==0)      r=0;
            else        r=1;
        } else {
            t = gp->right;
            if(t->color==0)     r=0;
            else        r=1;
        }
        //-----------------------------------Doing the real rotation--------------------------------------//
        //If XYr , r=1 then no need of rotation only color change will work
        if(r=1){
            if(gp->parent!=NULL){
                //gp is not root
                gp->color = 1;
            }
            pp->color = 0;
            t->color = 0;
            //We need to continue rebalancing
            checkRotation(gp);
        } else {
            //all the rotations are done in this else part
            //Initializations
            node * ggp = gp->parent;
            int z;
            if(gp->data > ggp->data)        z=1;
            else        z=0;
            //Basic color changes required
            pp->color = 0;
            gp->color = 1;
            if(x==0 && y==0){
                rotateLL(gp,z);
            } else if (x==0 && y==1){
                rotateLR(gp,z);
            } else if (x==1 && y==0){
                rotateRL(gp,z);
            } else {
                rotateRR(gp,z);
            }
        }
    }
}

void rbt::insertRBT(int tbi){
    node * myNode = new node();
    node * temp;
    if(root==null){
        //No node inserted till now
        myNode->data = tbi;
        myNode->left = null;
        myNode->right = null;
        myNode->color = 0;
        myNode->parent = null;
        root = myNode;
    } else {
        temp = findPos(tbi,root);
        if(tbi > temp->data){
            temp->right = myNode;
            myNode->left = null;
            myNode->right = null;
            myNode->parent = temp;
            myNode->color = 1;
        } else {
            temp->left = myNode;
            myNode->left = null;
            myNode->right = null;
            myNode->parent = temp;
            myNode->color = 1;
        }
    }
    //Now we need to check for rotations
    checkRotation(myNode);
}

void rbt::display(){
    cout<<temp->left<<endl;
}

int main(){

    return 0;
}
