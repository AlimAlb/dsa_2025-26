#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <stdexcept>

using namespace std;

class Queue {
 public:
  void push(int elem) {
    int min_val;
    if(pushStack_.empty())
      min_val = elem;
    else
      min_val = min(elem, pushStack_.top().currentMin);
    pushStack_.push({elem, min_val});
  }

  int pop() {
    is_empty();
    if (popStack_.empty()) {
      push2pop();
    }
    int val = popStack_.top().value;
    popStack_.pop();
    return val;
  }

  int& front() {
    is_empty();
    if (popStack_.empty()) {
      push2pop();
    }
    return popStack_.top().value;
  }

  int& back() {
    is_empty();
    if (pushStack_.empty()) {
      pop2push();
    }
    return pushStack_.top().value;
  }

  int currentMin() {
    if (empty()) {
      throw runtime_error("Queue is empty");
    }

    if (!pushStack_.empty() && !popStack_.empty()) {
      return min(pushStack_.top().currentMin, popStack_.top().currentMin);
    }
    else if (pushStack_.empty()){
      return popStack_.top().currentMin;
    } else {
      return pushStack_.top().currentMin;
    }
  }

  bool empty() const { return pushStack_.empty() && popStack_.empty(); }

 private:
  struct Node {
    int value;
    int currentMin;
  };

  void is_empty() const {
    if (empty()) {
      throw runtime_error("Queue is empty");
    }
  }

  void push2pop() {
    while (!pushStack_.empty()) {
      int value = pushStack_.top().value;
      pushStack_.pop();
      int minVal;
      if(popStack_.empty()){
        minVal = value;
      } 
      else{
        minVal = min(value, popStack_.top().currentMin);
      }
      popStack_.push({value, minVal});
    }
  }

  void pop2push() {
    while (!popStack_.empty()) {
      int value = popStack_.top().value;
      popStack_.pop();
      int minVal;
      if(pushStack_.empty())
        minVal = value;
      else
        minVal = pushStack_.top().currentMin;
      pushStack_.push({value, minVal});
    }
  }

  stack<Node> pushStack_;
  stack<Node> popStack_;
};



void io_test() {
  Queue q;
  q.push(1);
  q.push(2);
  q.push(3);

  assert(q.front() == 1);
  assert(q.back() == 3);
  assert(q.currentMin() == 1);

  assert(q.pop() == 1);
  assert(q.front() == 2);
  assert(q.back() == 3);
  assert(q.currentMin() == 2);
}

void test_of_min() {
  Queue q;
  q.push(5);
  q.push(3);
  q.push(7);
  q.push(2);

  assert(q.currentMin() == 2);
  q.pop();  // remove 5
  assert(q.currentMin() == 2);
  q.pop();  // remove 3
  assert(q.currentMin() == 2);
  q.pop();  // remove 7
  assert(q.currentMin() == 2);
  q.pop();  // remove 2
  assert(q.empty());

  bool threw = false;
  try {
    q.currentMin();
  } catch (const std::runtime_error&) {
    threw = true;
  }
  assert(threw);
}

void test_of_ref() {
  Queue q;
  q.push(10);
  int& f = q.front();
  assert(f == 10);
  assert(q.back() == 10);

  q.push(9);
  int& b = q.back();
  assert(b == 9);
  assert(f == 10);
  assert(q.currentMin() == 9);
} 

int main() {
  io_test();
  test_of_min();
  test_of_ref();

  std::cout << "All tests passed\n";
  return 0;
}
