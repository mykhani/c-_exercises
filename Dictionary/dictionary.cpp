#include <iostream>
#include <string.h>

using namespace std;

#define DEBUG

#if defined(DEBUG)
#define debug(x) cout << x"\n"
#else
#define debug(x) {}	
#endif

/* For now just create dictionary of integers, once I learn templates,
 * I can create dictionary of any type of objects */
class Dict {
private:
	class element {
	public:
		char key[255];
		int value;
		element *next;
		element *prev;

		element() : next(NULL), prev(NULL) {}
		element(char *key);
	}; 
	element *head;

	int* getVal(char *key);
	void listAdd(element *el);
	
public:
	Dict() : head(NULL) {}
	int& operator [] (char *);
};

Dict::element::element(char *key)
{
	strncpy(Dict::element::key, key, strlen(key)); 
}

int* Dict::getVal(char *key)
{
	element *i;

	static int dummy = -1001; /* invalid */

	for (i = head; i != NULL; i = i->next) {
		cout << "key to find: " << key << endl;
		cout << "key got: " << i->key << endl;
		if (strncmp(key, i->key, strlen(key)) == 0) {
			return &(i->value);
		} 
	}
	debug("key not found");
	/* key not found, so return invalid */
	return &dummy; 
}

void Dict::listAdd(element *el)
{
	/* check if list is empty */
	if (head == NULL) {
		debug("Adding first list entry");
		el->next = NULL;
		el->prev = NULL;
		head = el;
	} else {
		debug("Adding another list entry");
		el->next = head;
		el->prev = NULL;
		head->prev = el;
		head = el;
	}
}

int& Dict::operator [] (char *key)
{
	int *val;

	val = getVal(key);
	/* check if key is already present */
	if (*val < 0) {
		debug("Adding new key");
		/* Key not found, so add an element */
		element *el = new element(key);
		listAdd(el);
		return el->value;
	} else {
		return *val; 
	}
}

int main(int argc, char *argv[])
{
	Dict cities = Dict();

	cities["Pakistan"] = 48;
	cities["India"] = 148;
	
	cout << cities["Pakistan"] << endl;
	cout << cities["India"] << endl;
	/* TODO: see if there is a way to stop creating node for
         * for element for which value is not specified ? */
	cout << cities["Bangladesh"] << endl;


}
