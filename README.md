# Stacks
A stack structure static library written in C with a few extra features
- Set the stack to have either a dynamic or static length
- An error will be returned if the stack reaches its maximum set length
- Get the stack's current (*node's*) index at any time

### Initiate
Options allow the stack length to be set to dynamic or static. 
Without options the stack will have a dynamic length.
```c
 S_Stack *my_stack = S_Stack_new(NULL);
```
With options the stack will return a `S_OUT_OF_BOUNDS_ERROR`.
```c
S_Options options = (S_Options){ .max_length = 1, .dynamic = false };
// still within max_length limit
int ok = S_Stack_push(my_stack, &data1);
assert(S_OUT_OF_BOUNDS_ERROR != ok);

// exceeded the max_length
int err = S_Stack_push(my_stack, &data2);
assert(S_OUT_OF_BOUNDS_ERROR == err);

```
### Destroy
Detaches each node from the stack.
This function does not destroy allocated memory assigned to the node's data.
```c
if (S_Stack_destroy(my_stack) < 0)
    perror("panic!");
```

### Push
Pushes the next node on the stack.
You must initiate the stack by calling the S_Stack_new(NULL) first.
It is the responsibility of the caller to manage the memory of void *data.
```c
int data1 = 1, data2 = 2; // *void
S_Stack_push(my_stack, &data1);
S_Stack_push(my_stack, &data2);
```

### Pop
Removes the top nod from the stack. 
The caller must manage the memory of void *data.
```c
void* data = S_Stack_pop(my_stack);
```

### Peek *(macro)*
Enables the caller to peek at the top node without popping it off the stack.
It returns a reference to the top node.
```c
void *data = S_PEEK(my_stack);
```

### Size *(macro)*
Returns the size of the stack based on total count of nodes.
```c
int stack_size = S_SIZE(my_stack);
```

### Current Index *(macro)*
Returns the current node index (or top node on the stack).
```c
int current_node_index = S_CURRENT_INDEX(my_stack);
```
