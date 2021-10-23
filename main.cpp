//
//  main.cpp
//  GenericTrees
//
//  Created by RAMAN TYAGI on 04/08/21.
//  Copyright © 2021 RAMAN TYAGI. All rights reserved.
// TREES WALE MEIN QUESTION MEIN EULER SE DRY RUN !!!!
//*********************GENERIC TREES**************************
/*
 ~~~~~~~~~~~~~~~~~~~~FUNCTIONS/QUESTIONS~~~~~~~~~~~~~~~~~~~~~~
 
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ~~~~~~~~~~~~~~~~~~~~~~~~NOTES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1.Are trees similar in shape : Dono trees ke children check krte jao , RECURSIVELY!
  -> Agr children ka size brabar nii hai to return false
     nhi to return true!!
   ---> Is Sawal mei aadha euler aadha hi clta hai!<---
 
 
 2.Are trees mirror in shape : Dono trees ke children check krte jao , RECURSIVELY!(**Phli node ka first children ke children check kro! and dusre ke akhri node ke children check kro**)
 -> Agr children ka size brabar nii hai to return false
    nhi to return true!!
  ---> Is Sawal mei aadha euler aadha hi clta hai!<---
 
 
 3.Is tree Symmetric : Kul milakr dekhna hai ki kya vo tree mirror hai apne hi tree ka , or agr hai to it is symmetric otherwise not Symmetric!!!
 -> Agr children ka size brabar nii hai to return false
    nhi to return true!!
  ---> Is Sawal mei aadha euler aadha hi clta hai!<---
 
 4.Static variables heap mein pde hote hai !!!
    Recursion mein humesha available...
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#include <iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
class Node
{
    public:
    int data;
    vector<Node*> children; /* Node type walo ke addresses store krega --> A list of addresses of chilfren of a particular node  */
};
void Display(Node *node)
{
   
    cout<<node->data<<"->";
       for(auto child:node->children)
       {
           cout<<child->data<<",";
       }
    cout<<".\n";
    for(auto child:node->children)
    {
        Display(child);
    }
}
int size(Node *p)//Recursion : High level thinking -> Child pe call krte hi child apne subtree ka size dega!!!
{
    int count=0;
    for(auto child:p->children)
    {
       count+=size(child);;
    }
    return count+1;
}
int maximum(Node *p)
{
    static int max=INT_MIN;
    for(auto child:p->children)
    {
      max = maximum(child);
    }
    if(p->data>max)
    max=p->data;
    return max;
}
/*
 ch - child height
 */
int height(Node *p)
{
    int ht=-1;/*Edges ke term mein calculate krni hai islie -1 lia agr Nodes ki term mein krni hoti to ht=0 se shuru krte  */
    for(auto child:p->children)
    {
       int ch=height(child);
        ht=max(ht,ch);
    }
    ht+=1;
    return ht;
}
/*void Traversal(Node *p)
{
    cout<<"Node Pre"<<p->data<<"\n";
    for(auto child:p->children)
    {
        cout<<"Edge Pre:"<<p->data<<"--"<<child->data<<"\n";
        Traversal(child);
        cout<<"Node Post"<<child->data<<"\n";
        cout<<"Edge Post"<<p->data<<"--"<<child->data<<"\n";
        
    }
 if(p==root) // ~~~PROBLEM SOLVED BY THIS->
 cout<<"Node Post"<<p->data<<"\n";
    
}*/
/* Is Traversal wale function mein galti ye hai ki :: root node ke lie post wala ni chlega, ISKA SOL BHI DAL DIA!!! -- ROOT KO GLOBAL KRDO YA ROOT KO PASS KRDO PARAMETER MEIN */
void Traversal(Node *p)
{
    // Node Pre Area
    cout<<"Node Pre:"<<p->data<<"\n";
    for(auto child:p->children)
    {
        //Edge Pre Area
        cout<<"Edge Pre:"<<p->data<<"--"<<child->data<<"\n";
        Traversal(child);
        //Edge Post Area
        cout<<"Edge Post:"<<p->data<<"--"<<child->data<<"\n";
    }
    //Node Post Area
    cout<<"Node Post:"<<p->data<<"\n";
}
/* Remove,Print,Add -- ALGO for level order*/
void levelTraversal(Node *p)
{
    queue<Node*> qt;
    qt.push(p);
    while(qt.size()!=0)
    {
        p=qt.front();
        qt.pop();
        cout<<p->data<<" ";
        for(auto child:p->children)
        {
            qt.push(child);
        }
   }
}
/*
 ~~MET1. USING 2 QUEUES
 */
void levelLineWiseTraversal1(Node *p)
{
    queue<Node*> mq;
    queue<Node*> cq;
    mq.push(p);
    while(mq.size()!=0)
    {
        p=mq.front();
        mq.pop();
        cout<<p->data<<" ";
        for(auto child:p->children)
        {
            cq.push(child);
        }
        if(mq.empty())
        {
            cout<<"\n";
            queue<Node*> tq;
            tq=cq;
            cq=mq;
            mq=tq;
 /* ******* IMP--REINITIALZIE A QUEUE :: cq**********/
        }
    }
}
/*
 ~~MET2. USING 1 QUEUE BUT USING A MARKER FOR CHANGING THE LEVELS
 */
void levelLineWiseTraversal2(Node *p)
{
    queue<Node*> qt;
    qt.push(p);
    Node *t= new Node();
    t->data=-1;
    qt.push(t);
    while(qt.size()!=0)
    {
        p=qt.front();
        qt.pop();
        if(p==t)
        {
            cout<<"\n";
            if(qt.size()!=0)
            qt.push(t);
        }
        else{
            cout<<p->data<<" ";
            for(auto child: p->children)
            {
                qt.push(child);
            }
        }
   }
}
/*
 ~~MET3. USING 1 QUEUE BUT USING COUNTER AT EVERY STEP
 */
void levelLineWiseTraversal3(Node *p)
{
    queue<Node*>qt;
    qt.push(p);
    int queue_size=qt.size();
    while(queue_size!=0)
    {
        p=qt.front();
        qt.pop();
        queue_size--;
        cout<<p->data<<" ";
        for(auto child:p->children)
        {
            qt.push(child);
        }
        if(queue_size==0)
        {
            cout<<"\n";
            queue_size=qt.size();
        }
            
    }
}
/*
 ~~MET4. USING 1 QUEUE + USING A PAIR CLASS
 */

/* *************DIMAG PE ZOR DENE WALI APPROACH**************/
class Pair{
public:
    Node *node;
    int level;
};

void levelLineWiseTraversal4(Node *p)
{
    queue<Pair> qt;
    int level=1;
    Pair cp;
    cp.node=p;
    cp.level=level;
    qt.push(cp);
   while(qt.size()!=0)
    {
        Pair cur_pair=qt.front();
        qt.pop();
        if(cur_pair.level>level)
        {
            level=cur_pair.level;
            cout<<"\n";
        }
        cout<<cur_pair.node->data<<" ";
        for(auto child:cur_pair.node->children)
        {
            Pair child_pair;
            child_pair.node=child;
            child_pair.level=cur_pair.level+1;
            qt.push(child_pair);
        }
    }
    
}
void levelZigZagTraversal(Node *p)
{
    stack<Node*> ms;
    stack<Node*> cs;
    ms.push(p);
    int level=1;
    while(ms.size()!=0)
    {
        p=ms.top();
        ms.pop();
        cout<<p->data<<" ";
      /********* VERY IMP STEP -- USING THE LEVEL FLAG******* */
        if(level%2==0)
        {
            int s=p->children.size();
            for(int i=s-1;i>=0;i--)
            {
                cs.push(p->children[i]);
            }
        }
        else
        {
            for(int i=0;i<p->children.size();i++)
                    {
                        cs.push(p->children[i]);
                    }
        }
        if(ms.size()==0)
        {
            cout<<"\n";
            level++;
            stack<Node*> ts;
            ts=cs;
            cs=ms;
            ms=ts;
        }
    }
}
// MIRROR KRDO GENERIC TREE KO!!
// POST ORDER EULER MEIN REVERSE KRO
// HIGH LEVEL THINKING -- NICHE WALE CHILDREN MIRROR HOGYE!!
// THIS IS THE FAITH !!
void mirror(Node *p)
{
    for(auto child:p->children)
    {
        mirror(child);
    }
    if(p->children.size()>1)
    reverse(p->children.begin(),p->children.end());
}
/* **V-IMP** ::: array/vector pe delete krna hai to last se traverse krna shuru kro */
// Recursive Approach :: children ka size check krna hoga!!
// remove Function vector pe ni chlta !!
// Use Erase Function instead!!
/* Just make an iterator like --  vector<Node*>::iterator it;
  and do it = vector.begin()+(index to remove)
 and do vector.erase(it)
 */
void removeLeafNodes(Node *p)
{
    for(int i=(p->children.size()-1);i>=0;i--)
    {
        Node *t=p->children[i];

        if(t->children.size()==0)
        {
            vector<Node*>::iterator it;
            it=p->children.begin()+i;
            p->children.erase(it);
        }
                
    }
    for(auto child:p->children)
        removeLeafNodes(child);
}
/* IS FUNCTION SE HM TAIL NIKALTE HAI !!
  ---> JB TK SIZE 1 HAI TB TK NICHE JAATE RHO TAIL MIL JAEGI
 */
Node* tail(Node *t)
{
    while(t->children.size()==1)
    {
        t=t->children[0];
    }
    return t;
}
/*
 LINEARIZE-1
APPROACH ::
 1.LAST CHILD(lc) NIKALA USE REMOVE KRDIA!
 2.SECOND LAST CHILD(slc) NIKALA
 3.FIR SLC KI TAIL(tslc) NIKALI tail FUNCTION SE
 4.FIR US TAIL(tslc) KE CHILDREN MEIN lc ko add krdo!!!!
 lc  --  Last cildren
 slc -- Second Last children
 tslc -- tail of second last children
 ~~~~~~~~~~~~~~~~~TIME COMPLEXITY : O(n2)~~~~~~~~~~~~~~~~~~~~~
 */
void Linearize(Node *p)
{
    for(auto child:p->children)
        Linearize(child);
    while(p->children.size()>1)
    {
        Node *lc=p->children[p->children.size()-1];
        vector<Node*>::iterator it;
        it=p->children.begin()+(p->children.size()-1);
        p->children.erase(it);
        Node *slc=p->children[p->children.size()-1];
        Node *tslc=tail(slc);
        tslc->children.push_back(lc);
    }
}
/*
 LINEARIZE-2
APPROACH --> tail FUNCTION WALA KAAM BHI LINEARIZE FUNCTION SE HI KRA LIYA!!!
 ********HR NODE KI JAKR KEY TAIL NIKAL LI *********
 slkt-- Second Last key tail..
 lkt --  Last key tail...
 lc  --  Last cildren
 slc -- Second Last children
 lkt ko return kr rhe hai !!!!!
 Pr display level order traversal se hi kr rhe hai!!!
 ~~~~~~~~~~~~~~~~~TIME COMPLEXITY : O(n)~~~~~~~~~~~~~~~~~~~~~~
 */
Node* Linearize2(Node *p)
{
    if(p->children.size()==0)
        return p;
Node *lkt=Linearize2(p->children[p->children.size()-1]);
    while(p->children.size()>1)
    {
        Node *lc=p->children[p->children.size()-1];
        vector<Node*>::iterator it;
        it=p->children.begin()+(p->children.size()-1);
        p->children.erase(it);
        Node *slc=p->children[p->children.size()-1];
        Node *slkt=Linearize2(slc);
        slkt->children.push_back(lc);
    }
    return lkt;
}
/*
 ADHA EULER CHLTA HAI IS SAWAL MEIN !!
 Jse hi data match hogya return true krdo.....
 */
bool find(Node *p,int data)
{
    if(p->data==data)
        return true;
    for(auto child:p->children)
    {
        if(find(child,data)==true)
            return true;
    }
    return false;
}
/*
ADHA EULER CHLTA HAI IS SAWAL MEIN !!
ptc-Path till child
Jse hi data match hogya vector mein data push kro or return mardo list ko!
 ~~~~Agr data akhiri tk ni mila to khaali list return krdo~~~~
*/
vector<Node*> nodeToRootPath(Node *p,int data)
{
    vector<Node*> List;
    if(p->data==data)
    {
        vector<Node*> res;
        res.push_back(p);
        return res;
    }
    for(auto child:p->children)
    {
        vector<Node*> ptc = nodeToRootPath(child, data);
        if(ptc.size()>0)
        {
            ptc.push_back(p);
            return ptc;
        }
            
    }
    return List;
}
/*
 STEP1-Node to root path bnalia dono data's ki value ke liye!!!
 STEP2-fir i,j ko vector's ke last index pe le gye
 STEP3-fir , check kia jb tk path1[i]==path[j] --> i--;j--
 STEP4-fir index ek se bdhakr element ka data return krdo!!
 */
int lowestCommonAncestor(Node *t,int data1,int data2)
{
    vector<Node*> path1=nodeToRootPath(t, data1);
    vector<Node*> path2=nodeToRootPath(t, data2);
    int i,j;
    i=path1.size()-1;
    j=path2.size()-1;
   while(i>=0&&j>=0&&path1[i]==path2[j])
   {
       i--;
       j--;
   }
    i++;
    j++;
    return path1[i]->data;
}
/*
 STEP1-Node to root path bnalia dono data's ki value ke liye!!!
 STEP2-fir i,j ko vector's ke last index pe le gye
 STEP3-fir , check kia jb tk path1[i]==path[j] --> i--;j--
 STEP4-fir index ek se bdhakr (i+j) return krdo!!
 */
int distanceBetweenNodes(Node *t,int data1,int data2)
{
    vector<Node*> path1 = nodeToRootPath(t, data1);
    vector<Node*> path2 = nodeToRootPath(t,data2);
    int i=path1.size()-1;
    int j=path2.size()-1;
    while(i>=0&&j>=0&&path1[i]==path2[j])
    {
        i--;
        j--;
    }
    i++;
    j++;
    return i+j;
}
/*
APPROACH :  KYA TREE APNE HI SATH MIRROR HAI ..
 */
bool isSymmetric(Node *p)
{
    for(int i=0;i<p->children.size();i++)
    {
        int j=p->children.size()-i-1;
        Node *c1=p->children[i];
        Node *c2=p->children[j];
        if(c1->children.size()!=c2->children.size())
            return false;
        if(isSymmetric(c1)==false)
            return false;
   }
    return true;
}
static int ht=0;
   static int mini=INT_MAX;
   static int maxi=INT_MIN;
   static int sz=0;
// TRAVERAL AND CHANGE STRATEGY!!!!
void multiSolver(Node *p,int depth)
{
    sz=sz+1;
    maxi=max(maxi,p->data);
    mini=min(mini,p->data);
    ht=max(ht,depth);
    for(auto child:p->children)
        multiSolver(child, depth+1);
}
static Node* predecessor;
static Node* successor;
static int state=0;
/* TRAVERAL AND CHANGE STRATEGY!!!!
 APPROACH :
 1.Initially state ko 0 rkha , agr data node ke data se match krjata hai to state ko 1 krdo nhi to predecessor ko change krte jao.
 2.State 1 hone ka mtlb hai ki hm just abhi element ke paas se aaye hai mtlb hm successor pe khde hai , bs fir yahan state ko 2 krdo or is current node ko successor bna do!
   */
void predecessorAndSuccessor(Node *p,int data)
{
    if(state==0)
    {
        if(p->data==data)
            state=1;
        else
        {
            predecessor=p;
        }
    }
    else if(state==1)
    {
        successor=p;
        state=2;
    }
    for(auto child:p->children)
    {
        predecessorAndSuccessor(child, data);
    }
}
/* TRAVERAL AND CHANGE STRATEGY!!!!
 ~~~~~---> ceil : Smallest values amongst the larger values than a particular element <-----~~~~~
  ~~~~~---> floor : Largest values amongst the smaller values than a particular element <-----~~~~~
 */
static int ceil = INT_MAX;
static int floor = INT_MIN;
void ceilAndFloor(Node *p,int data)
{
    if(p->data>data)
    {
        ceil=min(ceil,p->data);
    }
    else if(p->data<data)
    {
        floor=max(floor,p->data);
    }
    for(Node* child:p->children)
    {
        ceilAndFloor(child,data);
    }
}
/* TRAVERAL AND CHANGE STRATEGY!!!!
~~~~~---> ceil : Smallest values amongst the larger values than a particular element <-----~~~~~
 ~~~~~---> floor : Largest values amongst the smaller values than a particular element <-----~~~~~
 
 ******Intuition : Infinity ka floor dega maximum node in the generic tree , then it's floor will give second maximum node and this process goes on..........******
*/
int kLargestElement(Node *p,int k)
{
    int factor=INT_MAX;
    for(int i=0;i<k;i++)
    {
        ceilAndFloor(p,factor);
        factor=floor;
        floor=INT_MIN;
    }
    return factor;
}
static int max_Sum=INT_MIN;
/*
 Recursion lgate hue faith establish kro pehle to :
 ki sbki children apne apne subtree mein maximum subtree ka sum dedenge....
 fir bs root ko add krke check krlo kya maximum sum se zyda hai kya???
 Aur agr hai to max_Sum mein vo cms(current maximum sum) daldo!!!!!
 ~~IS SAWAL MEIN JO RETURN KRA RHE HAI USE PRINT NI KRVA RHE~~
 */
int maxSubTree(Node *p)
{
    int cms=0;
    for(auto child:p->children)
        cms+=maxSubTree(child);
    cms+=p->data;
    if(cms>max_Sum)
        max_Sum=cms;
    return cms;
}
static int dia=0;
/* ***********************V-IMP*******************************
 ~~~~~~~~~~~~~~~~~DIAMETER : Maximum number of edges between any two nodes in a tree!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Wrong Approach :: lch+slch+2
                   lch - largest child height
                   slch - second largest child height
 WHY?? -- Kyuki ek hi node ke andr bhi mil skte hai hai zaruri nii hai root node ke andr wale hi ho!
 Right Approach :: dch+sdch+2
                dch - deepest child height
                sdch - second deepest child height
                ch  - child height
                dia - diameter
*************************V-IMP********************************
 */
int calculateDia(Node *p)
{
    int dch=-1;
    int sdch=-1;
    for(auto child:p->children)
    {
        int ch=calculateDia(child);
        if(ch>dch)
        {
            sdch=dch;
            dch=ch;
       }
        else if(ch>sdch)
        {
            sdch=ch;
        }
    }
    if(sdch+dch+2>dia)
        dia=dch+sdch+2;
    dch+=1;
    return dch;
}
class traversal_pair
{
    public:
    Node *node;
    int state;
};
/* **********************VIMP*********************************
 ~~~~~~~~~~~~~~~~~~~~INTUITION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 PAIR CLASS BNADI JISME NODE OR STATE PASS KRDI
 CONDITIONS:
 1. if state == -1
    -> Push in preorder string
    -> state++
 2. if state>=0 && state<st.top().node->children.size()
    ->state++
    ->Push children [state-1] wala
 3. if state == st.top().node->children.size()
    -> push in postorder string
    -> pop from the stack
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Int to string : use to_string() function
 *************************************************************
 */
void IterativePreAndPost(Node *p)
{
    string preOrder="";
    string postOrder="";
    stack<traversal_pair> st;
    traversal_pair pair;
    pair.node=p;
    pair.state=-1;
    st.push(pair);
    while(st.size()!=0)
    {
        if(st.top().state==-1)
        {
            preOrder+=to_string(st.top().node->data)+" ";
            st.top().state++;
        }
        else if(st.top().state>=0&&st.top().state<st.top().node->children.size())
        {
            st.top().state++;
            traversal_pair temp_pair;
    temp_pair.node=st.top().node->children[st.top().state-1];
            temp_pair.state=-1;
            st.push(temp_pair);
        }
        else if(st.top().state==st.top().node->children.size())
        {
            postOrder+=to_string(st.top().node->data)+" ";
            st.pop();
        }
    }
    cout<<"\nPREORDER TRAVERSAL OF THE GENERIC TREE:";
    cout<<preOrder;
    cout<<"\nPOSTORDER TRAVERSAL OF THE GENERIC TREE:";
    cout<<postOrder;
}
int main() {
    // insert code here...
    Node *root = nullptr;
int arr[]={10,20,50,-1,60,-1,-1,30,70,-1,80,110,-1,120,-1,-1,90,-1,-1,40,100,-1,-1,-1};
    stack<Node*> st;
    for(auto i:arr) // Ye sidha Element pick krta hai rather tha index!!
    {
        if(i==-1)
            st.pop();
        else{
            Node *t=new Node();
            t->data=i;
            if(st.size()==0)
            {
                root=t;
                st.push(t);
            }
         else
            {
                st.top()->children.push_back(t);
                st.push(t);
            }
        }
    }
    //Display(root);
    int x=size(root);
    cout<<"Size of the generic tree:"<<x<<"\n";
    int y=maximum(root);
    cout<<"Maximum of the generic tree:"<<y<<"\n";
    int z=height(root);
    cout<<"Height of the generic tree:"<<z<<"\n";
   // Traversal(root);
    cout<<"LEVEL ORDER TRAVERSAL::\n";
    levelTraversal(root);
    /*cout<<"\n LEVEL ORDER LINE WISE TRAVERSAL::\n";
      levelLineWiseTraversal4(root);*/
    /*cout<<"\n LEVEL ORDER ZIG ZAG TRAVERSAL::\n";
      levelZigZagTraversal(root);*/
    /*cout<<"\n MIRROR OF THE GENERIC TREE:";
      mirror(root);
     levelTraversal(root);*/
    /*cout<<"\n REMOVE LEAF NODES:";
    removeLeafNodes(root);
    cout<<"\n";
    levelTraversal(root); */
    /*cout<<"\n LINEARIZE THE GENERIC TREE:";
    Linearize2(root);
    cout<<"\n";
       levelTraversal(root);*/
   /* cout<<"\nFIND A PARTICULAR ELEMENT IN THRE GENERIC TREE:";
    cout<<find(root,40);*/
    /*cout<<"\n NODE TO ROOT PATH OF A PARTICULAR ELEMENT:";
    vector<Node*> t=nodeToRootPath(root,110);
    for(int i=0;i<t.size();i++)
    {
        cout<<t[i]->data<<" ";
    }*/
    /*cout<<"LOWEST COMMON ANCESTOR::";
   cout<<lowestCommonAncestor(root,80,110);*/
    /*cout<<"DISTANCE BETWEEN NODES::";
    cout<<distanceBetweenNodes(root,90,120);*/
    /*cout<<"CHECKING SYMMETRY OF GENERIC TREE::";
    cout<<isSymmetric(root);*/
     /*   multiSolver(root,0);
    cout<<"\nSIZE OF THE GENERIC TREE:";
    cout<<sz;
    cout<<"\nMINIMUM ELEMENT OF THE GENERIC TREE:";
    cout<<mini;
    cout<<"\nMAXIMUM ELEMENT OF THE GENERIC TREE:";
    cout<<maxi;
    cout<<"\nHEIGHT OF THE GENERIC TREE:";
    cout<<ht;*/
    /*cout<<"PREDECESSOR AND SUCCESSOR OF A PARTICULAR ELEMENT:";
    predecessorAndSuccessor(root,80);
    cout<<predecessor->data<<" "<<successor->data;*/
    /*ceilAndFloor(root,120);
    cout<<"CEIL"<<ceil<<" FLOOR:"<<floor;*/
    /*cout<<"Kth LARGEST ELEMENT IN THE GENERIC TREE:";
    cout<<kLargestElement(root,5);*/
    cout<<"\nSUM OF MAXIMUM SUBTREE IN THE GENERIC TREE:";
    maxSubTree(root);
    cout<<max_Sum;
    cout<<"\n Diameter of the generic tree:";
    calculateDia(root);
    cout<<dia;
    cout<<"\n PREORDER AND POSTORDER TRAVERSALS OF THE GENERIC TREE->";
    IterativePreAndPost(root);
    return 0;
}
