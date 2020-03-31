#include "huffman_tree.h"
#include "file_buffer.h"
#include <stdio.h>

HuffmanNode* tree_connect(HuffmanNode* left, HuffmanNode* right) {
	HuffmanNode* parent = (HuffmanNode*)calloc(1,sizeof(HuffmanNode));
	parent->c = 0;
	parent->leaf = 0;
	parent->leftchild = left;
	parent->rightchild = right;
	parent->count = left->count + right->count;
	return parent;
}


void tree_set_codes(HuffmanNode* root, int depth, int value) {
	if (root->leaf == 0) {
		tree_set_codes(root->leftchild, depth + 1, value << 1);
		tree_set_codes(root->rightchild, depth + 1, value << 1 | 1);
	}
	else {
		root->bit_value = value;
		root->bit_length = depth;
	}
}

void tree_write_buffer(HuffmanNode* root, FileBuffer* fbuffer) {
	if (root->leaf == 0) {
		buffer_write_bit(fbuffer, 0);
		tree_write_buffer(root->leftchild, fbuffer);
		tree_write_buffer(root->rightchild, fbuffer);
	}
	else {
		buffer_write_bit(fbuffer, 1);
		buffer_write_bits(fbuffer, root->c, 8);
	}
}

HuffmanNode* tree_reconstruct(HuffmanNode* root, FileBuffer* fbuffer) {
	int bit = buffer_next_bit(fbuffer);
	if (bit) {
		unsigned int c = buffer_next_bits(fbuffer, 8);
		root->c = c;
		root->leaf = 1;
	}
	else {
		HuffmanNode* left = (HuffmanNode*)calloc(1, sizeof(HuffmanNode));;
		HuffmanNode* right = (HuffmanNode*)calloc(1, sizeof(HuffmanNode));;
		root->leftchild = left;
		root->rightchild = right;
		tree_reconstruct(root->leftchild, fbuffer);
		tree_reconstruct(root->rightchild, fbuffer);
	}
	return root;
}

void tree_free(HuffmanNode* root) {
	if (root->leaf == 0) {
		tree_free(root->leftchild);
		tree_free(root->rightchild);
		free(root);
	}
	else {
		free(root);
	}
}

void tree_print(HuffmanNode* root, int i) {
	if (root->leaf == 0) {
		tree_print(root->rightchild, i+1);
		for (int k = 0; k < i; k++) {
			printf("\t");
		}
		printf("* \n");
		tree_print(root->leftchild, i + 1);
	}
	else {
		for (int k = 0; k < i; k++) {
			printf("\t");
		}
		printf("%c \n", root->c);
	}
}