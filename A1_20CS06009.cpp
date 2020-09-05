#include <iostream>

#include<bits/stdc++.h> 
using namespace std;
void print_dfa_table(vector<vector<int> > &dfa ,int &alphabet,int &dfa_states)
{
    cout<<"\nstate_no "<<" 0"<<"\t1\tfinal_state\n";
    for(int i=0;i<dfa_states;i++)                    // print dfa
    {
        if(dfa[i][2]!=-1)
        {
            cout<<"Q"<<dfa[i][2]<<"\t  ";
            for(int j=0;j<alphabet;j++)
            {
                int t1=dfa[i][j];
                cout<<"Q"<<dfa[t1][2]<<"\t";
            }
            cout<<"   "<<dfa[i][3];
            cout<<endl;
        }
    }
}
int main() {
    int n,start_state;                                      //no of states
    cin>>n;
    cin>>start_state;                                           //start state input
    int no_final_states;
    cin>>no_final_states;                                       
    int final_states=0 ,t ;
    for(int i=0; i < no_final_states ; i++)
    {
        cin>>t;
        final_states|=1<<t;
    }
    //cout<<"final_states "<<final_states<<endl;
    int alphabet;
    cin>>alphabet;
    vector< vector<int> > nfa (n ,vector<int>(alphabet,-1)) ;          // intialize 2d vector for 2 alphabet and n
 
    int temp,s;
    for(int j=0;j<alphabet;j++)
    {
        for(int i=0;i<n;i++)
        {
          cin>>s;
          nfa[i][j]=0;
          while(s)
          {
              cin>>temp;
              nfa[i][j]=nfa[i][j] | 1<<temp;
              s--;
          }
        }
    }
    // for(int i=0;i<n;i++)                   				 // print nfa
    // {
    //     for(int j=0;j<alphabet;j++)
    //         cout<<nfa[i][j]<<" ";
    //     cout<<endl;
    // }
    std::queue<int> q ;
    std::map<int, int>m ;
    q.push(1<<start_state);
    
    m[1]++;
    int dfa_states=pow(2,n);
    vector< vector<int> > dfa ( dfa_states ,vector<int>(alphabet+2,-1)) ;
    int j=0;
    dfa[1<<start_state][2]=0;
    while(!q.empty())
    {
        int t1=q.front(),t2;
        t2=t1;
        q.pop();
        int i=0,a=0,b=0;
        while(t1)
        {
            if(t1 & 1<<i)
            {
                a = a | nfa[i][0];
                b = b | nfa[i][1];
            }
            t1= t1 & ~(1 << (i ));              				//turnoff i th bit
            i++;
        }
        dfa[t2][0]=a;
        dfa[t2][1]=b;
        if( t2 & final_states)                 				 //set final states
            dfa[t2][3]=1;
        if(m.find(a)== m.end())
        {
             q.push(a);
             m[a]++;
             dfa[a][2]=++j;
        }
        if(m.find(b) == m.end())
        {
             q.push(b);  
             m[b]++;
             dfa[b][2]=++j;
        }
        
    }

    cout<<"\n\n";
    for(int i=0;i<dfa_states;i++)                    // print states
    {
        if(dfa[i][2]!=-1)
        {
            cout<<"Q"<<dfa[i][2]<<" = {";
            int k=0;
            int t1=i;
            while(t1)
            {
                if(t1 & 1<<k)
                    cout<<"q"<<k<<",";
                t1= t1 & ~(1 << (k ));              //turnoff k th bit
                k++;
            }
            cout<<" }\n";
        }
    }
    print_dfa_table(dfa,alphabet,dfa_states);
    cout<<"\n\n";
    cin>>t;                                        				 //no of strings
    int next_state;
    string str;
    while(t--)
    {
        cin>>str;                                       			//input string
        next_state=dfa[1<<start_state][str[0]-'0'];
        for(int i=1;i<str.length();i++)
        {
            next_state=dfa[next_state][str[i]-'0'];
        }
        if(dfa[next_state][3]==1)
            cout<<str<<" ACCEPTED\n";
        else
            cout<<str<<" REJECTED\n";
    }
}

/* 
Input 1 :

4
0
1
3
2
1 0 1 2 0 1 3
3 0 1 2 1 3 1 3 1 3
5
010111
010101
11111111
0000010
0100

OUTPUT 1 :
Q0 = {q0, }
Q2 = {q0,q2, }
Q1 = {q0,q1,q2, }
Q5 = {q0,q3, }
Q4 = {q0,q2,q3, }
Q3 = {q0,q1,q2,q3, }

state_no  0	1	final_state
Q0	  Q0	Q1	   -1
Q2	  Q0	Q3	   -1
Q1	  Q2	Q3	   -1
Q5	  Q5	Q3	   1
Q4	  Q5	Q3	   1
Q3	  Q4	Q3	   1


010111 ACCEPTED
010101 ACCEPTED
11111111 ACCEPTED
0000010 REJECTED
0100 REJECTED


Input 2 :

5
0
1
4
2
5 0 1 2 3 4 1 2 0 1 4 0 
2 3 4 1 4 1 1 0 0
5
010111
010101
11111111
0000010
0100

output 2:

Q5 = { }
Q0 = {q0, }
Q7 = {q1, }
Q8 = {q2, }
Q4 = {q4, }
Q6 = {q2,q4, }
Q2 = {q3,q4, }
Q3 = {q1,q3,q4, }
Q1 = {q0,q1,q2,q3,q4, }

state_no  0	1	final_state
Q5	  Q5	Q5	   -1
Q0	  Q1	Q2	   -1
Q7	  Q8	Q4	   -1
Q8	  Q5	Q7	   -1
Q4	  Q5	Q5	   1
Q6	  Q5	Q7	   1
Q2	  Q4	Q5	   1
Q3	  Q6	Q4	   1
Q1	  Q1	Q3	   1


010111   REJECTED
010101   REJECTED
11111111  REJECTED
0000010    ACCEPTED
0100     REJECTED */

