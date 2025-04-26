#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>

struct Node {
	int key;
	int height;
	Node* left;
	Node* right;
	Node* parent;
	bool lowestOne;
	bool toDelete;

	Node(int val, Node* father) : key(val), height(0), left(nullptr), right(nullptr), parent(father), lowestOne(false), toDelete(false) {}
};

int longestWay = -1;
Node* maxRoot = nullptr;
Node* top = nullptr;

int heights(Node* root) {
	if (root == nullptr) {
		return -1;
	}

	int leftHeight = heights(root->left);
	int rightHeight = heights(root->right);

	int isMaxRoot;
	if (root->left == nullptr && root->right == nullptr) {
		isMaxRoot = 0;
	}
	else if (root->left != nullptr && root->right != nullptr) {
		isMaxRoot = root->left->height + root->right->height + 2;
	}
	else {
		isMaxRoot = (root->left != nullptr ? root->left->height : root->right->height) + 1;
	}

	if (isMaxRoot > longestWay) {
		longestWay = isMaxRoot;
		maxRoot = root;
	}
	else if (isMaxRoot == longestWay) {
		maxRoot->lowestOne = true;
	}

	return root->height = std::max(leftHeight, rightHeight) + 1;
}

void defineNodesToDelete(Node* root) {
	while (true) {
		root->toDelete = true;
		if (root->left == nullptr && root->right == nullptr) {
			break;
		}
		else if (root->left != nullptr && root->right != nullptr) {
			if (root->left->height == root->right->height) {
				break;
			}
			else {
				root = root->left->height > root->right->height ? root->left : root->right;
			}
		}
		else {
			root = root->left == nullptr ? root->right : root->left;
		}
	}
}

void remove(Node* root) {
	if (root->left == nullptr && root->right == nullptr) {
		if (root->parent != nullptr) {
			if (root->parent->left == root) {
				root->parent->left = nullptr;
			}
			else {
				root->parent->right = nullptr;
			}
		}

		return;
	}

	if (root->left == nullptr) {
		if (root->parent != nullptr) {
			if (root->parent->left == root) {
				root->parent->left = root->right;
			}
			else {
				root->parent->right = root->right;
			}
		}

		root->right->parent = root->parent;

		if (root->parent == nullptr) {
			top = root->right;
		}

		return;
	}

	if (root->right == nullptr) {
		if (root->parent != nullptr) {
			if (root->parent->left == root) {
				root->parent->left = root->left;
			}
			else {
				root->parent->right = root->left;
			}
		}

		root->left->parent = root->parent;

		if (root->parent == nullptr) {
			top = root->left;
		}

		return;
	}

	Node* minRight = root->right;
	while (minRight->left != nullptr) {
		minRight = minRight->left;
	}

	root->key = minRight->key;
	remove(minRight);
}

void preorderTraversal(Node* root) {
	if (root == nullptr) {
		return;
	}

	std::cout << root->key << '\n';
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

void postorderTraversal(Node* root) {
	if (root == nullptr) {
		return;
	}

	postorderTraversal(root->left);
	postorderTraversal(root->right);
	if (root->toDelete == true) {
		remove(root);
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	//std::freopen("in.txt", "r", stdin);
	//std::freopen("out.txt", "w", stdout);

	int key;
	Node* root = nullptr;
	std::cin >> key;
	root = new Node(key, nullptr);
	top = root;

	Node* currNode = nullptr;
	while (std::cin >> key) {
		currNode = root;
		while (true) {
			if (key < currNode->key) {
				if (currNode->left == nullptr) {
					currNode->left = new Node(key, currNode);

					break;
				}
				else {
					currNode = currNode->left;
				}
			}
			else if (key > currNode->key) {
				if (currNode->right == nullptr) {
					currNode->right = new Node(key, currNode);

					break;
				}
				else {
					currNode = currNode->right;
				}
			}
			else {
				break;
			}
		}
	}

	heights(root);

	maxRoot->toDelete = true;
	if (maxRoot->lowestOne == true) {
		if (maxRoot->left->height > maxRoot->right->height) {
			defineNodesToDelete(maxRoot->left);
		}
		else if (maxRoot->left->height < maxRoot->right->height) {
			defineNodesToDelete(maxRoot->right);
		}
	}
	else {
		if (maxRoot->left != nullptr) {
			defineNodesToDelete(maxRoot->left);
		}

		if (maxRoot->right != nullptr) {
			defineNodesToDelete(maxRoot->right);
		}
	}

	postorderTraversal(root);

	preorderTraversal(top);

	return 0;
}
