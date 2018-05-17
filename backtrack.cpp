#include <iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include <math.h>

using namespace std;

int bestvalue=0;							//to store the best weight and profit
int bestweight=0;

typedef struct Node{
    int depth;                              //to store the depth of the node
    int weight;                             //total profit until that node
    int profit;                             //total profit until that node
    int side;
    struct Node *root;
    struct Node *left;                      //to store the left sub tree
    struct Node *right;                     //to store the right sub tree
}Node;

Node *node;                                 //creating a node structure variable
struct Node *rn;

/**
* tree() function builds the for the given weights and profits
*/
struct Node *tree(int n, int k, int w[], int p[], int depth, int wprev, int pprev, int side,struct Node *parent){
    struct Node *nd;
    //checking the promising condition wether adding the next node is less than the capacity of the kanpsack
    if(depth>n || (wprev > k)){
        nd = NULL;
    }else{
        nd = (Node*) malloc(sizeof(Node));
        nd->weight = wprev;
        nd->profit = pprev;
        nd->depth = depth;
        nd->side = side;
        nd->left = tree(n, k, w, p, depth+1, wprev + w[depth], pprev + p[depth],1,nd);
        nd->right = tree(n, k, w, p, depth+1, wprev, pprev,0,nd);
        nd->root = parent;
    }
    return nd;
}

/**
* checknode() function checks all the node with their weights and profits and gets the best profit and weight
*/
void checknode(struct Node *nd){
    if(nd->profit > bestvalue){
        bestvalue = nd->profit;
        bestweight = nd->weight;
        rn = nd;
    }
    
    if(nd->left != NULL){
        checknode(nd->left);
    }
    if(nd->right != NULL){
        checknode(nd->right);
    }
    
}


/**
* This function is to backtracking to the root node from the highest profit node and includes the items that are include
*/
void include(struct Node *nd, int a[]){
    if(nd->root != NULL){
        if(nd->side==1){
            a[nd->depth-1] = 1; 
        }
        
        include(nd->root, a);
    }
    
    if(nd->root == NULL)
    {
        return;
    }
    

}
    

/**
* parse the line and insert into array
*/
void parse (string s, int p[], int l)
{
  stringstream ss (s);
  string line[l];
  string token;
  int i = 0;

  while (getline (ss, token, ','))					//seperating the items from string and converting to the integers
    {
      line[i] = token;
	  p[i]=atoi(line[i].c_str());
      i++;
    }

}

int main(int argc, char *argv[])
{
	string s = argv[1];
	int n;
    int k;
	ifstream myfile (s.c_str ());
	string str;
	getline (myfile, str);						//getting the number of items
	n = atoi(str.c_str());
	getline (myfile, str);						//getting the knapsack capacity
	k = atoi(str.c_str());
	int w[n];
    int p[n];
    int a[n];
	getline (myfile, str);						//parsing the profits into array
	parse(str, p, n);
	getline (myfile, str);						//parssing the weights into array
	parse(str, w, n);
	myfile.close ();
	for(int i=0;i<n;i++){
		a[i]=0;
	}
	
    node = tree( n, k, w, p, 0, 0, 0, 0, NULL);
    
    checknode(node);
    
    cout<<"Total Weight = "<<bestweight<<endl;
    cout<<"Total Profit = "<<bestvalue<<endl;
    
	
    include(rn,a);								//backtracks to root node from best node and store the into array a
    
    cout<<"item taken in the Knapsack are :";
    for(int i=0;i<n;i++){
        if(a[i]==1){
            cout<<"item"<<i+1<<", ";
        }
    }
	cout<<endl;

    return 0;
}



