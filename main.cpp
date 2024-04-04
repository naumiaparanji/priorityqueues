#include "ArgumentManager.h"
#include "Linkedlist.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
struct door {
  bool isOpen;
  bool isLocked;
  door() : isOpen(false), isLocked(false) {}
};

bool isValidLine(string input) {
  if (input.find('(') == 0 || input.find(')') == 0)
    return false;
  if (input.find('(') == -1 || input.find(')') == -1)
    return false;
  if (input.find("open the door") == -1 && input.find("close the door") == -1 &&
      input.find("lock the door") == -1 && input.find("unlock the door") == -1)
    return false;
  return true;
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string inputfilename = am.get("input");
  string outputfilename = am.get("output");
  ifstream ifs(inputfilename);
  ofstream ofs(outputfilename);

  string inputline;
  Linkedlist pqueue;
  while (getline(ifs, inputline)) {
    inputline.erase(remove(inputline.begin(), inputline.end(), '\n'),
                    inputline.end());
    inputline.erase(remove(inputline.begin(), inputline.end(), '\r'),
                    inputline.end());
    if (inputline.empty())
      continue;
    if (isValidLine(inputline)) {
      string instruction = inputline.substr(0, inputline.find('('));
      int priority =
          stoi(inputline.substr(inputline.find('(') + 1,
                                inputline.find(')') - inputline.find('(') - 1));
      pqueue.insertPosition(priority, instruction);
    }
  }
  pqueue.print();
  door door;
  door.isLocked = false;
  door.isOpen = false;
  while (!pqueue.isEmpty()) {
    string instructionToProcess = pqueue.getHead();
    if (door.isLocked) {
      if (instructionToProcess.find("unlock") != -1) {
        door.isLocked = false;
      }
    } else if (!door.isLocked) {
      if (instructionToProcess.find("unlock") == 0)
        door.isLocked = false;
      else if (instructionToProcess.find("lock") == 0)
        door.isLocked = true;
      else if (instructionToProcess.find("open") == 0)
        door.isOpen = true;
      else if (instructionToProcess.find("close") == 0)
        door.isOpen = false;
    }
    pqueue.removeHead();
    cout << "for instruction: " << instructionToProcess << endl;
    cout << "closed: " << door.isOpen << endl;
    cout << "locked: " << door.isLocked << endl;
    cout << endl;
  }
  if (door.isOpen) {
    // cout << "the door is open";
    ofs << "the door is open";
  } else {
    // cout << "the door is closed";
    ofs << "the door is closed";
  }
  ifs.close();
  ofs.close();
  return 0;
}