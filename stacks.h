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
/********************************************//**
 * Inserts & deletes are only made at the top of
 * stack. The stack implements LIFO (last in - first out).
 * The stack is referenced via a pointer to the top node.
 * The link member of the last node in the stack is
 * set to NULL.
 *********************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define S_OK 0
#define S_OUT_OF_BOUNDS_ERROR (-1)

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
} Stack;

/********************************************//**
 * @brief Returns the size of the stack based on
 * total count of nodes.
 *
 * @param ADT_Stack
 * @return int
 *
 ***********************************************/
#define S_SIZE(stack) (stack->length)

/********************************************//**
 * @brief Returns the current index of the top node.
 *
 * @param ADT_Stack
 * @return int
 *
 ***********************************************/
#define S_CURRENT_INDEX(stack) (stack->nodes->index)

/********************************************//**
 * @brief Enables the caller to peek at the top
 *  node without popping it off the stack. It
 * returns a reference to the top node.
 *
 * @param stack const ADT_Stack*
 * @return ADT_Stack*
 *
 ***********************************************/
#define S_PEEK(stack) (stack->nodes->data)

/********************************************//**
* @brief Creates the stack & sets the stack's options
* It is the responsibility of the caller to manage
* the memory of void *data.
* @param data void*
* @return ADT_Stack*
*
***********************************************/
Stack * S_Stack_new(S_Options *o);

/********************************************//**
 * @brief Detaches each node from the stack.
 * This function does not destroy allocated memory
 * assigned to the node's data.
 *
 * @param stack ADT_Stack*
 * @return void
 *
 ***********************************************/
int S_Stack_destroy(Stack *stack);

/********************************************//**
 * @brief Pushes the next node on the stack.
 * You must initiates the stack by calling the
 * #init(void *data) first. It is the responsibility
 * of the caller to manage the memory of void *data.
 *
 * @param data void*s
 * @return int
 *
 ***********************************************/
int S_Stack_push(Stack *stack, void *data);

/********************************************//**
 * @brief Removes the top nod from the stack.
 * The caller must manage the memory of void *data.
 *
 * @param stack ADT_Stack*
 * @return int*
 *
 ***********************************************/
void *S_Stack_pop(Stack *stack);

#endif //STACKS_STACKS_H
