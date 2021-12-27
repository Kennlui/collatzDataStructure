//  OmniNode.h
//  Collatz Sequences Experimental Data Structure
//  Node Component
//  Created by Kenn Lui on 2021-12-17.
//  kenn_lui@sfu.ca

#ifndef OmniNode_h
#define OmniNode_h
#include <vector>

namespace OmniNodes {

class OmniNode;
int logMemoryAddress(OmniNode * &, int);
int logMemoryAddress(OmniNode ** &, int);
typedef int(* OmniNodeFunc)(OmniNode * &, int);
typedef int(* SuppFunc)(OmniNode ** &, int);

class OmniNode
{
    private:
        int value;
        OmniNode * next;
        OmniNode * tail;
        int length;
        static bool showConsoleDetailforNode;
        static std::vector<unsigned long> nodeAddressLog;
        static std::vector<unsigned long> nodeLog;
    
    public:
        OmniNode();
        OmniNode(int);
        OmniNode(OmniNode *, int);
        OmniNode(const OmniNode &);
        virtual ~OmniNode();
    
    public:
        int getValue() const;
        OmniNode * getNext() const;
        OmniNode * getTail() const;
        int getLength();
        bool isEven() const;
        int getMaxValue() const;
    
    public:
        void setValue(int);
        void setNext(OmniNode *);
        void setTail(OmniNode *);
    
    public:
        static void hideDetail();
        static void showDetail();
        
    public:
        void printNode() const;
    
    public:
        OmniNode operator=(const OmniNode &);
        bool compareSegments(const OmniNode &);
        bool operator==(const OmniNode &);
        bool operator>(const OmniNode &);
        bool operator<(const OmniNode &);
        bool operator==(const OmniNode * &);
        bool operator>(const OmniNode * &);
        bool operator<(const OmniNode * &);
        // comparison function for std::sort is housed in a struct 'cso'
        
    public:
        friend bool getConsoleDetailTogglePosition();
    
    public:  // OmniNodeFunc standard friend functions
/*p1*/  friend int printSegment(OmniNode * &, int);
/*a3*/  friend int decrease(OmniNode * &, int);
/*a2*/  friend int increase(OmniNode * &, int);
/*a1*/  friend int advance(OmniNode * &, int);
/*f1*/  friend int findNode(OmniNode * &, int);
/*f2*/  friend int findPrevNode(OmniNode * &, int);
/*l1*/  friend int logMemoryAddress(OmniNode * &, int);
/*l2*/  friend int removeFromLog(OmniNode * &, int);
/*l3*/  friend int printLog(OmniNode * &, int);
/*l7*/  friend int resetLog(OmniNode * &, int);
/*m1*/  friend int movePtrNSteps(OmniNode * &, int);
/*m2*/  friend int movePtrToNext(OmniNode * &, int);
/*m3*/  friend int movePtrToLast(OmniNode * &, int);
/*m4*/  friend int movePtrToNextToLast(OmniNode * &, int);
/*d1*/  friend int deallocate(OmniNode * &, int);

    public:  // Supplementary friend functions
/*p2*/  friend int printSequences(OmniNode ** &, int);
/*l4*/  friend int logMemoryAddress(OmniNode ** &, int);
/*l5*/  friend int removeFromLog(OmniNode ** &, int);
/*l6*/  friend int printLog(OmniNode ** &, int);
/*l8*/  friend int resetLog(OmniNode ** &, int);
/*d2*/  friend int deallocate(OmniNode ** &, int);
/*d3*/  friend int deallocateArray(OmniNode ** &, int);

};

bool OmniNode::showConsoleDetailforNode = true;
std::vector<unsigned long> emptyVector;
std::vector<unsigned long> OmniNode::nodeLog = emptyVector;
std::vector<unsigned long> OmniNode::nodeAddressLog = emptyVector;

struct
{
    bool operator()(OmniNode * lPtr, OmniNode * rPtr) const
    {
        return (lPtr -> getValue() > rPtr -> getValue());
    }
} cso;

struct
{
    bool operator()(OmniNode * lPtr, OmniNode * rPtr) const
    {
        return (lPtr -> getValue() < rPtr -> getValue());
    }
} csf;

OmniNode::OmniNode()
{
    this -> value = -1;
    this -> next = nullptr;
    this -> tail = nullptr;
    this -> length = 1;
    
    if (OmniNode::showConsoleDetailforNode)
        std::cout << "\nOmniNode default constructor has made an orphan node at " << (unsigned long) this << " with value [ " <<  this -> value << " ]; orphan node points to " << (unsigned long) this -> next << ".";
}

OmniNode::OmniNode(int n)
{
    this -> value = n;
    this -> next = nullptr;
    this -> tail = nullptr;
    this -> length = 1;
    
    if (OmniNode::showConsoleDetailforNode)
        std::cout << "\nOmniNode 1 arg constructor has made an orphan node at " << (unsigned long) this << " with value [ " <<  this -> value << " ]; orphan node points to " << (unsigned long) this -> next << ".";
}

OmniNode::OmniNode(OmniNode * prevPtr, int n)
{
    if (OmniNode::showConsoleDetailforNode)
        std::cout << "\nPrevious node at " << (unsigned long) prevPtr << " with value [ " << prevPtr -> value << " ] will point to a newly made node.";
    
    prevPtr -> next = this;
    this -> value = n;
    this -> next = nullptr;
    this -> tail = nullptr;
    this -> length = (prevPtr -> length)++;
    
    if (OmniNode::showConsoleDetailforNode)
        std::cout << "\nOmniNode 2 arg constructor has made a node at " << (unsigned long) this << " with value [ " <<  this -> value << " ]; previous node at " << (unsigned long) prevPtr << " with value [ " << prevPtr -> value << " ] points to the newly made node.";
}

OmniNode::OmniNode(const OmniNode & right)
{
    if (this != & right)
    {
        this -> length = right.length;
        this -> tail = right.tail;
        this -> value = right.value;
        if (right.next == nullptr)
            this -> next = nullptr;
        else if (right.next -> next == nullptr)
        {
            this -> next = new OmniNode(right.next -> value);
            this -> next -> tail = right.next -> tail;
            logMemoryAddress(this -> next, right.next -> value);
            this -> next -> next = nullptr;
        }
        else
        {
            this -> next = new OmniNode(right.next -> value);
            this -> next -> tail = right.next -> tail;
            logMemoryAddress(this -> next, right.next -> value);
            OmniNode * prevPtr = this -> next;
            OmniNode * rightRunner = right.next -> next;
            while (rightRunner)
            {
                OmniNode * nextNode = new OmniNode(prevPtr, rightRunner -> value);
                logMemoryAddress(nextNode, rightRunner -> value);
                prevPtr = nextNode;
                rightRunner = rightRunner -> next;
            }
        }
    }
    
    if (OmniNode::showConsoleDetailforNode)
        std::cout << "\nOmniNode copy constructor has made an orphan node at " << (unsigned long) this << " with value [ " << this -> value << " ]; orphan node points to " << (unsigned long) this -> next << ".";
}

OmniNode::~OmniNode()
{
    OmniNode * p = this -> next;
    this -> next = nullptr;
    this -> tail = nullptr;
    
    if (OmniNode::showConsoleDetailforNode && p)
        std::cout << "\nOmniNode virtual destructor may possibly orphan a node at " << (unsigned long) p << ".";
    if (OmniNode::showConsoleDetailforNode)
        std::cout << "\nOmniNode virtual destructor has run.  While the destructor does not perform memory management, OmniNode friend function 'deallocate' or d1 is available.  Consider using d1 if an OmniNode object has been allocated memory on the heap.";
}

int OmniNode::getValue() const
{
    return this -> value;
}

OmniNode * OmniNode::getNext() const
{
    return this -> next;
}

OmniNode * OmniNode::getTail() const
{
    return this -> tail;
}

int OmniNode::getLength()
{
    if (!(this -> next))
        this -> length = 1;
    else if (this -> tail)
        this -> length = 1;
    else if (!(this -> next -> next))
        this -> length = 2;
    else
    {
        OmniNode * runner = this -> next;
        int n = 1;
        int m = 1;
        while (n > 0)
        {
            n = movePtrToNext(runner, 0);
            m++;
        }
        this -> length = m;
    }
    return this -> length;
}

bool OmniNode::isEven() const
{
    return (this -> value % 2 == 0);
}

int OmniNode::getMaxValue() const
{
    int rv = this -> value;
    if (this -> next)
    {
        OmniNode * runner = this -> next;
        while (runner)
        {
            if (runner -> value > rv)
                rv = runner -> value;
            runner = runner -> next;
        }
    }
    return rv;
}

void OmniNode::setValue(int k)
{
    this -> value = k;
}

void OmniNode::setNext(OmniNode * ptr)
{
    this -> next = ptr;
}

void OmniNode::setTail(OmniNode * ptr)
{
    this -> tail = ptr;
}

void OmniNode::hideDetail()
{
    OmniNode::showConsoleDetailforNode = false;
}

void OmniNode::showDetail()
{
    OmniNode::showConsoleDetailforNode = true;
}

void OmniNode::printNode() const
{
    std::cout << "\nOmniNode object at " << this << " (" << (unsigned long) this << ") with value [ " << this -> value << " ] points to next object at " << this -> next << ".";
}

OmniNode OmniNode::operator=(const OmniNode & right)
{
    if (this != & right)
    {
        // delete home sequence
        if (this -> next)
        {
            OmniNode * runner = this -> next;
            deallocate(runner, 0);
        }
        
        // assign right value and length to this
        this -> value = right.value;
        this -> length = right.length;
        
        // initiate runner pointers to traverse both lists
        OmniNode * homeRunner = this -> next;
        OmniNode * rightRunner = right.next;
        while (rightRunner)
        {
            if (homeRunner == nullptr)
            {
                // extend empty home list with a new node initiated with next right value
                OmniNode * nextNode = new OmniNode(rightRunner -> value);
                logMemoryAddress(nextNode, rightRunner -> value);
                homeRunner = nextNode;
            } else {
                // change value for nth node in home list to value for nth node in right list
                homeRunner -> value = rightRunner -> value;
            }
            homeRunner = homeRunner -> next;
            rightRunner = rightRunner -> next;
        }
    }
    return * this;
}

bool OmniNode::compareSegments(const OmniNode & target)
{
    //compare lengths
    bool rv = (this -> length == target.length);
    
    //compare first node values
    if (rv)
        rv = (this -> value == target.getValue());
    
    //compare remaining node values
    if (rv)
    {
        OmniNode * homeRunner = this -> next;
        OmniNode * targetRunner = target.getNext();
        while (rv)
        {
            rv = (homeRunner -> getValue() == targetRunner -> getValue());
            homeRunner = homeRunner -> getNext();
            targetRunner = targetRunner -> getNext();
            rv = (homeRunner && targetRunner);
        }
    }
    
    //return comparison result value
    return rv;
}

bool OmniNode::operator==(const OmniNode & right)
{
    return (this -> compareSegments(right));
}

bool OmniNode::operator>(const OmniNode & right)
{
    return (this -> value > right.value);
}

bool OmniNode::operator<(const OmniNode & right)
{
    return (this -> value < right.value);
}

bool OmniNode::operator==(const OmniNode * & rightPtr)
{
    return (this -> compareSegments(*rightPtr));
}

bool OmniNode::operator>(const OmniNode * & rightPtr)
{
    return (this -> value > rightPtr -> value);
}

bool OmniNode::operator<(const OmniNode * & rightPtr)
{
    return (this -> value < rightPtr -> value);
}

bool getConsoleDetailTogglePosition()
{
    return OmniNode::showConsoleDetailforNode;
}

int printSegment(OmniNode * & runner, int n)
{
    bool goForward = true;
    if (runner == nullptr)
    {
        std::cout << ": empty :";
        return -1;
    }
    else if (n < 1 && (runner -> next))
        n = runner -> getLength();              // the getLength() accessor updates the length attribute, in case the attribute is out of date
    std::cout << ": ";
    while (runner -> next && (n > 0) && (goForward))
    {
        if (runner -> next -> tail)
            goForward = false;
        std::cout << runner -> value << ", ";
        runner = runner -> next;
        n--;
    }
    std::cout << runner -> value << " :";
    return n;
}

OmniNodeFunc p1 = printSegment;

int printSequences(OmniNode ** & runner, int size)
{
    int rv = 0;
    OmniNode * segmentRunner = nullptr;
    
    for (int i = 0; i < size - 1; i++)
    {
        std::cout << "\n [ ";
        if (runner + i)
        {
            segmentRunner = *(runner + i);
            if (segmentRunner)
                p1(segmentRunner, 0);
            else
                std::cout << ": empty :";
            std::cout << " ],";
            rv++;
        }
        else
        {
            std::cout << ": empty :";
            std::cout << " ],";
        }
    }
    if (runner + size - 1)
    {
        std::cout << "\n [ ";
        
        segmentRunner = *(runner + size - 1);
        if (segmentRunner)
            p1(segmentRunner, 0);
        else
            std::cout << ": empty :";
        std::cout << " ]";
        rv++;
    }
    else
    {
        std::cout << "\n [ ";
        std::cout << ": empty :";
        std::cout << " ]";
    }
    return rv;
}

SuppFunc p2 = printSequences;

int decrease(OmniNode * & target, int n)
{
    if (n < 1)
        n = 0;
    if (n == 0)
    {
        n = target -> value / 2;
        target -> value = n;
        if (OmniNodes::getConsoleDetailTogglePosition())
            std::cout << "\nCollatz friend function a2, expanded, has decreased the value for a node at " << (unsigned long) target << " to a value of " << n << ".";
        return n;
    }
    else
    {
        while (n % 2 == 0)
            n /= 2;
        target -> value = n;
        if (OmniNodes::getConsoleDetailTogglePosition())
            std::cout << "\nCollatz friend function a2, condensed, has decreased the value for a node at " << (unsigned long) target << " to a value of " << n << ".";
        return target -> value;
    }
}

OmniNodeFunc a2 = decrease; // this is a function that decreases a value for a node in place; the node whose value decreases in place has an address stored by 'target' pointer which is the first parameter; you can use this function to assist a constructor that has made a next node, nextNode, with a value that is identical to the previous node's value; after the constructor has made nextNode, this function will decrease nextNode's value in place

int increase(OmniNode * & target, int n)
{
    if (n < 1)
        n = 0;
    if (n == 0)
    {
        n = target -> value;
        n = (3 * n) + 1;
        target -> value = n;
        if (OmniNodes::getConsoleDetailTogglePosition())
            std::cout << "\nCollatz friend function a3, expanded, has increased the value for a node at " << (unsigned long) target << " to a value of " << n << ".";
        return n;
    }
    else
    {
        while (n % 2 != 0)
            n = (3 * n) + 1;
        target -> value = n;
        if (OmniNodes::getConsoleDetailTogglePosition())
            std::cout << "\nCollatz friend function a3, condensed, has increased the value for a node at " << (unsigned long) target << " to a value of " << n << ".";
        return n;
    }
}

OmniNodeFunc a3 = increase; // this is a function that decreases a value for a node in place; the node whose value decreases in place has an address stored by 'target' pointer which is the first parameter; you can use this function to assist a constructor that has made a next node, nextNode, with a value that is identical to the previous node's value; after the constructor has made nextNode, this function will decrease nextNode's value in place

int advance(OmniNode * & target, int n)
{
    if (target -> isEven())
        return (decrease(target, n));
    else
        return (increase(target, n));
}

OmniNodeFunc a1 = advance;

int findNode(OmniNode * & runner, int target)
{
    if (runner == nullptr)
        return -1;
    else if (runner -> next == nullptr)
    {
        if (runner -> value == target)
            return target;
        else
            return -1;
    }
    else if (target < 1)
        target = 0;
    while (runner)
        if (runner -> value == target)
            return target;
        else
            runner = runner -> next;
    return -1;
}

OmniNodeFunc f1 = findNode;

int findPrevNode(OmniNode * & runner, int target)
{
    OmniNode * prev = nullptr;
    if (runner == nullptr)
        return -1;
    else if (runner -> next == nullptr)
        return -1;
    else if (target < 1)
        target = 0;
    while (runner)
    {
        if ((runner -> value == target) && prev)
        {
            runner = prev;
            return target;
        }
        prev = runner;
        runner = runner -> next;
    }
    return -1;
}

OmniNodeFunc f2 = findPrevNode;

int movePtrNSteps(OmniNode * & runner, int n)
{
    if (runner == nullptr)
        return -1;
    else if (runner -> next == nullptr)
        return -1;
    else if (n < 1)
        n = 1;
    while (runner && n)
    {
        n--;
        runner = runner -> next;
    }
    return n;
}

OmniNodeFunc m1 = movePtrNSteps;

int movePtrToNext(OmniNode * & runner, int n)
{
    if (!runner)
        return -1;
    else if (runner -> tail)
    {
        runner = nullptr;
        return -1;
    }
    else if (!(runner -> next))
    {
        runner = nullptr;
        return -1;
    }
    else if (n < 1)
        n = 0;
    if (n == 0)
        runner = runner -> next;
    else if (f1(runner, n) < 0)
        return -1;
    return runner -> value;
}

OmniNodeFunc m2 = movePtrToNext;

int movePtrToLast(OmniNode * & runner, int n)
{
    if (runner == nullptr)
        return -1;
    else if (runner -> next == nullptr)
    {
        runner = nullptr;
        return runner -> value;
    }
    else if (n < 1)
        n = 0;
    if (n == 0)
        while (runner -> next)
            runner = runner -> next;
    else if (f1(runner, n) < 0)
        return -1;
    else
        while (f1(runner, n) >= 0)
            runner = runner -> next;
    return runner -> value;
}

OmniNodeFunc m3 = movePtrToLast;

int movePtrToNextToLast(OmniNode * & runner, int n)
{
    OmniNode * prev = nullptr;
    if (runner == nullptr)
        return -1;
    else if (runner -> next == nullptr)
    {
        return -1;
    }
    else if (n < 1)
        n = 0;
    if (n == 0)
    {
        while (runner -> next)
        {
            prev = runner;
            runner = runner -> next;
        }
        if (prev)
        {
            runner = prev;
            return runner -> value;
        }
        else
            return -1;
    }
    else if (f2(runner, n) < 0)
        return -1;
    else
        while (f2(runner, n) >= 0)
            runner = runner -> next -> next;
    return runner -> value;
}

OmniNodeFunc m4 = movePtrToNextToLast;

int logMemoryAddress(OmniNode * & runner, int value)
{
    if (value > 0)
    {
        unsigned long v = (unsigned long) value;
        OmniNode::nodeLog.push_back(v);
        unsigned long m = (unsigned long) runner;
        OmniNode::nodeLog.push_back(m);
        return value;
    }
    return -1;
}

OmniNodeFunc l1 = logMemoryAddress;

int removeFromLog(OmniNode * & runner, int value)
{
    std::vector<unsigned long>::iterator itl1;
    unsigned long v = (unsigned long) value;
    itl1 = std::find(OmniNode::nodeLog.begin(), OmniNode::nodeLog.end(), v);
    
    std::vector<unsigned long>::iterator itl2;
    unsigned long m = (unsigned long) runner;
    itl2 = std::find(OmniNode::nodeLog.begin(), OmniNode::nodeLog.end(), m);
    
    if (++itl1 == itl2)
    {
        OmniNode::nodeLog.erase(--itl1, ++itl2);
        return value;
    }
    else
        while (itl1 < OmniNode::nodeLog.end())
        {
            itl1 = std::find(itl1, OmniNode::nodeLog.end(), v);
            if (++itl1 == itl2)
            {
                OmniNode::nodeLog.erase(--itl1, ++itl2);
                return value;
            }
        }
    return -1;
}

OmniNodeFunc l2 = removeFromLog;

int printLog(OmniNode * & dummy, int value)
{
    int s = (int) OmniNode::nodeLog.size();
    if (value == 0)
        value = s;
    std::vector<unsigned long>::iterator itl;
    std::cout << "\nContents of node log:";
    if (s == 0)
    {
        std::cout << "\n\t The node log is empty.";
        return 0;
    }
    itl = OmniNode::nodeLog.begin();
    while (itl < OmniNode::nodeLog.end() && value)
    {
        std::cout << "\n\t Value: " << *itl << "\n\t\t\t\t\t\t /  ";
        if (itl < OmniNode::nodeLog.end())
            {
                itl++;
                std::cout << "Address: " << *itl << ".";
            }
        itl++;
        value--;
    }
    std::cout << "\n  Size of log: " << (OmniNode::nodeLog.size() / 2) << " node(s).";
    return 1;
}

OmniNodeFunc l3 = printLog;

int logMemoryAddress(OmniNode ** & runner, int dummy)
{
    unsigned long m = (unsigned long) runner;
    OmniNodes::OmniNode::nodeAddressLog.push_back(m);
    return 1;
}

SuppFunc l4 = logMemoryAddress;

int removeFromLog(OmniNode ** & runner, int dummy)
{
    std::vector<unsigned long>::iterator itl;
    unsigned long m = (unsigned long) runner;
    itl = std::find(OmniNode::nodeAddressLog.begin(), OmniNode::nodeAddressLog.end(), m);
    
    if (itl < OmniNode::nodeAddressLog.end())
    {
        OmniNode::nodeAddressLog.erase(itl);
        return 1;
    }
    return -1;
}

SuppFunc l5 = removeFromLog;

int printLog(OmniNode ** & dummy, int n)
{
    int s = (int) OmniNode::nodeAddressLog.size();
    if (n == 0)
        n = s;
    std::vector<unsigned long>::iterator itl;
    std::cout << "\nContents of sequence log:";
    if (n == 0)
    {
        std::cout << "\n\t The sequence log is empty.";
        return 0;
    }
    itl = OmniNode::nodeAddressLog.begin();
    for (; itl < OmniNode::nodeAddressLog.end(); itl++)
        if (n)
        {
            std::cout << "\n\t Address: " << *itl << ".";
            n--;
        }
    std::cout << "\n  Size of log: " << (OmniNode::nodeAddressLog.size()) << " sequence(s).";
    return 1;
}

SuppFunc l6 = printLog;

int resetLog(OmniNode * & runner, int hash)
{
    if (hash == 9232)
    {
        OmniNode::nodeLog.clear();
        return hash;
    }
    return -1;
}

OmniNodeFunc l7 = resetLog;

int resetLog(OmniNode ** & runner, int hash)
{
    if (hash == 9232)
    {
        OmniNode::nodeLog.clear();
        return hash;
    }
    return -1;
}

SuppFunc l8 = resetLog;

int deallocate(OmniNode * & runner, int n)
{
    OmniNode * nextPtr = nullptr;
    if (n < 1)
        n = 0;
    if (runner == nullptr)
        return -1;
    else if (runner -> next == nullptr)
    {
        if (OmniNode::showConsoleDetailforNode)
            std::cout << "\nOmniNode friend function d1 will now deallocate memory at " << (unsigned long) runner << ".";
        if (removeFromLog(runner, runner -> value))
            delete runner;
            if (n > 1)
                return n--;
        else
            return 0;
    }
    if (n == 0)
        n = runner -> getLength();
    while (runner && n)
    {
        if (runner -> next != runner -> tail)
            nextPtr = runner -> next;
        else
            nextPtr = nullptr;
        if (OmniNode::showConsoleDetailforNode)
            std::cout << "\nOmniNode friend function d1 will now deallocate memory at " << (unsigned long) runner << ".";
        if (removeFromLog(runner, runner -> value))
        {
            delete runner;
            runner = nextPtr;
        }
        n--;
    }
    if (runner)
    {
        if (OmniNode::showConsoleDetailforNode)
            std::cout << "\nOmniNode friend function d1 has completed, leaving runner pointer in position for value " << runner -> value << ".";
    }
    else
    {
        if (OmniNode::showConsoleDetailforNode)
            std::cout << "\nOmniNode friend function d1 has completed.";
    }
    return n;
}

OmniNodeFunc d1 = deallocate;

int deallocate(OmniNode ** & runner, int dummy)
{
    if (runner == nullptr)
        return -1;
    int rv = -1;
    if (runner)
    {
        if (OmniNode::showConsoleDetailforNode)
            std::cout << "\nOmniNode friend function d2 will now deallocate memory at " << (unsigned long) runner << ".";
        rv = removeFromLog(runner, 0);
        if (rv)
        {
            delete runner;
            runner = nullptr;
        }
    }
    if (runner)
    {
        if (OmniNode::showConsoleDetailforNode)
            std::cout << "\nOmniNode friend function d2 has completed, leaving runner pointer intact at address " << (unsigned long) runner << ".";
    }
    else
    {
        if (OmniNode::showConsoleDetailforNode)
            std::cout << "\nOmniNode friend function d2 has completed.";
    }
    return rv;
}

SuppFunc d2 = deallocate;

int deallocateArray(OmniNode ** & array, int arraySize)
{
    if (array == nullptr)
        return -1;
    int rv = 0;
    OmniNodes::OmniNode ** pptr = nullptr;
    for (int i = 0; i < arraySize; i++)
    {
        pptr = array + i;
        rv += removeFromLog(pptr, 0);
        if (OmniNode::showConsoleDetailforNode)
            std::cout << "\nOmniNode friend function d3 will deallocate memory at " << (unsigned long) pptr << ".";
    }
    if (rv == arraySize)
    {
        delete [] array;
        return 1;
    }
    else
        return -1;
}

SuppFunc d3 = deallocateArray;

// OmniNodes namespace ends

}

#endif /* OmniNode_h */
