// Project_Two-Enhanced.cpp 
// Author: Chad nadeau

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
    int height; // height of the node for balancing

    // default constructor
    Node() : left(nullptr), right(nullptr), height(1) {}

    // initialize with a course
    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

class AVLTree {
private:
    Node* root;

    int height(Node* node);
    int balanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);
    Node* insert(Node* node, Course course);
    Node* search(Node* node, string courseId);
    void inOrder(Node* node);

public:
    AVLTree();
    void insert(Course course);
    Course Search(string courseId);
    void InOrder();
};

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::height(Node* node) {
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(Node* node) {
    return height(node->left) - height(node->right);
}

Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // New root
}

Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // New root
}

Node* AVLTree::balance(Node* node) {
    // Left Left Case
    if (balanceFactor(node) > 1 && balanceFactor(node->left) >= 0)
        return rotateRight(node);
    // Right Right Case
    if (balanceFactor(node) < -1 && balanceFactor(node->right) <= 0)
        return rotateLeft(node);
    // Left Right Case
    if (balanceFactor(node) > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Right Left Case
    if (balanceFactor(node) < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node; // No balancing needed
}

Node* AVLTree::insert(Node* node, Course course) {
    if (node == nullptr)
        return new Node(course);

    if (course.courseId < node->course.courseId)
        node->left = insert(node->left, course);
    else if (course.courseId > node->course.courseId)
        node->right = insert(node->right, course);
    else // Duplicate courseId not allowed
        return node;

    // Update the height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Balance the node
    return balance(node);
}

void AVLTree::insert(Course course) {
    root = insert(root, course);
}

Course AVLTree::Search(string courseId) {
    Node* resultNode = search(root, courseId);
    return resultNode ? resultNode->course : Course(); // Return empty Course if not found
}

Node* AVLTree::search(Node* node, string courseId) {
    if (node == nullptr || node->course.courseId == courseId)
        return node;

    if (courseId < node->course.courseId)
        return search(node->left, courseId);
    else
        return search(node->right, courseId);
}

void AVLTree::InOrder() {
    inOrder(root);
}

void AVLTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseId << ", " << node->course.courseName << ", " << node->course.prerequisite << endl;
        inOrder(node->right);
    }
}

// open file using fstream
void openFile(std::string fileName, AVLTree* avlTree) {
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::cout << "File: " << fileName << ", has been loaded successfully" << std::endl;
        std::string line;
        std::getline(file, line); 

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string courseId, courseName, prerequisite;
            std::getline(ss, courseId, ',');
            std::getline(ss, courseName, ',');
            std::getline(ss, prerequisite, ',');

            Course course = { courseId, courseName, prerequisite };
            avlTree->insert(course);
        }

        file.close();
    }
    else {
        std::cout << "File: " << fileName << ", failed to load successfully" << std::endl;
    }
}

int main() {
    std::string file;

    // AVL tree to hold all courses
    AVLTree* avlTree = new AVLTree();
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
            openFile(file, avlTree);
            break;

        case 2:
            std::cout << "Here are all the courses that were found: " << std::endl;
            std::cout << std::endl;
            avlTree->InOrder();
            std::cout << std::endl;
            break;

        case 3:           
            std::cout << "What course would you like to look up? ";
            std::cin >> course.courseId;

            course = avlTree->Search(course.courseId);
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

    delete avlTree; // Clean up memory
    return 0;
}