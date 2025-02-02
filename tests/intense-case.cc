#include <iostream>
#include <string>
#include <vector>


struct Person {
  std::string name;
  int age;

  void printInfo() const {
    std::cout << "Name: " << name << ", Age: " << age << std::endl;
  }
};


int add(int a, int b);
void printVector(const std::vector<int> &vec);


int main() {
  
  int x = 10;
  int y = 20;
  int sum = add(x, y);

  
  if (sum > 25) {
    std::cout << "Sum is greater than 25" << std::endl;
  } else {
    std::cout << "Sum is less than or equal to 25" << std::endl;
  }

  
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  printVector(numbers);

  
  Person person;
  person.name = "Alice";
  person.age = 30;
  person.printInfo();

  return 0;
}


int add(int a, int b) { return a + b; }


void printVector(const std::vector<int> &vec) {
  for (int num : vec) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}
