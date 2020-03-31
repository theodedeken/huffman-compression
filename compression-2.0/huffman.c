#include "huffman.h"
#include "huffman_map.h"
#include "huffman_queue.h"
#include "huffman_tree.h"
#include "file_buffer.h"

#include <stdlib.h>

FileBuffer* huffman_encode(FileBuffer* fbuffer) {
	//nieuwe map
	HuffmanMap* charmap = map_alloc();
	//overloop buffer en pas de count aan in map
	unsigned char next;
	while (fbuffer->pointer < fbuffer->size) {
		next = buffer_next_char(fbuffer);
		if (map_contains(charmap, next)) {
			map_find(charmap, next)->count++;
		}
		else {
			HuffmanNode* new_node = (HuffmanNode*)calloc(1, sizeof(HuffmanNode));
			new_node->count = 1;
			new_node->c = next;
			new_node->leaf = 1;
			map_insert(charmap, next, new_node);
		}		
	}
	//nieuwe pqueue
	HuffmanQueue* pqueue = pqueue_alloc();
	//alles van map in pqueue
	map_fill_pqueue(charmap, pqueue);
	//overloop pqueue en voeg de twee kleinste steeds samen
	HuffmanNode* node1 = pqueue_remove_first(pqueue);
	HuffmanNode* node2 = pqueue_remove_first(pqueue);
	while (node2 != NULL) {
		pqueue_add(pqueue, tree_connect(node1, node2));
		node1 = pqueue_remove_first(pqueue);
		node2 = pqueue_remove_first(pqueue);
	}
	HuffmanNode* root = node1;
	//stel de bitcodes in 
	tree_set_codes(root,0,0);
	//nieuwe buffer
	FileBuffer* encoded = buffer_alloc();
	//schrijf weg hoeveel karakters de gecodeerde tekst zal bevatten, tekst kan niet langer zijn dan 2^64 karakters
	buffer_write_bits(encoded, fbuffer->size, 64);
	//schrijf boom weg
	tree_write_buffer(root, encoded);
	//fbuffer flip
	buffer_flip(fbuffer);
	//overloop fbuffer en schrijf overeenkomstige bitcode in nieuwe buffer
	
	while (fbuffer->pointer < fbuffer->size) {
		next = buffer_next_char(fbuffer);
		buffer_write_bits(encoded, map_find(charmap, next)->bit_value, map_find(charmap, next)->bit_length);
	}
	buffer_bit_flush(encoded);
	//free map
	map_free(charmap);
	//free pqueue
	pqueue_free(pqueue);
	//free tree
	tree_free(root);
	//return buffer
	return encoded;
}

FileBuffer* huffman_decode(FileBuffer* fbuffer) {
	unsigned long long size = buffer_next_bits(fbuffer, 64);
	//reconstrueer boom
	HuffmanNode* start = (HuffmanNode*)calloc(1, sizeof(HuffmanNode));
	HuffmanNode* root = tree_reconstruct(start, fbuffer);
	//nieuwe buffer
	FileBuffer* decoded = buffer_alloc();
	//lees bestand bit per bit en traverseer boom en schrijf char in buffer
	int bit = buffer_next_bit(fbuffer);
	HuffmanNode* current = root;
	//geeft -1 terug als buffer op is
	while (size > 0) {
		if (bit) {
			//rechts
			current = current->rightchild;
		}
		else {
			//links
			current = current->leftchild;
		}
		if (current->leaf != 0) {
			buffer_write_char(decoded, current->c);
			current = root;
			size--;
		}
		bit = buffer_next_bit(fbuffer);
	}
	//geef de boom vrij
	tree_free(root);
	//return buffer
	return decoded;
}