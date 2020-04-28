#include<memory>
#include "Nude.h"

using namespace std;

class Tree
{
private: 
  Nude* root;


  // Inserts and Their Cases 1 2 and 3

  // fucntion to absoard nodes     
  void absorb(Nude*a, Nude *b)
  {
    if (b==root)
    {
      Nude *rhizome= new Nude();
      // left of rhizome
      rhizome->addShoot(a);
      // right of rhizome
      rhizome-> addShoot(b);
      // The rhzome will become the new nude 
      rhizome->setShootValues();
      
      root = rhizome;
      return;
    }
    else 
    {
      Nude* p = b ->getParent();
      p-> addShoot(a);
      cout<< " Grow "<< endl; 

      // easy cases  when the array isnt full and you dont have to do magic
      if (p-> ShootCount <=3 && p-> parent !=0)
      p->parent->PruneSubtree();

      else 
      {
      Nude *rleft = new Nude();
        //seperate by left and right sideds of tree 
        int leftLeaves = p-> ShootCount /2;
        int rightLeaves =p-> ShootCount-leftLeaves;

        for (int i=0; i < leftLeaves; i++)
        {
        rleft->addShoot(p->Shoot[i]);             
          p->Shoot[i] = p->Shoot[i + leftLeaves];
        }
        if (leftLeaves < rightLeaves)
          p->Shoot[leftLeaves] = p-> Shoot[p->ShootCount -1];
        
        for ( int x =rightLeaves; x < p->ShootCount -1; ++x)
          p->Shoot[rightLeaves]=0;
      
      p->ShootCount=rightLeaves;
      p->setShootValues();
      absorb(rleft,p);
      }
    }
  }
  





    // Delete - discard a from the tree
    void discard(Nude *a)
    {
        // Let p be the parent of a
        Nude *p = a->getParent();

        // Remove the connection between p and a by searching for a in the parent
        for (int i = 0; i < p->ShootCount; i++)
            if (p->Shoot[i] == a)
                p->removeShoot(i);

        // Cleanup
        delete a;

        //Parent could remove child
        if (p->ShootCount >= 2){
            return;
        }
        else if (p->getParent() == NULL)    //Deleted the root value (2 case)
        {
            if (!p->Shoot[0]->isLeaf())     //Set root to left child
            {
                root = p->Shoot[0];
                delete (p);
            }
            return;
        }


    //Find the totnumber of children among all siblings of p
        Nude *allMyBranches = p-> getParent();
        int allMyLeaves = 0;
        int pups;
        bool recurse; 

        if (allMyLeaves >= 4)
        {
            if (allMyBranches->ShootCount == 2)
                 (allMyBranches->Shoot[0]->ShootCount == 3)?
                    allMyBranches->shiftUp(0, 1): allMyBranches->shiftUp(1, 0);

            else if (allMyLeaves == 5)
                 (pups == 2)? 
                    allMyBranches->shiftUp(pups, 1):
                        allMyBranches->shiftUp(pups, pups+1);
            else
                if (pups == 0)
                {
                    allMyBranches->shiftUp(1, 0);
                    if (allMyBranches->Shoot[1]->ShootCount == 1)
                        allMyBranches->shiftUp(2, 1);
                }
                else if (pups == 2)
                {
                    allMyBranches->shiftUp(1, 2);
                    if (allMyBranches->Shoot[1]->ShootCount == 1)
                        allMyBranches->shiftUp(0, 1);
                }
                else
                    (allMyBranches->Shoot[0]->ShootCount > allMyBranches->Shoot[2]->ShootCount)?
                        allMyBranches->shiftUp(0, 1): allMyBranches->shiftUp(1, 1);
        }
        else //Allocate b to the sibling of p
        {
            if (pups == 0)
                allMyBranches->shiftUp(0, 1);
            else
                allMyBranches->shiftUp(1, 0);
                discard(p);
                recurse = false;
        }

        if (recurse)
            allMyBranches->PruneSubtree();
    }


    public: 
    Tree (Nude*l)
    {
      root = l;
    }
    Tree ()
    {
      root=nullptr;
    }

  Nude *Search(Nude *root, int valToFind)
    { //I found a leaf at least my value
        if (root->isLeaf())
        {
            return root;
        }
        // Find where in my node to recurse
        if (root->getLeft()->getValue() >= valToFind)
        {
            return Search(root->getLeft(), valToFind);
        }
        if (root->hasMiddleShoot() && root->getMiddle()->getValue() >= valToFind)
        {
            return Search(root->getMiddle(), valToFind);
        }
        else
            return Search(root->getRight(), valToFind);
    }

    void Insert(int valToAdd)
      {
        //new leaf a
        Nude *a = new Nude(valToAdd);
        Nude *b = Search(root, valToAdd);
        if (a == b) //I already am in the tree
            return;
        else //Absorb me into the tree
            absorb(a, b);
      }

    void Delete(int valToRemove)
    {
        //Find a leaf at least my value in the tree
        Nude *a = Search(root, valToRemove);

        //I exist in the tree so delete me
        if (a->getValue() == valToRemove)
            discard(a);
    }


    // Print a 2-3 tree
    void Print() {
        print(root);
    }

    void print(Nude * r) {
        //No Tree
        if(r == nullptr)
            cout << "The seedling does not exist." << endl;
        else {
            Nude * parent = r;
            if(parent->ShootCount < 2)
                cout << "One Child: " << parent->getValue() << endl;
            else if(parent->ShootCount == 2) {
                cout << "Two Child: " << parent->getLeft()->getValue() << " " << parent->getRight()->getValue() << endl;
                print(parent->getLeft());
                print(parent->getRight());
                cout << endl;
            }
            else {
                cout << "Three Child: " << parent->getLeft()->getValue() << " " << parent->getMiddle()->getValue() << " " << parent->getRight()->getValue() << endl;
                print(parent->getLeft());
                print(parent->getMiddle());
                print(parent->getRight());
                cout << endl;
            }
        }
    }
};






//   // Case 1 Insert into a node with 1 child

//  void InsertPhaseI (int seeds)
// { 
//   p ->parent = new Nude(seeds)
  
// }



  // Case 2 Insert into a node with 2 children







  // Case 3 // Insert into a node with 3 children








//Lets print the stree 
// function to print the tree
// void print() {
//     print(root->child[0]);
//     cout << endl;
// }



// //constructors 
// Tree(){
//   root->new Nude();
//   root->child[0]=new Nude();
//   root->child[0]->parent = root;
// }

// // Class tree 


















// // Delete 
// T.delete(leaf a){

//     leaf b=T.search(a);
//     if(b==a)
//         discard(a);
//     return T;
// }

// T.discard(node a){
//     let p be the parent of a
//     Remove the connection between p and a
//     if (p has 2 children)
//         return T; //&nbsp;might have to "readjust" p (and up)
//     // p has 1 child
    
//     let allMyBranches = number of children among all siblings of p (including p)     // allMyBranches  [3,7]
    
//     if ( allMyBranches >= 4)
//         distribute children among at least 2 parents, skewing left.
//         // maybe I have to remove one parent
//         // might need to propagate these new values up the tree.
//         retrun T;
        
        
//         //allMyBranches = 3
//         let b be the only child of p.
//         if ( p is the root) {
//             remove p and make b the root of T;
//             return T; ( or b if you prefer, since its the root of the tree)
//         }
//         //p is not the root
//         Allocate b to the siblinf of s of p.
//         Return discard (p);  
// }


// print tree 







// // Search tree 

// T.Search(leaf a) { 
    
//     /* Let "root" refer to the root of T. */
//     /* Basr case for leaf */
//     if(root has no children)
//         return root;
    
       
//     if ( a<= root.left) {
//         (root.leftchild).Search(a);
        
//     } else if ( a<= root.mid) {              /* reminder to write something to check if mid is there*/
//         (root.midchild).Search(a);
        
//     } else if (a <= root.right)
//         (root.rightchild).search(a);
//     }
//     else 
//         return /* largest element in the array */;
//