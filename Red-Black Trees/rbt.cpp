#include<iostream>
#include<cstdio>
using namespace std;

//Basic unit structure for the tree
struct node{
    int data;
    bool color;     //0 for black and 1 for red
    node * left;
    node * right;
    node * parent;
};

//Basic unit of the queue
struct qNode{
    node * content;
    qNode * next;
};

//Class of the red-black tree
class rbt{
    public:
        //Constructors
        rbt(){
            this->start = NULL;
            this->finish = NULL;
            this->root = NULL;
        }
        ~rbt(){
            start = NULL;
            finish = NULL;
            root = NULL;
        }
        //For the queue
        qNode * start;
        qNode * finish;
        void insQueue(node *);
        node * delQueue();
        //For the red-black tree
        node * root;
        int noOfNodes, noOfRedNodes;
        void rotateLL(node * gp, int z);
        void rotateRR(node * gp, int z);
        void rotateLR(node * gp, int z);
        void rotateRL(node * gp, int z);
        void checkRotation(node * temp);
        node * findPos(int tbi,node * temp);
        void insertRBT(int tbi);
        void removeRBT(node * temp,int z);
        void findRot(node * temp);
        void deleteRBT(int tbd);
        void displayRBT(node * temp);
};

//-----------------------------------SET OF ROTATION FUNCTIONS-----------------------------------//
void rbt::rotateLL(node * gp,int z){
    cout<<"LL"<<endl;
    node * pp = gp->left;
    if(z>=0){
        node * ggp = gp->parent;
        if(z==1)    ggp->right = pp;
        else        ggp->left = pp;
        pp->parent = ggp;
    } else {
        this->root = pp;
        pp->parent = NULL;
    }
    gp->parent = pp;
    gp->left = pp->right;
    pp->right = gp;
}
void rbt::rotateRR(node * gp,int z){
    cout<<"RR"<<endl;
    node * pp = gp->right;
    if(z>=0){
        node * ggp = gp->parent;
        if(z==1)    ggp->right = pp;
        else        ggp->left = pp;
        pp->parent = ggp;
    } else {
        this->root = pp;
        pp->parent = NULL;
    }
    gp->parent = pp;
    gp->right = pp->left;
    pp->left = gp;
}
void rbt::rotateLR(node * gp,int z){
    this->rotateRR(gp->left,0);
    this->rotateLL(gp,z);
}
void rbt::rotateRL(node * gp,int z){
    this->rotateLL(gp->right,1);
    this->rotateRR(gp,z);
}
//-----------------------------------END OF ROTATION FUNCTIONS-----------------------------------//

//-----------------------------------SET OF INSERTION FUNCTIONS-----------------------------------//
//Function to find location and type of deformity and find the type of rotation required
void rbt::checkRotation(node * temp){
    //-----------------------------------Finding the defect location-----------------------------------//
    node * temp2 = temp;
    while(temp->parent!=NULL){
        if(temp->color==1){
            if(temp->parent->color==1){
                temp2 = temp;
                break;
            }
        }
        temp = temp->parent;
    }
    //Now we have the defect location
    if(temp->parent==NULL)      return;
    else {
        //-----------------------------------Finding the rotation type-----------------------------------//
        int x,y,r;  //x,y (0 for left and 1 for right)  and r (0 for black and 1 for red)
        node * p, * pp, * gp, * t;
        p = temp2;
        pp =  p->parent;
        gp = pp->parent;
        //Now we have to find XY
        if(pp->data > gp->data)     x = 1;
        else    x = 0;
        if(p->data > pp->data)      y = 1;
        else    y = 0;
        //Now we have to find r
        if(x==1){
            t = gp->left;
            if(!t)      r=0;
            else if(t->color==0)      r=0;
            else        r=1;
        } else {
            t = gp->right;
            if(!t)      r=0;
            else if(t->color==0)     r=0;
            else        r=1;
        }
        //-----------------------------------Doing the real rotation--------------------------------------//
        //If XYr , r=1 then no need of rotation only color change will work
        if(r==1){
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
            int z;
            if(gp->parent){
                node * ggp = gp->parent;
                if(gp->data > ggp->data)        z=1;
                else        z=0;
            } else {
                z = -1;
            }
            if(x==0 && y==0){
                pp->color = 0;
                gp->color = 1;
                this->rotateLL(gp,z);
            } else if (x==0 && y==1){
                p->color = 0;
                gp->color = 1;
                this->rotateLR(gp,z);
            } else if (x==1 && y==0){
                p->color = 0;
                gp->color = 1;
                this->rotateRL(gp,z);
            } else {
                pp->color = 0;
                gp->color = 1;
                this->rotateRR(gp,z);
            }
        }
    }
}
//Function to find the position where is the element is to be inserted in the bst
node * rbt::findPos(int tbi,node * temp){
    if(tbi > temp->data){
        //If there is a right node recurse at that node or else return this node
        if(temp->right!=NULL)       return this->findPos(tbi,temp->right);
        else        return temp;
    } else {
        if(temp->left!=NULL)        return this->findPos(tbi,temp->left);
        else        return temp;
    }
}
//Main function used to insert in the red-black tree
void rbt::insertRBT(int tbi){
    node * myNode = new node;
    node * temp;
    myNode->data = tbi;
    myNode->left = NULL;
    myNode->right = NULL;
    if(this->root==NULL){
        //No node inserted till now
        myNode->color = 0;
        myNode->parent = NULL;
        this->root = myNode;
        cout<<"Element inserted"<<endl;
        return;
    } else {
        temp = this->findPos(tbi,this->root);
        myNode->parent = temp;
        myNode->color = 1;
        if(tbi > temp->data){
            temp->right = myNode;
        } else {
            temp->left = myNode;
        }
    }
    //Now we need to check for rotations
    this->checkRotation(myNode);
    cout<<"Element inserted"<<endl;
}
//-----------------------------------END OF INSERTION FUNCITONS-----------------------------------//

//-----------------------------------SET OF DELETION FUNCTIONS------------------------------------//
//function to remove the node premanently
void rbt::removeRBT(node * temp,int z){
    if(z==-1)       this->root = NULL;
    else if(z==1)   temp->parent->right = NULL;
    else            temp->parent->left = NULL;
}
//function to find the deletion defect type and correct
void rbt::findRot(node * temp){
    if(temp->parent==NULL){
        //temp is root
        this->root = NULL;
        delete temp;
    } else {
        node * py, * v, * a, * b, * y;
        int x,c,n;   //x (o for left and 1 for right)  c (0 for black and 1 for red)  n (no of red child of v)
        y = temp;
        py = y->parent;
        if(y->data > py->data){
            v = py->left;
            x = 1;
        } else {
            v = py->right;
            x = 0;
        }
        a = v->left;
        b = v->right;
        c = v->color;
        if(v->left->color)      n++;
        if(v->right->color)     n++;
        if(c==0){
            if(n==0){
                v->color = 1;
                if(py->color==1){
                    py->color = 0;
                    return;
                } else {
                    py->color = 0;
                    findRot(py);
                }
            } else if (n==1) {

            }
        } else {

        }
    }
}
//Main function to delete from RBT
void rbt::deleteRBT(int tbd){
    node * temp = root;
    //Find the position
    while(temp->data!=tbd){
        if(temp->data < tbd)    temp = temp->right;
        else        temp = temp->left;
    }
    //Now we have the element
    if((!temp->left) && (!temp->right)){
        //If there is no child
        if(temp->color==1){
            //If the red node is deleted
            int z;
            if(temp->parent){
                if(temp->parent->data > temp->data)     z=0;
                else        z=1;
            } else {
                z=-1;
            }
            this->removeRBT(temp,z);
            return;
        }
    } else if(!temp->left){
        //If there is a right child
        //Find the dummy
        node * dummy = temp->right;
        while(dummy->left)     dummy = dummy->left;
        int z;
        if(temp->right == dummy)    z=1;
        else        z=0;
        temp->data = dummy->data;
        temp = dummy;
        if(temp->color==1){
            //if the red node is deleted
            this->removeRBT(temp,z);
            return;
        }
    } else {
        //There is a left child
        //Find the dummy
        node * dummy = temp->left;
        while(dummy->right)     dummy = dummy->right;
        int z;
        if(temp->left == dummy)    z=0;
        else        z=1;
        temp->data = dummy->data;
        temp = dummy;
        if(temp->color==1){
            //if the red node is deleted
            this->removeRBT(temp,z);
            return;
        }
    }
    //Now we have dealed with all the cases in which red node was deleted
    //Now we have to delete an ext. node temp which is a black node
    this->findRot(temp);
}
//-----------------------------------END OF DELETION FUNCTIONS------------------------------------//

//-----------------------------------SET OF FUNCTIONS TO DISPLAY TREE-----------------------------------//
//Function to insert in the queue
void rbt::insQueue(node * temp){
    qNode * myNode = new qNode;
    myNode->content = temp;
    if(this->start==NULL){
        this->start = myNode;
        this->finish = myNode;
    } else {
        this->finish->next = myNode;
        myNode->next = NULL;
        this->finish = myNode;
    }
}
//Function to remove from the queue
node * rbt::delQueue(){
    node * myNode = this->start->content;
    qNode * temp = this->start;
    this->start = this->start->next;
    delete temp;
    return myNode;
}
//Main function to display the red-black tree
void rbt::displayRBT(node * temp){
    if(!temp)   return;
    cout<<"     "<<"("<<temp->color<<")"<<temp->data;
    if(temp->parent)    cout<<"{"<<temp->parent->data<<"}";
    if(temp->left)      this->insQueue(temp->left);
    if(temp->right)     this->insQueue(temp->right);
    while(this->start!=NULL)    this->displayRBT(delQueue());
}
//-----------------------------------END OF DISPLAY FUNCTIONS-----------------------------------//

int main(){
    cout<<"This program will let you perform simple operations in a RED-BLACK TREE:"<<endl;
    bool leave = false;
    rbt * myTree = new rbt();
    do{

        cout<<endl<<endl;
        cout<<"What do you want to do with the tree:"<<endl<<"1.View the tree"<<endl<<"2.Add another node"<<endl<<"3.Search an element"<<endl<<"4.delete an element"<<endl<<"5.Exit"<<endl;
        cout<<endl;
        int choice,no;
        cin>>choice;
        switch(choice){
            case 1:
                myTree->displayRBT(myTree->root);
                break;
            case 2:
                cout<<"Enter the element to be inserted."<<endl;
                cin>>no;
                myTree->insertRBT(no);
                break;
            case 3:
                //cout<<"Enter the element to be searched."<<endl;
                //cin>>no;
                //search(no);
                break;
            case 4:
                cout<<"Enter the element to be deleted."<<endl;
                cin>>no;
                myTree->deleteRBT(no);
                break;
            case 5:
                leave = true;
                break;
            default:
                cout<<"Invalid choice.Select again."<<endl;
                break;
        }
    } while(!leave);
    return 0;
}
