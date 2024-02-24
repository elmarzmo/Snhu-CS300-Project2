// C300ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Author      : Mohamed Elmarzougui

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

struct Node;
class Course {
    // private fields for a course object.
private:
    string courseId;
    string courseTitle;
    vector<string> coursePrerequisites;
    Node* root;
    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    Node* removeNode(Node* node, string courseId);
    void destroyRecursive(Node* node);




    // public methods for a course object.

public:
    Course()=default;
    Course(string id, string title, vector<string> prerequisties);
    
    string  getCourseId();
    string getCourseTitle();
    vector<string> getCoursePrerequisites();;
    void InOrder();
    void PreOrder();
    void PostOrder();
    void Insert(Course course);
    void Remove(string courseId);
    Course Search(string courseId);
    ~Course();
    string getCourseId() const;

    
};
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
    Node(Course newCourse) :
        Node() {
        course = newCourse;
    }

};

Course::~Course() {
    destroyRecursive(root);
}
void Course::destroyRecursive(Node* node) {
    // if node is not equal to nullptr
    if (node != nullptr) {
        // call for destruction of any children
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        // remove the current node
        delete node;
        node = nullptr;
    }
}
void Course::InOrder() {
    // call inOrder function and pass root
    inOrder(root);
}

void Course::PostOrder() {
    // call posOrder function and pass root
    postOrder(root);
}

void Course::PreOrder() {
    // call preOrder function and pass root
    preOrder(root);
}

void Course::Insert(Course course) {
    // if root equal to nullptr
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(root, course);
    }
}

void Course::Remove(string courseId) {
    this->removeNode(root, courseId);
}

Course Course::Search(string) {
    // convert courseID to upper case for use in comparison
    transform(courseId.begin(), courseId.end(), courseId.begin(), ::toupper);
    // set current node equal to root
    Node* cur = root;
    // keep looping downwards until bottom reached or matching courseId found
    while (cur != nullptr) {
        // if match found, return current course
        if (cur->course.getCourseId().compare(courseId) == 0) {
            return cur->course;
        }
        // if course is smaller than current node then traverse left
        else if (courseId.compare(cur->course.getCourseId()) < 0) {
            cur = cur->left;
        }
        // else larger so traverse right
        else {
            cur = cur->right;
        }
    }
    // course not found so return empty course.
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void Course::addNode(Node* node, Course course) {
    // if node is smaller than add to left
    if (node != nullptr && (node->course.getCourseId().compare(course.getCourseId()) > 0)) {
        // if there's no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
            return;
        }// else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }
    else if (node != nullptr && (node->course.getCourseId().compare(course.getCourseId()) < 0)) {
        // if there's no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
            return;
        }
        // else if node is larger than add to right
        else {
            // recurse down the right node
            this->addNode(node->right, course);
        }
    }
}


void Course::inOrder(Node* node) {
    // if node is not equal to null ptr
    if (node != nullptr) {
        // inOrder left
        inOrder(node->left);
        // output courseID and courseName
        cout << node->course.getCourseId() << ", "  << node->course.getCourseTitle() << endl;
        // inOder right
        inOrder(node->right);
    }
}

void Course::postOrder(Node* node) {
    // if node is not equal to nullptr
    if (node != nullptr) {
        // postOrder left
        postOrder(node->left);
        // postOrder right
        postOrder(node->right);
        // output courseID and courseName
        cout << node->course.getCourseId() << ", "  << node->course.getCourseTitle() << endl;
    }
}

void Course::preOrder(Node* node) {
    // if node is not equal to nullptr
    if (node != nullptr) {
        // output courseID and courseName
        cout << node->course.getCourseId() << ", " << node->course.getCourseTitle() << endl;
        // preOrder left
        preOrder(node->left);
        // preOrder right
        preOrder(node->right);
    }
}


Node* Course::removeNode(Node* node, const std::string courseId) {
    if (node == nullptr) {
        return node;
    }
    // if course is smaller than current node then traverse left
    else if (courseId.compare(node->course.getCourseId()) < 0) {
        node->left = removeNode(node->left, courseId);
    }
    // else if course is larger than current node then traverse right
    else if (courseId.compare(node->course.getCourseId()) > 0) {
        node->right = removeNode(node->right, courseId);
    }
    // else match point found
    else {
        // leaf node
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        // else if left child
        else if (node->left != nullptr && node->right == nullptr) {
            Node* tmp = node;
            node = node->left;
            delete tmp;
            tmp = nullptr;
        }
        // else if right child
        else if (node->left == nullptr && node->right != nullptr) {
            Node* tmp = node;
            node = node->right;
            delete tmp;
            tmp = nullptr;
        }
        // else both children
        else {
            // find the minimum of the right subtree nodes for bst
            Node* tmp = node;
            while (tmp->left != nullptr) {
                tmp = tmp->left;
            }
            node->course = tmp->course;
            node->right = removeNode(node->right, tmp->course.getCourseId());
        }
    }
    return node;
}



Course::Course(string id, string courseTitle, vector<string> prerequisites) {
    this->courseId = id;
    this->courseTitle = courseTitle;
    this->coursePrerequisites = prerequisites;
    root = nullptr;
}

string Course::getCourseId() {
    return this->courseId;
}

string Course::getCourseTitle() {
    return this->courseTitle;
}

vector<string>  Course::getCoursePrerequisites() {
    return this->coursePrerequisites;
}
string Course::getCourseId() const {
    return this->courseId;
}
void displayCourse(Course course) {
    vector<string> coursePrerequisites = course.getCoursePrerequisites();
    string prerequisites;
    // formats output for prerequisites, if there are any
    if (coursePrerequisites.size() == 1) {
        prerequisites = course.getCoursePrerequisites()[0];
    }
    else if (coursePrerequisites.size() > 1) {
        for (int i = 0; i < coursePrerequisites.size() - 1; i++) {
            prerequisites += coursePrerequisites[i] + ", ";
        }
        prerequisites += coursePrerequisites.back();
    }
    else {
        prerequisites = "n/a";
    }

    // prints out the course details
    cout << course.getCourseId() << ", " << course.getCourseTitle() << endl;
    cout << "Prerequisites: " << prerequisites << endl;
}
void loadCourse(string inputPath, vector<Course>& courses) {
    cout << "Loading input file " << inputPath << endl;
    // Open the file
    ifstream file(inputPath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file\n";
        return;
    }
    string currentLine;
    try {
        // Read each line from the file
        while (getline(file, currentLine)) {
            stringstream ss(currentLine);
            string word, id, title;
            vector<string> prerequisites;
            int index = 0;
            // Parse the line by commas
            while (getline(ss, word, ',')) {
                // Remove leading and trailing whitespace
                word = regex_replace(word, regex("^\\s+|\\s+$"), "");
                // Assign values based on index
                if (index == 0) {
                    id = word;
                }
                else if (index == 1) {
                    title = word;
                }
                else {
                    prerequisites.push_back(word);
                }
                index++;
            }
            Course course = Course(id, title, prerequisites);
            courses.push_back(course);
        }
    }
    catch (ifstream::failure& e) {
        cerr << "Error reading file: " << e.what() << endl;
    }
    file.close();
}

int main()
{
    Course course;
    vector<Course> courses;
    string inputPath, courseKey;
    int choice=0;
    cout << "Welcome to the course planner." << endl;
    // Display menu options
    while (choice != 9) {
        cout << "1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "9. Exit\n";
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the path to the input file:  ";
            cin.ignore(); // Clear the input buffer
            cin >> inputPath;
         //   getline(cin, inputPath); // Read the entire line
            loadCourse(inputPath, courses);

            
            break;
        case 2:
            if (courses.empty()) {
                cout << "No courses loaded. Please load courses first." << endl;
            }
            else {
                cout << "Here is a sample schedule:" << endl << endl;
                courses[0].InOrder();
            }
            break;
        case 3:
            cout << "What course do you want to know about? ";
            cin >> courseKey;
            cout << "Course key entered: " << courseKey << endl;
            {
                bool found = false;
                for (const auto& crs : courses) {
                    if (crs.getCourseId() == courseKey) {
                        displayCourse(crs);
                        found = true;
                        break;
                    }
                }
                if (!found)
                    cout << "Course Id " << courseKey << " not found." << endl;
            }
            break;
        case 9:
            cout << "Good bye." << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cout << endl;
    }
    return 0;
}
