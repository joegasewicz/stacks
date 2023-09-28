/* @file lists.h */
/**
* MIT License
*
* Copyright (c) 2023 Joe Gasewicz
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#ifndef STACKS_STACKS_H
#define STACKS_STACKS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define S_FIXED_SIZED 0
#define S_OK 0

typedef struct Node_ {
    void *data;
    struct Node_* link;
    int index;
} Node;

typedef struct S_Options_ {
    int max_length;
    bool dynamic;
} S_Options;

typedef struct Stack_ {
    Node* nodes;
    Node* top;
    S_Options *options;
    int length;
    int curr_index;
    int top_index;
} Stack;

Stack * S_Stack_new(S_Options *o);
int S_Stack_push(Stack *stack, void *data);


#endif //STACKS_STACKS_H
