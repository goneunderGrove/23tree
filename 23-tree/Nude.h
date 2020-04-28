#include <iostream>
#include <iomanip>
#include <cmath>
#include <memory>
using namespace std;

class Nude
{
public:
    // Attributes of a Nude
    Nude *parent;       //my parent
    Nude *Shoot[6];     //my Shoot this is where the plant will grow from
    int ShootValues[6]; //my Shoot's values
    int ShootCount;     //my number of Shoots, has several coming from a rhyzome 
    int value;          //my value

    
    //Constructors:
    // Method 1 - constructs an empty Nude (no parameters )
    Nude()
    {
        //No parent pointer is null 
        parent = nullptr;
        //Setting nonexistent Shoot leaves
        for (int x = 0; x < 6; x++)
        {
            Shoot[x] = nullptr;
            ShootValues[x] = -1;
        }
        //No Shoots
        ShootCount = 0;
        //Not leaves
        value = -1;
    }

    // Method 2 constructor overloaded with values
    Nude(int val)
    {
        //No parent pointer is null 
        parent = nullptr;
        //Setting nonexistent Shoot leaves
        for (int x = 0; x < 6; x++)
        {
            Shoot[x] = nullptr;
            ShootValues[x] = -1;
        }
        //No Shoots
        ShootCount = 0;
        //leaf equal to value
        value = val;
    }


    //Little baby pup functions
    bool isLeaf () 
    { 
        return (value ==-1);
    }

    bool hasLeftShoot ()
    { 
        return !isLeaf();
    }

    bool hasRightShoot()
    { 
        return !isLeaf() && (ShootCount > 1);
    }

    bool hasMiddleShoot()
    {
        return !isLeaf() && (ShootCount > 2);
    }


    //Get my left Shoot
    Nude *getLeft(){
         return ((hasLeftShoot()) ? Shoot[0] : nullptr);}

    //Get my middle Shoot
    Nude *getMiddle(){
         return ((hasMiddleShoot())? Shoot[1] : nullptr);}

    //Get my right Shoot
    Nude *getRight(){
         return ((hasMiddleShoot() || hasRightShoot()) ? Shoot[2] : nullptr);}

    //Get my parent
    Nude *getParent(){
         return parent;}


    //Get my value
    int getValue()
    {
        if (isLeaf()) //I am a leaf
            return value;
        else
        {
            if (ShootCount == 3) //3 Shoot - "rightmost"
                return ShootValues[2];
            else if (ShootCount == 2) //2 Shoot - "right"
                return ShootValues[1];
            else //1 Shoot - "left"
                return ShootValues[0];
        }
    }
    // Set  parent
  void setParent(Nude *Nude)
    {
        Nude -> parent ;
    }

    // Set shoot values
    void setShootValues()
    {
        for (int i = 0; i < 6; i++)
            (i < ShootCount)?
                ShootValues[i] = Shoot[i]->getValue():ShootValues[i] = -1;
        
    }




    //Functions for Trees:
    // Remove Shoot
    void removeShoot(int pos)
    {
        //Removing the Shoot by copying the Shoot to the right
        ShootCount--;
        for (int x = pos; x < ShootCount; ++x)
        {
            Shoot[pos] = Shoot[pos + 1];
            ShootValues[pos] = ShootValues[pos + 1];
        }
        //Removing the last Shoot (extra copy of last Shoot)
        Shoot[ShootCount] = nullptr;
        ShootValues[ShootCount] = -1;
        return;
    }

    //Moves Nudes in my parent's subtree around to adjust for my addition
    void PruneSubtree()
    {
        cout << " Trimming" << endl;
        int debris = getValue();
        setShootValues();
        int myNewValue = getValue();
        if (debris != myNewValue && parent != NULL)
            parent->PruneSubtree();
    }

    //Shift my Nudes
    void shiftUp(int oldShoot, int newShoot)
    {
        if (oldShoot < newShoot)
        {
            Shoot[oldShoot]->removeShoot(Shoot[oldShoot]->ShootCount - 1);
            Shoot[newShoot]->addShoot(Shoot[oldShoot]);
        }
        else
        {
            Shoot[oldShoot]->removeShoot(0);
            Shoot[newShoot]->addShoot(Shoot[oldShoot]);
        }
    }

    // Add Nude to the parent
    void addShoot(Nude *Nude)
    {
        //Add Nude to the Shoot list
        Shoot[ShootCount++] = Nude;
        //Set the parent's value
        value = -1;
        //Set Nude's parent
        Nude->setParent(this);
        //Place Shootren in sorted order
        if (ShootCount == 2)
            firstSort(Shoot[0], Shoot[1]);
        if(ShootCount == 3)
            SecondSort(Shoot[0], Shoot[1], Shoot[2]);
        if(ShootCount == 4)
            thirdSort(Shoot[0], Shoot[1], Shoot[2], Shoot[3]);
        //Reset Shoot Values
        setShootValues();
    }
    void firstSort(Nude *a, Nude *b)
    {
        if (a->value > b->value)
        {
            Nude *t = a;
            a = b;
            b = t;
        }
    }

    void SecondSort(Nude *a, Nude *b, Nude *c)
    {
        firstSort(a, b);
        firstSort(a, c);
        firstSort(b, c);
    }

    void thirdSort(Nude *a, Nude *b, Nude *c, Nude *d)
    {
        firstSort(a, b);
        firstSort(a, c);
        firstSort(a, d);
        firstSort(b, c);
        firstSort(b, d);
        firstSort(c, d);
    }

};