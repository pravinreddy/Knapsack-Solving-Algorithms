#include <iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include <math.h>
using namespace std;

static int max_weight;
static int max_profit;


/**
 * This function return the array of items to take
 * we give 2 input parameters decimal value and number of items
*/
void sets(int n, int k, int a[]){
    int x=0;
    int z=k;
    int y=1;
    while(k!=0){
        a[x]=n%2;
        n=n/2;
        x++;
        k--;
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

  while (getline (ss, token, ','))
    {
      line[i] = token;
	  p[i]=atoi(line[i].c_str());
      i++;
    }

}


int main(int argc, char *argv[])
{

	int n;
    int k;
	string s = argv[1];
	ifstream myfile (s.c_str ());
	string str;
	getline (myfile, str);						//getting the number of items
	n = atoi(str.c_str());
	getline (myfile, str);						//getting the knapsack capacity
	k = atoi(str.c_str());
	int w[n];
    int p[n];
    int a[n];
	int items_taken[n];
	getline (myfile, str);						//parsing the profits into array
	parse(str, p, n);
	getline (myfile, str);						//parssing the weights into array
	parse(str, w, n);
	myfile.close ();
	for(int i=0;i<n;i++){
		a[i]=0;
		items_taken[i]=0;
	}
    

    
    for(int i=0; i<pow(2,n);i++){
		
        sets(i,n,a);						//creats the sets in the a array
		
        int temp_weight=0;
        int temp_profit=0;
        
        for(int i=0; i<n ;i++){
            temp_weight += w[i]*a[i];
            temp_profit += p[i]*a[i];
        }
        
        //to check weathe the present profit is geter than than the previous weight and update
        if(temp_profit >= max_profit){
            if(temp_weight <= k){
                max_profit = temp_profit;
                max_weight = temp_weight;
                for(int i=0; i<n; i++){
                    items_taken[i] = a[i];
                }
            }
        }
        
    }
    
    cout<<"Item taken in the Knapsack are :";
    
    for(int i=0;i<n;i++){
        if(items_taken[i]==1){
            cout<<"item"<<i+1<<", ";
        }
    }

    cout<<endl<<"total weight = "<<max_weight<<endl<<"Total profit = "<<max_profit<<endl;
    
}