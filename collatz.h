//  collatz.h
//  Collatz Sequences Experimental Data Structure
//  Sequence Component
//  Created by Kenn Lui on 2021-12-17.
//  kenn_lui@sfu.ca

#ifndef collatz_h
#define collatz_h

#include "OmniNode.h"

class CollatzSequences
{
    private:
        OmniNodes::OmniNode ** head;
        static std::vector<OmniNodes::OmniNode *> trunk;
    public:
        CollatzSequences();
        CollatzSequences(const CollatzSequences &);
        ~CollatzSequences();
    public:
        OmniNodes::OmniNode ** getHead() const;
        std::vector<OmniNodes::OmniNode *> getTrunk() const;
    public:
        CollatzSequences operator=(const CollatzSequences &);
    public:
        static void printSequences();
        OmniNodes::OmniNode * findSequence (int);
        OmniNodes::OmniNode * findNode (int, int);
        int initiateTrunk(OmniNodes::OmniNode * &, OmniNodes::OmniNode ** &);
        int updateTrunk();
        int forwardSortTrunk();
        int addSequence(OmniNodes::OmniNode * &, int);
};

std::vector<OmniNodes::OmniNode *> emptyTrunk;
std::vector<OmniNodes::OmniNode *> CollatzSequences::trunk = emptyTrunk;

CollatzSequences::CollatzSequences()
{
    (this -> head) = nullptr;
}

CollatzSequences::CollatzSequences(const CollatzSequences & right)
{
    std::cout << "\nCollatzSequence deactivated copy constructor has been called.";
}

CollatzSequences::~CollatzSequences()
{
    (this -> head) = nullptr;
}

OmniNodes::OmniNode ** CollatzSequences::getHead() const
{
    return this -> head;
}

std::vector<OmniNodes::OmniNode *> CollatzSequences::getTrunk() const
{
    return (trunk);
}

CollatzSequences CollatzSequences::operator=(const CollatzSequences & right)
{
    std::cout << "\nCollatzSequence deactivated assignment operator has been called.";
    return * this;
}

void CollatzSequences::printSequences()
{
    OmniNodes::OmniNode * runner = nullptr;
    if ((trunk).size())
    {
        std::vector<OmniNodes::OmniNode *>::iterator it = (trunk).begin();
        while (it < (trunk).end())
        {
            std::cout << "\n[";
            if (*it)
            {
                runner = *it;
                OmniNodes::p1(runner,0);
            }
            else
                std::cout << ": empty :";
            std::cout << "]";
            it++;
        }
    }
}

OmniNodes::OmniNode * CollatzSequences::findSequence(int startValue)
{
    std::vector<OmniNodes::OmniNode *>::iterator it = (trunk).begin();
    while (it < (trunk).end())
    {
        if ((*it) -> getValue() == startValue)
            return *it;
        it++;
    }
    return nullptr;
}

OmniNodes::OmniNode * CollatzSequences::findNode(int nodeValue, int index)
{
    if ((trunk).size())
        if (index > (trunk).size() - 1)
        {
            std::vector<OmniNodes::OmniNode *>::iterator it = (trunk).begin();
            OmniNodes::OmniNode * runner = *(it + index);
            if (OmniNodes::f1(runner, nodeValue))
                return runner;
        }
    return nullptr;
}

int CollatzSequences::initiateTrunk(OmniNodes::OmniNode * & targetPtr, OmniNodes::OmniNode ** & targetAddress)
{
    int startValue = 6;
    int n = startValue;
    OmniNodes::OmniNode * nextNode = nullptr;
    
    if (targetPtr && targetAddress)
    {
        (trunk).clear();
        
        this -> head = targetAddress;
        OmniNodes::l4(targetAddress, startValue);
        
        *(this -> head) = targetPtr;
        *targetPtr = OmniNodes::OmniNode(startValue);
        OmniNodes::l1(targetPtr, startValue);
        
        OmniNodes::OmniNode * runner = targetPtr;
        (trunk).push_back(runner);
        
        while (n > 1)
        {
            nextNode = new OmniNodes::OmniNode(runner, n);
            n = OmniNodes::advance(nextNode, 0);
            OmniNodes::l1(nextNode, n);
            
            (trunk).push_back(nextNode);
            runner = nextNode;
        }
        
        if (OmniNodes::getConsoleDetailTogglePosition())
            std::cout << "\nCollatzSequences method 'initiateTrunk' has made a head node at " << (unsigned long) this -> head << " for a sequence at " << (unsigned long) this << " with a start value of " << startValue << ".";
        
        return 6;
    }
    return -1;
}

int CollatzSequences::updateTrunk()
{
    if ((trunk).size() < 2)
    {
        std::cout << "\nCollatzSequences method 'updateTrunk' did not run.";
        return -1;
    }
    
    OmniNodes::OmniNode * runner = nullptr;
    OmniNodes::OmniNode * secondRunner = nullptr;
    
    std::sort((trunk).begin(), (trunk).end(), OmniNodes::cso);
    std::vector<OmniNodes::OmniNode *>::iterator it = (trunk).begin();
    
    while (it < (trunk).end())
    {
        runner = *it;
        while (runner)
        {
            int targetValue = runner -> getValue();
            std::sort((trunk).begin(), (trunk).end(), OmniNodes::cso);
            secondRunner = findSequence(targetValue);
            if (secondRunner == nullptr)
                (trunk).push_back(runner);
            runner = runner -> getNext();
        }
        it++;
    }
    std::cout << "\nCollatzSequences method 'updateTrunk' has run.";
    
    return 1;
}

int CollatzSequences::forwardSortTrunk()
{
    if (updateTrunk())
    {
        std::sort((trunk).begin(), (trunk).end(), OmniNodes::csf);
        std::cout << "\nCollatzSequences method 'forwardSortTrunk' has run.";
        return 1;
    }
    std::cout << "\nCollatzSequences method 'forwardSortTrunk' did not run.";
    return -1;
}

int CollatzSequences::addSequence(OmniNodes::OmniNode * & targetPtr, int target)
{
    if (this -> head && *(this -> head) && targetPtr)
    {
        updateTrunk();
        
        // check if the target value is already in the trunk
        OmniNodes::OmniNode * secondRunner = nullptr;
        secondRunner = findSequence(target);
        if (secondRunner)
            return -1;
        
        // build sequence until a trunk value is reached or until 1 is reached
        else
        {
            int n = target;
            OmniNodes::OmniNode * runner = nullptr;
            
            targetPtr -> setValue(target);
            OmniNodes::l1(targetPtr, target);
            (trunk).push_back(targetPtr);
            runner = targetPtr;
            
            while (n > 1)
            {
                OmniNodes::OmniNode * nextNode = new OmniNodes::OmniNode(runner, n);
                n = OmniNodes::advance(nextNode, 0);
                secondRunner = findSequence(n);
                if (secondRunner)
                {
                    // secondRunner holds an address once a trunk value is reached
                    delete nextNode;
                    nextNode = nullptr;
                    runner -> setNext(secondRunner);
                    runner -> setTail(secondRunner);
                    return n;
                }
                else
                {
                    // nextNode is allocated memory so long as no trunk value is reached
                    OmniNodes::l1(nextNode, n);
                    (trunk).push_back(nextNode);
                    runner = nextNode;
                }
            }
            return target;
        }
    }
    return -1;
}

class CollatzWorkBook
{
    private:
        OmniNodes::OmniNode ** headNodes;
        int headNodesCount;
        CollatzSequences driver;
        
    public:
        CollatzWorkBook();
        CollatzWorkBook(int);
        virtual ~CollatzWorkBook();
    
    public:
        std::vector<OmniNodes::OmniNode *> getTrunk() const;
    
    public:
        void printNodes();
};

CollatzWorkBook::CollatzWorkBook()
{
    this -> driver = CollatzSequences();
    this -> headNodesCount = 1;
    this -> headNodes = new OmniNodes::OmniNode *;
    //OmniNodes::l4(this -> headNodes, 0);
    //log later; wait for CollatzSequences method 'initiateTrunk' to call l4
    
    OmniNodes::OmniNode ** runner = (this -> headNodes);
    *runner = new OmniNodes::OmniNode(1);
    //OmniNodes::l1(*runner, 1);
    //log later; wait for CollatzSequences method 'initiateTrunk' to call l1
    
    (this -> driver).initiateTrunk(*runner, runner);
    (this -> driver).updateTrunk();
    
    OmniNodes::OmniNode * nodeDummy = nullptr;
    OmniNodes::OmniNode ** addressDummy = nullptr;
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
}

CollatzWorkBook::CollatzWorkBook(int n)
: CollatzWorkBook::CollatzWorkBook()
{
    // Count variable and memory log dummy nodes
    
    int count = 1;
    OmniNodes::OmniNode * nodeDummy = nullptr;
    OmniNodes::OmniNode ** addressDummy = nullptr;
    
    // Display memory logs
    
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
    
    // Address to which more memory is allocated than will be required
    
    OmniNodes::OmniNode ** overallocatedArray = new OmniNodes::OmniNode * [n];
    
    // Copy over first head node to the overallocated array
    
    OmniNodes::OmniNode ** runner = overallocatedArray;
    *runner = *(this -> headNodes);
    
    // Continue populating the overallocated array to the extent necessary

    //for (int i = n; i > 1; i--)
    for (int i = 7; i < n; i++)
    {
        (this -> driver).updateTrunk();
        runner = overallocatedArray + count;
        nodeDummy = (this -> driver).findSequence(i);
        if (nodeDummy == nullptr)
        {
            *runner = new OmniNodes::OmniNode(i);
            (this -> driver).addSequence(*runner, i);
            this -> headNodesCount++;
            count++;
        }
    }
    
    // Move this -> headNodes to new memory that just accommodates the elements in overallocated array
    
    OmniNodes::d2(this -> headNodes, 0);
    this -> headNodes = new OmniNodes::OmniNode * [this -> headNodesCount];
    for (int i = 0; i < this -> headNodesCount; i++)
    {
        runner = this -> headNodes + i;
        *runner = *(overallocatedArray + i);
        OmniNodes::l4(runner, 0);
    }
    
    // Deallocate overallocation address
    
    delete [] overallocatedArray;
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
}

CollatzWorkBook::~CollatzWorkBook()
{
    OmniNodes::OmniNode ** runner = nullptr;
    
    for (int i = 0; i < this -> headNodesCount; i++)
    {
        runner = (this -> headNodes + i);
        if (*runner)
            OmniNodes::d1(*runner, 0);
    }
    
    runner = this -> headNodes;
    OmniNodes::d3(runner, this -> headNodesCount);
    
    OmniNodes::OmniNode * nodeDummy = nullptr;
    OmniNodes::OmniNode ** addressDummy = nullptr;
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
    
    std::cout << "\nCollatzWorkBook virtual destructor has run.\n";
}

std::vector<OmniNodes::OmniNode *> CollatzWorkBook::getTrunk() const
{
    return (this -> driver).getTrunk();
}

void CollatzWorkBook::printNodes()
{
    OmniNodes::p2(this -> headNodes, this -> headNodesCount);
}

void testTrunkInitiation()
{
    std::cout << "Trunk testing, initiation, has started.";
    OmniNodes::OmniNode::hideDetail();
    
    CollatzSequences test;
    int target;
    OmniNodes::OmniNode * targetPtr = new OmniNodes::OmniNode();
    OmniNodes::OmniNode ** targetAddress = new OmniNodes::OmniNode *;
    test.initiateTrunk(targetPtr, targetAddress);
    target = targetPtr -> getValue();
    
    CollatzSequences::printSequences();
    
    OmniNodes::OmniNode * nodeDummy = nullptr;
    OmniNodes::OmniNode ** addressDummy = nullptr;
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
    
    test.updateTrunk();
    CollatzSequences::printSequences();
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
    
    OmniNodes::OmniNode * nextPtr = new OmniNodes::OmniNode();
    test.addSequence(nextPtr, 7);
    CollatzSequences::printSequences();
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
    
    OmniNodes::OmniNode * nextNextPtr = new OmniNodes::OmniNode();
    test.addSequence(nextNextPtr, 8);
    CollatzSequences::printSequences();
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
    
    OmniNodes::d1(targetPtr, 0);
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
    
    OmniNodes::d1(nextPtr, 0);
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
    
    OmniNodes::d1(nextNextPtr, 0);
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
    
    OmniNodes::OmniNode::showDetail();
    OmniNodes::d2(targetAddress, target);
    OmniNodes::l3(nodeDummy, 0);
    OmniNodes::l6(addressDummy, 0);
    
    std::cout << "\nTrunk testing, initiation, is complete.\n";
}

#endif /* collatz_h */

