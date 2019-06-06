#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "Tree.h"
using namespace std;

vector<int> string_to_int(string array) // string array to int vector
{
  stringstream ss;
  vector<int> arr;
  ss << array;
  string temp; 
  int found; 
  while (!ss.eof()) 
  { 
  
        /* extracting word by word from stream */
        ss >> temp; 
  
        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found) 
            arr.push_back(found);
  
        /* To save from space at the end of string */
        temp = ""; 
    }    
    return arr;
}

Node* main_insert(Node* root, vector<int> arr1)
{
    int rot = 0;
    double N = arr1.size();
    int visits = 0;
    int temp;
    double n=0;
    for (int i = 0; i < N; i++) 
    {  
        if (lookup(root, arr1[i], &temp) != arr1[i])
        {
          n +=1;
        }
        root = insert(root, arr1[i], &rot, &visits);
    }

    double amort_visits = visits/N;
    double amort_rot = rot/N;

    cout << "Added " << n << " of " << N << " nodes." << endl;
    cout << "Visited " << visits << " (" << amort_visits << ") nodes and performed " << rot << " (" << amort_rot << ") rotations." << endl;
    cout << endl;


    return root;
}

void main_lookup(Node* root, vector<int> lookup_vec)
{
  int visits = 0;
  vector<int> found_vec;
  double N = lookup_vec.size();

  for (int i=0; i<N; i++)
  {
    int found = lookup(root, lookup_vec[i], &visits);
    if(lookup_vec[i] == found)
      found_vec.push_back(found);
  }

  int n = found_vec.size();
  cout << "Found " << n << " of " << N << " nodes: [";

  for (int i=0; i<n; i++)
  {
    cout << found_vec[i];
    if(i<n-1)
      cout << ", ";
  }

  double amort_visits = visits/N;
  cout << "]\nVisited " << visits << " (" << amort_visits << ") nodes and performed 0 (0) rotations.";
  cout << endl;
}


int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		string line;
		ifstream inFile;
		inFile.open( argv[1] );
    Node *root = NULL;
		while(getline(inFile, line))
		{
			if(line.length() > 6)
			{
				if ((line.substr(0,6)).compare("insert") == 0)
				{
					string array = line.substr(7, line.length());
          vector<int> arr1 = string_to_int(array);
					root = main_insert(root, arr1);
				}
        if ((line.substr(0,6)).compare("lookup") == 0)
        {
          string array = line.substr(7, line.length());
          vector<int> lookup_vec = string_to_int(array);
          main_lookup(root, lookup_vec);
          cout << endl;
        }
        if (line.compare("print tree") == 0)
        {
          int count = 0;
          print_the_tree(root, &count);
          cout << endl;
        }
			}
		}

    delete_everything(root);

	}
	return 0;


}