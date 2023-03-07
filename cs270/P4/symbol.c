#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Debug.h"
#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement the symbol.h interface
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. The reference implementation added approximately
 *  110 lines of code to this file. This count includes lines containing
 *  only a single closing bracket (}).
 * <p>
 * @author <b>Your name</b> goes here
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16)

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** defines data structure used to store nodes in hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** defines the data structure for the hash table */
struct sym_table {
  int      capacity;    /**< length of hast_table array                  */
  int      size;        /**< number of symbols (may exceed capacity)     */
  node_t** hash_table;  /**< array of head of linked list for this index */
  char**   addr_table;  /**< look up symbols by addr                     */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}

/** @todo implement this function */
sym_table_t* symbol_init (int capacity) {
    sym_table_t *table=(sym_table_t*) malloc(sizeof(sym_table_t));
	table->capacity=capacity;
	table->size=0;
	table->hash_table=calloc(capacity,sizeof(node_t*));
	table->addr_table=calloc(LC3_MEMORY_SIZE,sizeof(char*));
	return table;
}

/** @todo implement this function */
void symbol_term (sym_table_t* symTab) {
}

/** @todo implement this function */
void symbol_reset(sym_table_t* symTab) {
    for(int i=0; i<symTab->capacity; i++){
		node_t *node=symTab->hash_table[i];
		while(node != NULL){
			node_t *temp=node->next;
			free(node->symbol.name);
			free(node);
			node=temp;
		}
		symTab->hash_table[i]=NULL;
	}
	symTab->size=0;
}

/** @todo implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
    debug("add running");
	int hash,index;
	//check if node exists
	node_t *node=symbol_search(symTab,name,&hash,&index);
	if (node==NULL){ //does not exist so add it
		node=(node_t*) malloc(sizeof(node_t));
		//new node node needs a symbol
		node->symbol.name=strdup(name);
		node->symbol.addr=addr;
		node->hash=hash;
		debug("HASH %d, INDEX %d",hash,index);
		node->next=symTab->hash_table[index];
		symTab->hash_table[index]=node;
		symTab->addr_table[addr]=node->symbol.name;
		symTab->size+=1;
		return 1;
	}
	debug("NULL");
	return 0;
	debug("new name: %s, existingname: %s",name,node->symbol.name);
}

/** @todo implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
  
  debug("search running");
    *hash = symbol_hash(name);    
    *index = *hash%(symTab->capacity);
    node_t *node = symTab->hash_table[*index];
    while(node != NULL){
		if(*hash==node->hash){
			if(strcasecmp(name, node->symbol.name)==0){
				return node;
			}
		}
		node=node->next;
    }
    
	return NULL;
}

/** @todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
    int hash, index;
	node_t *node = symbol_search(symTab,name,&hash,&index);
	return &(node->symbol);
}

/** @todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
  return symTab->addr_table[addr];
}

/** @todo implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
    debug("iterate running");
	for(int h=0; h<symTab->capacity; h++){
		node_t *cnode = symTab->hash_table[h];
		while(cnode != NULL){
			(*fnc)(&(cnode->symbol),data);
			cnode=cnode->next;
		}
		
	}
}

/** @todo implement this function */
int symbol_size (sym_table_t* symTab) {
  return 0;
}

/** @todo implement this function */
int compare_names (const void* vp1, const void* vp2) {
  // symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this

  return 0;
}

/** @todo implement this function */
int compare_addresses (const void* vp1, const void* vp2) {
  return 0;
}

/** @todo implement this function */
symbol_t** symbol_order (sym_table_t* symTab, int order) {
  // will call qsort with either compare_names or compare_addresses
  return NULL;
}

