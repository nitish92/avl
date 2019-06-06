#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>
#include "Tree.h"
using namespace std;

void delete_everything(Node* root)
{
  if (root != NULL)
  {
    delete_everything(root->left);
    delete_everything(root->right);
    delete root;
  }
}

vector<int> int_vector(string array) // string array to int vector
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

Node* insert_master(Node* root, vector<int> int_vec)
{
    int rotations = 0;
    float N = int_vec.size();
    int visits = 0;
    int dummyvar;
    float n=0;
    for (int i = 0; i < N; i++) 
    {  
        if (lookup(root, int_vec[i], &dummyvar) != int_vec[i])
        {
          n +=1;
        }
        root = insert(root, int_vec[i], &rotations, &visits);
    }

    // Added 2 of 2 nodes.
    cout << "Added " << n << " of " << N << " nodes." << endl;
    // Visited 1 (0.5) nodes and performed 0 (0) rotations.
    cout << "Visited " << visits << " (" << visits/N << ") nodes and performed " << rotations << " (" << rotations/N << ") rotations.\n" << endl;


    return root;
}

void lookup_master(Node* root, vector<int> lookup_vec)
{
  int visits = 0;
  vector<int> found_vec;
  float N = lookup_vec.size();

  for (int i=0; i<N; i++)
  {
    int found = lookup(root, lookup_vec[i], &visits);
    if(lookup_vec[i] == found)
      found_vec.push_back(found);
  }

  // Found 3 of 5 nodes: [7, 12, 7]
  // Visited 10 (2) nodes and performed 0 (0) rotations.

  int n = found_vec.size();
  cout << "Found " << n << " of " << N << " nodes: [";

  for (int i=0; i<n; i++)
  {
    cout << found_vec[i];
    if(i<n-1)
      cout << ", ";
  }
  cout << "]\nVisited " << visits << " (" << visits/N << ") nodes and performed 0 (0) rotations.\n";
}


int main(int argc, char* argv[])
{
	// /root/avl-master/tests.left-left.avl
	if (argc > 1)
	{
		string line;
		ifstream inFile;
		inFile.open( argv[1] ); // note no mode needed 
    Node *root = NULL;
		if (!inFile)
		{
			cout<<"unable to open file";
		}
		while(getline(inFile, line))
		{
			if(line.length() > 6)
			{
				//cout << (line.substr(0,6)) << endl;
				string function_name = line.substr(0,6);
				if (function_name.compare("insert") == 0)
				{
					string array = line.substr(7, line.length());
          vector<int> int_vec = int_vector(array);
					root = insert_master(root, int_vec);
				}
        if (line.compare("print tree") == 0)
        {
          int c = 0;
          printTree(root, &c);
          cout << endl;
        }
        if (function_name.compare("lookup") == 0)
        {
          string array = line.substr(7, line.length());
          vector<int> lookup_vec = int_vector(array);
          lookup_master(root, lookup_vec);
          cout << endl;
        }
			}
		}

    delete_everything(root);

	}
	return 0;


}