// Project_Two.cpp 
// Author : Chad nadeau
// 7-1 Project Two

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// defines structure to hold course information
struct Course {
    string courseId; // unique course identifier
    string courseName; // description of course
    string prerequisite; // prerequisites for course
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }

    // copy constructor
    Node(const Node& otherNode) {
        course = otherNode.course;
        left = otherNode.left;
        right = otherNode.right;
    }
};

class BinarySearchTree {

private:
    Node* root;

    void inOrder(Node* node);

public:
    BinarySearchTree();
    void InOrder();
    Course Search(string courseId);
    void insert(Course course);
};

BinarySearchTree::BinarySearchTree() {

    root = nullptr;
}

void BinarySearchTree::InOrder() {

    inOrder(root);
}

// in order traversal of all courses
void BinarySearchTree::inOrder(Node* node) {

    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseId << ", " << node->course.courseName << ", " << node->course.prerequisite << endl;
        inOrder(node->right);
    }
}

// display all courses delineated by a comma
void displayCourse(Course course) {
    cout << course.courseId << ", " << course.courseName << ", " << course.prerequisite << endl;
    return;
}

// function to search through tree for specified course
Course BinarySearchTree::Search(string courseId) {

    Node* curNode = root;

    while (curNode != nullptr) {
        if (curNode->course.courseId.compare(courseId) == 0) {
            return curNode->course;
        }
        else if (courseId.compare(curNode->course.courseId) < 0) {
            curNode = curNode->left;
        }
        else {
            curNode = curNode->right;
        }
    }

    Course course;
    return course;
}

// insert function to insert each course that is parsed into the tree
void BinarySearchTree::insert(Course course) {
    Node* newNode = new Node(course);
    if (root == nullptr) {
        root = newNode;
    }
    else {
        Node* curNode = root;
        while (true) {
            if (newNode->course.courseId < curNode->course.courseId) {
                if (curNode->left == nullptr) {
                    curNode->left = newNode;
                    break;
                }
                else {
                    curNode = curNode->left;
                }
            }
            else if (newNode->course.courseId > curNode->course.courseId) {
                if (curNode->right == nullptr) {
                    curNode->right = newNode;
 
                    break;
                }
                else {
                    curNode = curNode->right;
                }
            }
            else {                
                delete newNode;
                break;
            }
        }
    }
}
// open file using fstream
void openFile(std::string fileName, BinarySearchTree* bst) {
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::cout << "File: " << fileName << ", has been loaded succesfully" << std::endl;
        std::string line;
        std::getline(file, line); 

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string courseId, courseName, prerequisite;
            std::getline(ss, courseId, ',');
            std::getline(ss, courseName, ',');
            std::getline(ss, prerequisite, ',');

            Course course = { courseId, courseName, prerequisite };
            bst->insert(course);
        }

        file.close();
    }
    else {
        std::cout << "File: " << fileName << ", failed to load successfully" << std::endl;
    }
}

int main() {

    std::string file;

    // binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    while (choice != 4) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Load Data Structure" << std::endl;
        std::cout << "2. Print Course List" << std::endl;
        std::cout << "3. Print Course" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cin >> choice;

        switch (choice) {

        case 1:
            std::cout << "What is the file you would like to load? ";
            std::cin >> file;
            openFile(file, bst);
            break;

        case 2:
            std::cout << "Here are all the courses that were found: " << std::endl;
            std::cout << std::endl;
            bst->InOrder();
            std::cout << std::endl;
            break;

        case 3:           
            std::cout << "What course would you like to look up? ";
            std::cin >> course.courseId;

            for (auto& c : course.courseId) {
                c = std::toupper(c);
            }

            course = bst->Search(course.courseId);
            if (course.courseId.empty()) {
                std::cout << "Course not found." << std::endl;
            }
            else {
                std::cout << "Course: " << course.courseId << ", " << course.courseName << std::endl;
                std::cout << "Prerequisite: " << course.prerequisite << std::endl;
            }
            break;

        case 4:
            std::cout << "Goodbye." << std::endl;
            break;

        default:
            std::cout << "Invalid selection, please make another selection from the menu." << std::endl;
            break;
        }
    }

    return 0;

}