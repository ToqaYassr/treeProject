#include"student_class.cpp"

///binary search tree structure///

class BST {
//    a node struct that represents a node in the BST
    struct node {
        int key;
        student data;
        node *left;
        node *right;

//        constructor to initialize the node
        node(int key, student data) {
            this->key = key;
            this->data = data;
            left = NULL;
            right = NULL;
        }
    };

    node *root = NULL;
    int num_of_nodes = 0;

//// HELPER FUNCTIONS ////
//   a function that inserts a value in the BST using recursion
    void insertHelper(node *root, int value, student data) {

        //  if the value is less than the root go to the left
        if (value < root->key) {
            if (root->left == NULL) {
                root->left = new node(value, data);
            } else {
                insertHelper(root->left, value, data);

            }
        }

//       else if the value is greater than the root go to the right
        else if (value > root->key) {
            if (root->right == NULL) {
                root->right = new node(value, data);
            } else {
                insertHelper(root->right, value, data);
            }
        }
    }

    //    function search using recursion
    node *searchHelper(node *root, int value) {
        if (root == NULL) {
            student s(-1, "not found", -1, "not found");
            root = new node(-1, s);
            return root;
        }
//        if the value is equal to the root return true
        else if (value == root->key) {
            return root;
        }
//        if the value is less than the root go to the left
        else if (value < root->key) {
            return searchHelper(root->left, value);
        }
//        if the value is greater than the root go to the right
        else {
            return searchHelper(root->right, value);
        }
    }

    //    a function to print the tree in order using recursion
    void printInOrderHelper(node *root) {
        if (root == NULL) {
            return;
        }
        printInOrderHelper(root->left);// print the left subtree
        root->data.print();// print the root
        printInOrderHelper(root->right);// print the right subtree
    }

// function to find the minimum value node in a subtree
    node *findMinNode(node *root) {
        if (root == NULL) {
            return NULL;
        } else if (root->left == NULL) {
            return root;
        } else {
            return findMinNode(root->left);
        }
    }

// function to delete a node from the BST
    node *deleteHelper(node *root, int value) {
        if (root == NULL) {
            return NULL;
        }
        if (value < root->key) {
            root->left = deleteHelper(root->left, value);
        } else if (value > root->key) {
            root->right = deleteHelper(root->right, value);
        } else {
            if (root->left == NULL && root->right == NULL) {
                delete root;
                root = NULL;
            } else if (root->left == NULL) {
                node *temp = root;
                root = root->right;
                delete temp;
            } else if (root->right == NULL) {
                node *temp = root;
                root = root->left;
                delete temp;
            } else {
                node *temp = findMinNode(root->right);
                root->key = temp->key;
                root->right = deleteHelper(root->right, temp->key);
            }
        }
        return root;
    }

public:
// returns the number of nodes in the tree
    int size() {
        return num_of_nodes;
    }

////    tree functions using recursion section:
//    insert function that calls the insertHelper function
    void insertRec(int value, student data) {

//  if the tree is empty make the new node the root
        if (root == NULL) {
            root = new node(value, data);
        }
//  else call the insertHelper function
        else {
            insertHelper(root, value, data);
            num_of_nodes++;
        }
    }

//    a function to insert a value in the BST using recursion
    student searchRec(int value) {
        return searchHelper(root, value)->data;
    }

    void deleteRec(int value) {
        deleteHelper(root, value);
    }

//    a function to print the tree in order using recursion
    void printInOrderRecursive() {
        printInOrderHelper(root);
    }

};



///AVL tree structure///
class AVL {
//    a node struct that represents a node in the BST
    struct node {
        int height;
        int key;
        student data;
        node *left;
        node *right;

//        constructor to initialize the node
        node(int id, student s) {
            this->height = 1;
            this->key = id;
            this->data = s;
            left = NULL;
            right = NULL;
        }
    };

    int height(node *N) {
        if (N == NULL)
            return 0;
        return N->height;
    }

    // Rotate right
    node *rightRotate(node *y) {
        node *x = y->left;
        node *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left),
                        height(y->right)) + 1;
        x->height = max(height(x->left),
                        height(x->right)) + 1;
        return x;
    }

// Rotate left
    node *leftRotate(node *x) {
        node *y = x->right;
        node *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left),
                        height(x->right)) + 1;
        y->height = max(height(y->left),
                        height(y->right)) + 1;
        return y;
    }

// Get the balance factor of each node
    int getBalanceFactor(node *N) {
        if (N == NULL)
            return 0;
        return height(N->left) -
               height(N->right);
    }

    node *root = NULL;
    int num_of_nodes = 0;

//// HELPER FUNCTIONS ////


//    function that finds the minimum value in the BST
    node *findMin(node *root) {
        if (root == NULL) {
            return NULL;
        }
        if (root->left != NULL) {
            return findMin(root->left);
        }
        return root;
    }

// a function that deletes a value from the AVL tree using recursion
    void deleteHelper(node *&root, int value) {
        // base case: if root is null, the value is not in the tree
        if (root == NULL) {
            return;
        }

        // if the value is less than the root, delete from the left subtree
        if (value < root->key) {
            deleteHelper(root->left, value);
        }

            // if the value is greater than the root, delete from the right subtree
        else if (value > root->key) {
            deleteHelper(root->right, value);
        }

            // if the value is found in the root, delete it
        else {
            // case 1: node has no children
            if (root->left == NULL && root->right == NULL) {
                delete root;
                root = NULL;
            }

                // case 2: node has one child
            else if (root->left == NULL) {
                node *temp = root;
                root = root->right;
                delete temp;
            } else if (root->right == NULL) {
                node *temp = root;
                root = root->left;
                delete temp;
            }

                // case 3: node has two children
            else {
                // find the minimum value in the right subtree
                node *temp = findMin(root->right);
                root->key = temp->key;
                deleteHelper(root->right, temp->key);
            }
        }

        // check and balance the AVL tree
        if (root != NULL) {
            int bf = getBalanceFactor(root);

            // Left Left Case
            if (bf > 1 && getBalanceFactor(root->left) >= 0) {
                rightRotate(root);
            }

            // Right Right Case
            if (bf < -1 && getBalanceFactor(root->right) <= 0) {
                leftRotate(root);
            }

            // Left Right Case
            if (bf > 1 && getBalanceFactor(root->left) < 0) {
                root->left = leftRotate(root->left);
                rightRotate(root);
            }

            // Right Left Case
            if (bf < -1 && getBalanceFactor(root->right) > 0) {
                root->right = rightRotate(root->right);
                leftRotate(root);
            }
        }
    }

    //    function search using recursion
    node *searchHelper(node *root, int value) {
        if (root == NULL) {
            student s(-1, "not found", -1, "not found");
            root = new node(-1, s);
            return root;
        }
//        if the value is equal to the root return true
        else if (value == root->key) {
            return root;
        }
//        if the value is less than the root go to the left
        else if (value < root->key) {
            return searchHelper(root->left, value);
        }
//        if the value is greater than the root go to the right
        else {
            return searchHelper(root->right, value);
        }
    }


    // a function that inserts a value in the BST using recursion
    void insertHelper(node *root, int value, student s) {


        // if the value is less than the root go to the left
        if (value < root->key) {
            if (root->left == NULL) {
                root->left = new node(value, s);
            } else {
                insertHelper(root->left, value, s);
            }
        }

            // if the value is greater than the root go to the right
        else if (value > root->key) {
            if (root->right == NULL) {
                root->right = new node(value, s);
            } else {
                insertHelper(root->right, value, s);
            }
        }

        // perform balance factor checks and rotations after insertion
        int bf = getBalanceFactor(root);

        // Left Left Case
        if (bf > 1 && value < root->left->key)
            rightRotate(root);

        // Right Right Case
        if (bf < -1 && value > root->right->key)
            leftRotate(root);

        // Left Right Case
        if (bf > 1 && value > root->left->key) {
            root->left = leftRotate(root->left);
            rightRotate(root);
        }

        // Right Left Case
        if (bf < -1 && value < root->right->key) {
            root->right = rightRotate(root->right);
            leftRotate(root);
        }

    }


    //    a function to print the tree in order using recursion
    void printInOrderHelper(node *root) {
        if (root == NULL) {
            return;
        }
        printInOrderHelper(root->left);// print the left subtree

        root->data.print();

        printInOrderHelper(root->right);// print the right subtree
    }

public:


//    a function to insert a value in the BST using recursion
    void insertRec(int value, student s) {
        if (root == NULL) {
            root = new node(value, s);
        }
        else {
            insertHelper(root, value, s);
        }
        num_of_nodes++;
    }


//    a function to search a value in the BST using recursion
    student searchRec(int value) {
        return searchHelper(root, value)->data;
    }

//    a function to delete a value from the BST using recursion
    void deleteRec(int value) {
        deleteHelper(root, value);
        num_of_nodes--;
    }

//    a function to print the tree in order using recursion
    void printInOrderRecursive() {
        printInOrderHelper(root);
    }


};


///Min heap structure///

class MinHeap {
    student *arr;
    int size;
    int capacity;

    // Recursive function to maintain the heap property
    void heapify(student arr[], int arr_size, int index) {
        int smallest = index;
        int left = 2 * index + 1; // Left child
        int right = 2 * index + 2; // Right child

        // Compare the left child with the current smallest
        if (left < arr_size && arr[left].getId() < arr[smallest].getId()) {
            smallest = left;
        }

        // Compare the right child with the current smallest
        if (right < arr_size && arr[right].getId() < arr[smallest].getId()) {
            smallest = right;
        }

        // If the smallest value is not the current index, swap and recursively heapify
        if (smallest != index) {
            swap(arr[index], arr[smallest]);
            heapify(arr, arr_size, smallest);
        }
    }

    // Build heap (rearrange the array)
    void buildHeap(student arr[], int arr_size) {
        // Check every level of the tree (array)
        for (int i = arr_size / 2 - 1; i >= 0; i--) {
            heapify(arr, arr_size, i);
        }
    }

    // Sort the heap in ascending order
    void sortHeap(student arr[], int arr_size) {
        buildHeap(arr, arr_size);

        // One by one extract an element from the heap
        for (int i = arr_size - 1; i >= 0; i--) {
            // Move the current root to the end
            swap(arr[0], arr[i]);
            // Call heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }

public:
    // Constructor
    MinHeap() {
        capacity = 1;
        arr = new student[capacity];
        size = 0;
    }

    // Search for a student with a given ID
    student search(int id) {
        for (int i = 0; i < size; i++) {
            if (id == arr[i].getId()) {
                return arr[i];
            }
        }
        // Return a student object indicating "not found"
        student s(-1, "not found", -1, "not found");
        return s;
    }

    // Delete a student with a given ID from the heap
    void deleteMinHeap(int id) {
        for (int i = 0; i < size; i++) {
            if (arr[i].getId() == id) {
                arr[i] = arr[size - 1];
                size--;
                buildHeap(arr, size);
                sortHeap(arr, size);
                break;
            }
        }
    }

    // Insert a new element into the heap
    void insert(student s) {
        if (size == capacity) {
            student *temp = new student[2 * capacity];
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
            capacity *= 2;
        }
        arr[size] = s;
        size++;
        buildHeap(arr, size);
        sortHeap(arr, size);
    }

    // Print the elements of the heap
    void printHeap() {
        // Print the elements of the heap
        for (int i = 0; i < size; i++) {
            arr[i].print();
            if (i != size - 1) {
                cout << endl;
            }
        }
    }
};




///Max heap structure///

class MaxHeap {
    student *arr;
    int size;
    int capacity;

    void heapify(student arr[] , int arrs_ize, int index ){
        int largest = index;// initialize largest as root to start with
        int left = 2*index + 1;// left child
        int right = 2*index + 2; // right child


//  check if left child is larger than root
//  if so make it the largest
        if(left < arrs_ize && arr[left].getId() >  arr[largest].getId()){
            largest = left;
        }

//    check if right child is larger than root
//    if so make it the largest
        if(right < arrs_ize && arr[right].getId() > arr[largest].getId()){
            largest = right;
        }

//    if largest is not root
//  to make sure that the root is the largest
//  among the root and its children
        if(largest != index){
//        swap the root with the largest
            swap(arr[index], arr[largest]);
//  recursively heapify the affected sub-tree
            heapify(arr, arrs_ize, largest);
        }

    }

//    build heap (rearrange array)

    void buildHeap(student arr[], int arr_size){
//    check every level of the tree(array)
//     if it follows the max heap property
        for(int i = arr_size/2 - 1; i >= 0; i--){
            heapify(arr, arr_size, i);
        }
    }


    void sortHeap(student arr[], int arr_size){
//    build a max heap
        buildHeap(arr, arr_size);

//    one by one extract an element from heap
        for(int i = arr_size - 1; i >= 0; i--){
//        move current root to end
            swap(arr[0], arr[i]);
//        call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }

public:

    MaxHeap(){
        capacity=1;
        arr = new student[capacity];
        size = 0;

    }

    student search(int id){

        for(int i=0;i<size;i++){
            if(id==arr[i].getId()){
                return arr[i];
            }
        }

        student s(-1, "not found", -1, "not found");
        return s;

    }

    void deleteMaxHeap(int id){
        for (int i = 0; i < size; i++) {
            if (arr[i].getId() == id) {
                arr[i] = arr[size - 1];
                size--;
                buildHeap(arr, size);
                sortHeap(arr, size);
                break;
            }


        }
        buildHeap(arr,size);
        sortHeap(arr,size);
    }

    // function to insert a new element into the heap
    void insert(student s){
        if(size == capacity){
            student *temp = new student[2*capacity];
            for(int i = 0; i < capacity; i++){
                temp[i] = arr[i];
            }

            delete[] arr;
            arr = temp;
            capacity *= 2;

        }

        arr[size] = s;
        size++;

        buildHeap(arr,size);
        sortHeap(arr,size);
    }

// function to print an array
    void printHeap(){
        for(int i = 0; i <size; i++){
            arr[i].print();
            if(i != size - 1){
                cout << endl;
            }
        }
    }


};


