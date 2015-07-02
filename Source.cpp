#include "stdafx.h" 
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>

/*  
  Objects for playing cards game

  CardDeck -- collection of all cards
    spade[13]    --- sorted array
    diamond[13]
    hearts[13]
    clubs[13]

    -------------- Collection of objects can't be a class

    getCard()
    returnCard()

  DistributeCards
    getCard()
    giveToPlayer()

    -------------- action can't be a object

  Player
    holds cards -- sort according to type n value

  GameRule
    check available cards in a card set n match sequence according to game rule

  Play Card set
    -- collects cards as per game rule
    
  shuffle cards distribute card Throw Card / Pick Card ... moveCard
  
*/


/*
1. Investigatation on an individual card instead of a collection of cards, focus on a card's state and interface.
2. A card game has its own specific constrain and requirement on cards, such that a generic card cannot satisfy a blackjack card
3. Player manage multiple cards
*/

 
using namespace std;
 
namespace SUIT
{
    enum Enum
    {
        SPADE,
        HEART,
        CLUB,
        DIAMOND
    };
};
 
class Card
{
private:
    SUIT::Enum s;
    int v;
     
public:
    virtual SUIT::Enum suit() const
    {
        return s;
    };
     
    virtual int val() const
    {
        return v;
    };
     
    Card(int val, SUIT::Enum suit):s(suit), v(val){};
};
 
/*
Just remember and practise the paradigm of inheritance
*/
class BlackJackCard : public Card
{
public:
    virtual int val()
    {
        int v = Card::val();
        if (v < 10) return v;
        return 10;
    }
     
    BlackJackCard(int val, SUIT::Enum suit):Card(val, suit){};
};
 
class player
{
private:
    int id;
    int bet;
    set<int> points;
    vector<BlackJackCard *> bjcs;

    bool addPoint(set<int>& points, BlackJackCard* card)
    {
        if (points.empty())
        {
            points.insert(card->val());
            if (card->val() == 1)
                points.insert(11);
        }
        else
        {
            /*
            set elements are ALWAYS CONST, they can't be modified once inserted.
            */
            set<int> tmp;
            for (set<int>::iterator it = points.begin(); it != points.end(); ++ it)
            {
                tmp.insert(*it + card->val());
                if (card->val() == 1)
                    tmp.insert(*it + 11);
            }
            points = tmp;
        }

        return true;
    }
      
    void getPoints()
    {
        cout << "You All Possible Points : " << endl;
        for (set<int>::iterator it = points.begin(); it != points.end(); ++ it)
        {
            cout << *it << endl;
        }
    };
     
    int getMinPoints()
    {
        /*
        set is implemented by commonly BST, so eles are in order!!!
        learn to use lower_bound() and upper_bound()
         
        "they allow the direct iteration on subsets based on their order."
        which gives us another option to find min. preferable
        */
         
        //return *(points.lower_bound(0));
        return *(points.begin());
    };
     
    void printCards()
    {
        cout << "You Cards : " << endl;
        for (vector<BlackJackCard *>::iterator it = bjcs.begin(); it != bjcs.end(); ++ it)
        {
            cout << (*it)->val() << endl;
        }
         
    }
public:
    player(int i, int j):id(i),bet(j)
    {
        bjcs.push_back(new BlackJackCard(rand() % 13 + 1, SUIT::SPADE));
        bjcs.push_back(new BlackJackCard(rand() % 13 + 1, SUIT::SPADE));
        addPoint(points, bjcs[0]);
        addPoint(points, bjcs[1]);
    };
     
    void getAnotherCard()
    {
        for (set<int>::iterator it = points.begin(); it != points.end(); ++ it)
        {
            /*
            predefined strategy for the player
            */
            if (*it <= 21 && 21 - *it <= 4)
            {
                printCards();
                getPoints();
                cout << "Stand" << endl; 
                exit(1);
            }
        }
        bjcs.push_back(new BlackJackCard(rand() % 13 + 1, SUIT::SPADE));
        addPoint(points, bjcs.back());
        if (getMinPoints() > 21)
        {
            printCards();
            getPoints();
            cout << "Busted" << endl;
            exit(2);
        }
    };
     
    virtual ~player()
    {
        for (vector<BlackJackCard *>::iterator it = bjcs.begin(); it != bjcs.end(); ++it)
        {
            delete *it;
        }
    };
     
};
 
int main()
{
    srand(time(NULL));
    player p(1, 1000);
    p.getAnotherCard();
    p.getAnotherCard();
    p.getAnotherCard();
     
    return 0;
}


/***************************************************************/

/*

  Imagine you have a call center with three levels of employees: fresher, technical lead 
  (TL), product manager (PM). There can be multiple employees, but only one TL or PM.
  An incoming telephone call must be allocated to a fresher who is free. If a fresher 
  can’t handle the call, he or she must escalate the call to technical lead. If the TL is 
  not free or not able to handle it, then the call should be escalated to PM. Design the 
  classes and data structures for this problem. Implement a method getCallHandler().


  Objects: Employee Fresher, TL, PM, CallHandler

  ready queue of freshers who are free
  queue of TL who are free
  queue of PM who are free

  remove emp from queue whenever they are assigned some task.


  Employee getCallHandler()
  {
    get first emp from fresher queue
      assign job, dequeue emp from fresher queue

      else check for TL queue
        if not busy assign job

      else check for PM queue
        if not busy assign job
  }


*/


/***************************************************************/

/*


  Let’s first understand the basic system components:
    » CD player
    » CD
    » Display () (displays length of song, remaining time and playlist)

  Now, let’s break this down further:

    » Playlist creation (includes add, delete, shuffle etc sub functionalities)
    » CD selector
    » Track selector
    » Queueing up a song
    » Get next song from playlist

  A user also can be introduced:

    » Adding
    » Deleting
    » Credit information

*/