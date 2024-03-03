//============================================================================
// Name        : ABCUBinarySearchTree.cpp
// Author      : July Wellman
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

//Construct the Course
struct Course {
    string courseId;
    string courseName;
    vector<string> preRequisite;
};
//Construst the left and right nodes for the tree
struct Node {
    Course course;
    Node* left;
    Node* right;
    //Set left and right nodes to a null pointer
    Node() {
        left = nullptr;
        right = nullptr;
    }
    //initialize aCourse to the node
    Node(Course aCourse) : Node() {
        this->course = aCourse;
    }
};
//Create a class for the binary search tree
class BinarySearchTree {
private:
    //Create a destruct
    void Destruct(Node* node);
public:
    Node* root;
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(BinarySearchTree* tree, Node* node);
    void Search(string courseId);
    void PrintCourse(Node* node);
};
//Set the root to the null pointer
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
};
//delete the root
BinarySearchTree::~BinarySearchTree() {
    Destruct(root);
};
//delete the left and right nodes
void BinarySearchTree::Destruct(Node* node) {
    if (node != nullptr) {
        Destruct(node->left);
        node->left = nullptr;
        Destruct(node->right);
        node->right = nullptr;
        delete node;
    }
};
//search for a course
void BinarySearchTree::Search(string courseId) {
    Node* currentNode = root;
    //While the current node is not empty
    while (currentNode != nullptr) {
        //if the current course id on the current node equals the courseId input
        if (currentNode->course.courseId == courseId) {
            //prints course id, name
            cout << currentNode->course.courseId << ", ";
            cout << currentNode->course.courseName;
            cout << endl;
            cout << "Prerequisites: ";
            //prints all prerequisites, followed by a "," if there are more than one prerequisite
            for (string preRequisite : currentNode->course.preRequisite) {
                if (preRequisite == currentNode->course.preRequisite.back()) {
                    cout << preRequisite << endl;
                }
                else {
                    cout << preRequisite << ", ";
                }
            }
            return;
        }
        //else if the courseId is less than the current node course Id
        else if (courseId < currentNode->course.courseId) {
            //if the left node from the current node is not empty
            if (currentNode->left != nullptr) {
                //Move to the left node
                currentNode = currentNode->left;
            }
        }
        //else move the current node to the right
        else {
            currentNode = currentNode->right;
        }
    }
    //course Id is not in the list
    cout << "Course " << courseId << " not found. " << endl;
    return;
}

//inserts courses into a Binary Search Tree
void BinarySearchTree::Insert(BinarySearchTree* tree, Node* node) {
    //if root of tree is the null pointer
    if (tree->root == nullptr) {
        //root of tree is equal to the node
        tree->root = node;
    }
    //else the current node is the root
    else {
        Node* curr = tree->root;
        //while the current node is empty
        while (curr != nullptr) {
            //if the course Id is less than the current course Id
            if (node->course.courseId < curr->course.courseId) {
                //if the left node is empty
                if (curr->left == nullptr) {
                    //left is equal to node
                    curr->left = node;
                    //current is now empty
                    curr = nullptr;
                }
                //else the current node moves to the left
                else {
                    curr = curr->left;
                }
            }
            //else
            else {
                //if the right is empty
                if (curr->right == nullptr) {
                    //right is equal to node
                    curr->right = node;
                    //current node is now empty
                    curr = nullptr;
                }
                //else the current node moves to the right
                else {
                    curr = curr->right;
                }
            }
        }
    }
}
//prints course list
void BinarySearchTree::PrintCourse(Node* node) {
    //if node is empty
    if (node == nullptr) {
        //return empty
        return;
    }
    //print the course information for the node on the left
    PrintCourse(node->left);
    //print the course Id with a ", "
    cout << node->course.courseId << ", ";
    //print the course name and end the line
    cout << node->course.courseName << endl;
    //print the course information for the node on the right
    PrintCourse(node->right);
};
//loads file and creates the course list
void loadCourse(string filename, BinarySearchTree* bst) {
    ifstream file(filename);
    //if the file is open
    if (file.is_open()) {
        //print confirmation
        cout << "File has succesfully uploaded." << endl;
        int num;
        string line;
        string word;
        //while reading rech line
        while (getline(file, line)) {
            num = 0;
            //point the pointer to the new node
            Node* node = new Node();
            stringstream str(line);
            //while the number of parse lines is less than two
            while (num < 2) {
                //seperate with a ","
                getline(str, word, ',');
                //if the num is equal to 0
                if (num == 0) {
                    //node course Id is equal to word
                    node->course.courseId = word;
                }
                //else
                else {
                    //node course name is equal to word
                    node->course.courseName = word;
                }
                //increment num
                num++;
            }
            //while reading with ","
            while (getline(str, word, ',')) {
                //push back course prerequisite
                node->course.preRequisite.push_back(word);
            }
            //insert node into bst
            bst->Insert(bst, node);
        }
    }
    //file error if file not found
    else {
        cout << "Error file was not successfully uploaded, please try again. " << endl;
        return;
    }
}

//Create and display the menu
void DisplayMenu() {
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "9. Exit" << endl << endl;
    cout << "Please make a selection from the list: ";
}

//Main Menu Functions
void main() {
    BinarySearchTree* bst = new BinarySearchTree();
    string fileChoice;
    string courseChoice;
    //set user input to equal zero
    int userInput = 0;
    //Print an Welcome message
    cout << "**************************************" << endl;
    cout << "* Welcome to the ABCU Course Planner *" << endl;
    cout << "**************************************" << endl << endl;
    //while userInput is not equal to 9
    while (userInput != 9) {
        //Display the menu
        DisplayMenu();
        //take the user input
        cin >> userInput;

        switch (userInput) {
            //loads file that user chooses
        case 1:
            cout << "***********************" << endl;
            cout << "* Load Data Structure *" << endl;
            cout << "***********************" << endl << endl;
            cout << "*Note: Default file is CourseInformation.csv*" << endl;
            cout << "Please enter the name of the file you would like to load: ";
            cin >> fileChoice;
            loadCourse(fileChoice, bst);
            cout << endl;
            break;
            //prints courses in alphanumeric order
        case 2:
            cout << endl;
            cout << "***************************" << endl;
            cout << "* COURSE ID | COURSE NAME *" << endl;
            cout << "***************************" << endl;
            //prints course starting at root   	
            bst->PrintCourse(bst->root);
            cout << endl;
            break;
            //prints course that user chooses and any prerequisites
        case 3:
            cout << endl;
            cout << "Please enter the Course ID: ";
            cin >> courseChoice;
            cout << endl;
            std::transform(courseChoice.begin(), courseChoice.end(), courseChoice.begin(), ::toupper);
            bst->Search(courseChoice);
            cout << endl;
            break;
            //exits the program
        case 9:
            cout << "Thank you for using the ABCU Course Planner!" << endl;
            break;
            //default message if one of the above choices is not entered
        default:
            cout << userInput << " is not a valid option." << endl << endl;
            break;
        }
    }
}