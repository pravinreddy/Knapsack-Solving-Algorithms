#include <iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include <math.h>
using namespace std;


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

	
	
    int b[n+1][k+1];							//creating a matrix of rows = items and column = capacity

    
    for(int i=0;i<=k;i++){						//making 1st row to zeros
        b[0][i]=0;
    }
    
    for(int i=1; i<=n;i++){
        b[i][0]=0;
        
        for(int j=1;j<=k;j++){
            if((w[i-1]<=j) && ((b[i-1][j-w[i-1]]+p[i-1])> b[i-1][j])){		//check the previous values are less if less update the values
                b[i][j] = b[i-1][j-w[i-1]] + p[i-1];
            }
            else{
                b[i][j] = b[i-1][j];
            }
        }
    }
    
/**
* traversing the array to find the items that are included in the knapsack
*/
    int item = n;
    int cap = k;
    while(cap>0){
        if(b[item][cap] == b[item-1][cap]){
            item = item-1;
        }else{
            a[item-1]=1;
            item = item -1;
            cap = cap - w[item];
        }
    }
 
	
/**
* printing the result
*/  
    cout<<"item taken in the Knapsack are :";
    
    int totalprofit = 0;
    int totalweight = 0;
    
	
    for(int i=0;i<n;i++){
        if(a[i]==1){
            cout<<"item"<<i+1<<", ";
            totalprofit = totalprofit +p[i];
            totalweight = totalweight +w[i];
        }
    }
    
    cout<<endl<<"total weight = "<<totalweight<<endl<<"Total profit = "<<totalprofit<<endl;

    return 0;
}

