typedef struct Node{
    char* name;
    char* surname;
    char* email;
    char* phoneNumber;

    struct Node* next;
} Node;

extern void print_node(Node* node);
extern void print_records();
extern int add_new_to_end(Node* node);
extern int add_new_by_index(Node* node, int idx);
extern int delete_by_index(int idx);
extern void delete_all();
extern Node* find_by_pos(int idx);
extern Node* find_by_name(char* name);
extern Node* create_new_node(char* name, char* surname, char* email, char* phoneNumber);