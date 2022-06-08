#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <utility>
#include <cstdlib>
#include <array>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std; // bank_account

struct TrieNode
{
  unordered_map<char, TrieNode *> child;
  bool isLast;

  TrieNode()
  {
    for (char i = 'a'; i <= 'z'; i++)
    {
      child[i] = NULL;
    }
    isLast = false;
  }
};

TrieNode *root = NULL;

void insert(string s)
{
  int len = s.length();

  TrieNode *itr = root;
  for (int i = 0; i < len; i++)
  {
    TrieNode *nextNode = itr->child[s[i]];
    if (nextNode == NULL)
    {
      nextNode = new TrieNode();
      itr->child[s[i]] = nextNode;
    }

    itr = nextNode;

    if (i == len - 1)
      itr->isLast = true;
  }
}

void displayContactsUntil(TrieNode *curNode, string prefix)
{
  if (curNode->isLast)
    cout << prefix << endl;

  for (char i = 'a'; i <= 'z'; i++)
  {
    TrieNode *nextNode = curNode->child[i];
    if (nextNode != NULL)
      displayContactsUntil(nextNode, prefix + (char)i);
  }
}

void displayContacts(string str)
{
  TrieNode *prevNode = root;
  string prefix = "";
  int len = str.length();

  int i;
  for (i = 0; i < len; i++)
  {
    prefix += (char)str[i];
    char lastChar = prefix[i];

    TrieNode *curNode = prevNode->child[lastChar];

    if (curNode == NULL)
    {
      cout << "No results found for " << prefix << endl;
      i++;
      break;
    }

    cout << "Suggestions based on " << prefix << " are:" << endl;
    displayContactsUntil(curNode, prefix);
    prevNode = curNode;
  }

  for (; i < len; i++)
  {
    prefix += (char)str[i];
    cout << "No results found for " << prefix << endl;
  }
}

void insertIntoTrie(string contact)
{
  if (root == NULL)
  {
    cout << "hey" << endl;
    root = new TrieNode();
  }
  insert(contact);
}

int main()
{

  cout << "********** MENU **********" << endl;
  cout << "<1. Find contact> <2. Add contact> <3. Exit>" << endl;
  char x;
  cin >> x;

  while (x != '3')
  {
    switch (x)
    {
    case '1':
    {
      cout << "Enter the name of contact to find: ";
      string contact_to_find;
      cin >> contact_to_find;
      displayContacts(contact_to_find);
      break;
    }
    case '2':
    {
      cout << "Enter the name of contact to add: ";
      string contact_to_add;
      cin >> contact_to_add;
      insertIntoTrie(contact_to_add);
      break;
    }
    }
    cout << "********** MENU **********" << endl;
    cout << "<1. Find contact> <2. Add contact> <3. Exit>" << endl;
    cin >> x;
  }
}
