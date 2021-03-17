#include "bst.h"
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

//Name: Default Constructor
//Pre-Condition: Root has not benn initalized and data has not been parced
//Post-Condition: Root has benn initalized and data has been parced
//Description: Initializes root and parces data from file so it can be inserted
bst::bst()
{
    root = NULL;
    string s1; //used to get the line from file
    string sub1, sub2;  //used to parce the string into county and population
    int firstSpace, secondSpace;
    int num;
    ifstream in;
    in.open("county_data.txt");
    if(in.fail())
    {
        cout << "File did not open" << endl;
        exit(1);
    }
    while(!in.eof())
    {
        getline(in, s1);
        //parse
        cout << s1 << endl;
        firstSpace = s1.rfind(' ', 0);
        secondSpace = s1.rfind(' ', firstSpace);
        sub1 = s1.substr(0, secondSpace);    //used to extract county
        sub2 = s1.substr(numLoc(s1));       //used to extract population
        num = stod(sub2);                    //makes population string into int
        insert(root, sub1, num);
    }
   
    in.close();
}

//Name: Destructor
//Pre-Condition: Memory for nodes have not ben de-allocated
//Post-Condition: Memory for nodes has ben de-allocated
//Description: De-allocates nodes
bst::~bst()
{
    cout << "Destructor called" << endl;
    while(root != NULL)
    {
        del_name(root -> county_name);
    }
}

//Name: numLock
//Pre-Condition: Memory for nodes have not ben de-allocated
//Post-Condition: Memory for nodes has ben de-allocated
//Description: De-allocates nodes
int bst::numLoc(string sentence)
{
    int senLength = sentence.length();
    
    for(int i = 0; i < senLength; i++)
    {
        if(isdigit(sentence[i]))
        {
            return i;
        }
    }
    return 0;
}


//Name: print_tree
//Pre-Condition: auxillary function for print_tree has not been called
//Post-Condition: auxillary function for print_tree has been called
//Description: calles auxillary function
void bst::print_tree()
{
    print_tree(root);
}

//Name: print_tree
//Pre-Condition: output has not been sent to the screen
//Post-Condition: output has been sent to the screen
//Description: prints output to the screen
void bst::print_tree(treenode* &loc_ptr)
{
    if(loc_ptr != NULL)
    {
        print_tree(loc_ptr -> lchild);
        cout << loc_ptr -> county_name << endl;
        //cout << setw(8) << loc_ptr -> county_population << endl;
        print_tree(loc_ptr -> rchild);
    }
}


//Name: insert
//Pre-Condition: auxillary function for insert has not been called
//Post-Condition: auxillary function for insert has been called
//Description: calles auxillary function
void bst::insert(const string & item, const double& population)
{
    insert(root, item, population);
}


//Name: insert
//Pre-Condition: node has not been inserted
//Post-Condition: node has been inserted
//Description: inserts node into the tree
 void bst::insert(treenode* &loc_ptr, const string& item, const double& population)
{
    if(loc_ptr == NULL)
    {
        loc_ptr = new treenode;
        loc_ptr -> lchild = loc_ptr -> rchild = NULL;
        loc_ptr -> county_name = item;
        loc_ptr -> county_population = population;
        //loc_ptr -> lchild = NULL;
        //loc_ptr -> rchild = NULL;
    }
    else if(loc_ptr -> county_name > item)
    {
        insert(loc_ptr -> lchild, item, population);
    }
    else if(loc_ptr -> county_name < item)
    {
        insert(loc_ptr -> rchild, item, population);
    }
    else
    {
        cout << "Item is already in the tree" << endl;
    }
    
}

//Name: county_ranges
//Pre-Condition: auxillary function for county_ranges has not been called
//Post-Condition: auxillary function for county_ranges has been called
//Description: calles auxillary function
void bst::county_ranges(const string& min_name, const string& max_name)
{
    county_ranges(root, min_name, max_name);
  
}

//Name: county_ranges
//Pre-Condition: range has not been outputed to the screen
//Post-Condition: range has been outputed to the screen
//Description: outputs range to the screen
void bst::county_ranges(treenode* &loc_ptr, const string& min_name, const string& max_name)
{
    
   if (loc_ptr != 0)
    {
        county_ranges(loc_ptr->lchild, min_name, max_name);
        if (loc_ptr->county_name >= min_name && loc_ptr->county_name <= max_name)
        {cout << loc_ptr->county_name << endl;
            
        }
        county_ranges(loc_ptr->rchild, min_name, max_name);
    }
    
}

//Name: del_name
//Pre-Condition: auxillary function for del_name has not been called
//Post-Condition: auxillary function for del_name has been called
//Description: calles auxillary function
void bst::del_name(string item)
{
    del_name(root, item);
}


//Name: del_name
//Pre-Condition: node has not been deleted
//Post-Condition: node has been deleted
//Description: deletes node from tree
void bst::del_name(treenode*& loc_ptr, string item)
{
    if (loc_ptr == NULL)
        cout << "item not in tree\n";
    else if (loc_ptr -> county_name > item)
        del_name(loc_ptr -> lchild, item);
    else if (loc_ptr -> county_name < item)
        del_name(loc_ptr -> rchild, item);
    else
    {
        treenode * ptr;
        //loc_ptr->county_population = ptr->county_population;
        if (loc_ptr -> lchild == NULL)
        {
            ptr = loc_ptr -> rchild;
            delete loc_ptr;
            loc_ptr = ptr;
            
        }
        else if (loc_ptr -> rchild == 0)
        {
            ptr = loc_ptr->lchild;
            delete loc_ptr;
            loc_ptr = ptr;
        }
        else
        {
            ptr = inorder_succ(loc_ptr);
            loc_ptr -> county_name = ptr -> county_name;
            del_name(loc_ptr -> rchild, ptr-> county_name);
            
        }
        
    }
}

//Name: inorder_succ
//Pre-Condition: the leftmost node of the right node has not been found
//Post-Condition: the leftmost node of the right node has been found
//Description: finds the leftmost node of the right node
treenode* bst::inorder_succ(treenode* loc_ptr)
{
    treenode *ptr = loc_ptr -> rchild;
    while (ptr -> lchild != NULL)
    {
        ptr = ptr -> lchild;
        
    }
    return ptr;
}

//Name: sorted_info
//Pre-Condition: auxillary function for sorted_info has not been called
//Post-Condition: auxillary function for sorted_info has been called
//Description: calles auxillary function and opens output file
void bst::sorted_info()
{
    ofstream out;
    out.open("county_info.txt");
    sorted_info(out, root);
    out.close();
}

//Name: sorted_info
//Pre-Condition: data has not been sent to the file
//Post-Condition: data has been sent to the file
//Description: sends data to output file
void bst::sorted_info(ostream& out, treenode*& loc_ptr)
{
    if(loc_ptr != NULL)
    {
        sorted_info(out, loc_ptr -> lchild);
        out << loc_ptr -> county_name;
        out << setw(8) << loc_ptr -> county_population << endl;
        sorted_info(out, loc_ptr -> rchild);
    }
}

//Name: empty_tree
//Pre-Condition: data has not been erased from tree
//Post-Condition: data has been erased from tree
//Description: erases data from tree
void bst::empty_tree() //de-allocate all nodes that were allocated to the bst
{
    while(root != NULL)
    {
        del_name(root -> county_name);
    }
    if(root == NULL)
    {
        cout << "Tree is empty" << endl;
    }
}
