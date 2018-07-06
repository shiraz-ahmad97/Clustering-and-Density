//Fahad Sultan Abbas 2016118
//Syed Shiraz Ahmed 2016492
//Ali Aqeel Zafar 2016061
//Hamza Qureshi 2016149
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int maxv = 6500 ;
double graph[maxv][maxv];
double graph2[maxv][maxv];
int arr2[maxv];
int Number_of_Vertices = 0;
double density = 0.01437;

struct degreei{									//structure to store degree
        int index;
        int de;
};

struct won{										//structure to store weight of node
        int index;
        int weight;
};
struct won n[maxv];
struct won k[maxv];
//struct degreei d[maxv];
void initialize()
{
    int i, j;
    for(i=0; i<maxv; i++)
    {
            for(j=0; j<maxv;j++)
        {
                graph[i][j]=0;
                }
        }
}
void read()									//funtion to read the file and store the data in a 2d matrix
{
    ifstream inf;
    int V1, V2; 
    int a=1;
    int b=0;
    inf.open("Villain.txt");
    double X;        
    while(!inf.eof())
    {
        inf >> V1;
                inf >> V2;
                inf >> X;
                cout<<"o is "<<V1<<","<<V2<<","<<X<<endl;
                graph[V1][V2]=1;
                graph[V2][V1]=1;
                
        if (Number_of_Vertices < max(V1, V2))
        {
            Number_of_Vertices = max(V1, V2);
        }
    }
    inf.close();
   // system("pause");
    
}

void print()                                    //print the 2d matrix
{
    int i, j;
    for(i=0; i< Number_of_Vertices; i++)
    {
        for(j=0; j< Number_of_Vertices; j++)
        {
                cout<<graph[i][j]<<"";
                }
                cout<<endl;                
    }
}

void multi()										//function to square the adjacency matrix
{
        int sum;
        for(int i=0; i<Number_of_Vertices; i++)
        {
                for(int j=0; j<Number_of_Vertices; j++)
                {
                        sum=0;
                        for(int k=0; k<Number_of_Vertices; k++)
                        {
                                sum = sum + graph[i][k] * graph[k][j];
                        }
                        graph2[i][j] = sum;
                }
        }
        /*cout<<"\nMultiplication of two Matrices : \n";
        for(int i=0; i<Number_of_Vertices; i++)
        {
                for(int j=0; j<Number_of_Vertices; j++)
                {
                        cout<<graph2[i][j]<<" ";
                }
                cout<<"\n";
        }*/
}


void sortingofnode(struct won d[])						//funtion to sort each node
{
       for(int i=0 ; i < Number_of_Vertices;i++)
        {
                
                for(int j=0 ; j<(Number_of_Vertices - i - 1) ; j++)
                {
                        int tempa;
                        int tempb;
                        
                        if(d[j].weight < d[j+1].weight)
                        {
                                    int tempa = d[j].weight;
                                    int tempb = d[j].index;
                                    d[j].weight = d[j+1].weight;
                                    d[j].index = d[j+1].index;
                                    
                                    d[j+1].weight = tempa;
                                    d[j+1].index = tempb;
                                    
                                
                        }
                }
        }
        cout<<"After sorting: "<<endl;
        for(int i=0 ; i<Number_of_Vertices ; i++)
        {
                cout<<d[i].index<<" "<<d[i].weight<<endl;
        }
        
}

void degree_of_nodes()						//funtion to sort the degree of nodes
{
	
        int sum=0;
        int a=0;
        int deg[maxv];
        for(int j=0 ; j<Number_of_Vertices ; j++)
        {
                for(int i=0 ; i<Number_of_Vertices ; i++)
                {
                        sum= sum + graph[j][i];
                }
                n[j].weight= sum;
                n[j].index = j;
                sum=0;
        }
        
        for(int q=0 ; q<Number_of_Vertices ; q++)
        {
                cout<<n[q].index<<" "<<n[q].weight<<endl;
        }
        
       sortingofnode(n);
}


void weightofnode()							//function to calculate the sum of node
{
        
        int sum1;
        for(int i=0 ; i<Number_of_Vertices ; i++)
        {
                for(int j=0; j<Number_of_Vertices ; j++)
                {
                    if(graph2[i][j]!=0)
                    {
                               sum1 = sum1 + graph2[i][j];        
                        }
                }
                k[i].weight = sum1;
                k[i].index = i;
                sum1=0;
        }
       for(int i=0 ; i<Number_of_Vertices ; i++)
        {
                cout<<"weight of node "<<k[i].index<<": "<<k[i].weight<<endl;
        }
        sortingofnode(k);
}


bool weight_check()									//funtion to check if the array of weight of nodes is empty or not
{
  for (int i = 0 ; i < Number_of_Vertices ; i++)
  {
      if(arr2[i] != 0)
      {
        return false;
      }
  }
  return true;
}


void sorting(struct degreei d[])					//function to sort degree of nodes
{
		cout<<"Before sorting: "<<endl;
        for(int i=0 ; i<Number_of_Vertices ; i++)
        {
                cout<<d[i].index<<" "<<d[i].de<<endl;
        }
        for(int i=0 ; i < Number_of_Vertices;i++)
        {
                
                for(int j=0 ; j<(Number_of_Vertices - i - 1) ; j++)
                {
                        int tempa;
                        int tempb;
                        
                        if(d[j].de < d[j+1].de)
                        {
                                    int tempa = d[j].de;
                                    int tempb = d[j].index;
                                    d[j].de = d[j+1].de;
                                    d[j].index = d[j+1].index;
                                    
                                    d[j+1].de = tempa;
                                    d[j+1].index = tempb;
                                    
                                
                        }
                }
        }
        cout<<"After sorting: "<<endl;
        for(int i=0 ; i<Number_of_Vertices ; i++)
        {
                cout<<d[i].index<<" "<<d[i].de<<endl;
        }
        
}

void clustering()											//function to add clusters node by node
{
        int sum;
        degreei d[Number_of_Vertices];
        int temp[Number_of_Vertices];
        int cus[Number_of_Vertices];
        ofstream file;
        file.open("cluster.txt");
        cout<<endl;
        for(int i=0 ; i<Number_of_Vertices ; i++)
        {
                int a=k[i].index;
                cus[i] = a;
                file<<a<<endl;
                for(int x=0 ; x<Number_of_Vertices ; x++)
                {
                        if(graph[a][x] == 1)
                        {
                                for(int y=0 ; y<Number_of_Vertices ; y++)
                                {                      
                                    sum = sum + graph[x][y];
                                }        
                                
                        }
                        d[x].de = sum;
                        d[x].index = x;
                        sum = 0;
					 
					 sorting(d);
                     cus[x] = d[x].index;
                     file<<cus[x]<<",,,"<<endl;
                     d[x].index = NULL;
                     d[x].de = NULL;
                        //put in cluster here!!
                }
             
        }
        
}

int main()
{
    int V1;
    int V2;
    won d[Number_of_Vertices];
    initialize();
    read();
    print();
    multi();
   	weightofnode();
   	cout<<endl;
   	clustering();
    
}
