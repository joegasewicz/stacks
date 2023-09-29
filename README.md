# Stacks
A stack static library written in C

### Initiate
```c
 Stack *my_stack = S_Stack_new(NULL);
```
### Destroy
```c
if (S_Stack_destroy(my_stack) < 0)
    perror("panic!");
```

### Push
```c
int data1 = 1, data2 = 2; // *void
S_Stack_push(my_stack, &data1);
S_Stack_push(my_stack, &data2);
```

### Peek
```c
// TODO
```

### Size
```c
// TODO
```
