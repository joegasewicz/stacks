/** @file stacks.c */
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
#include "stacks.h"



Stack * S_Stack_new(S_Options *o)
{
    S_Options *default_options;
    Stack *s = malloc(sizeof(Stack));
    if (s == NULL)
        goto error;
    s->length = 0;
    s->nodes = NULL;
    s->top = NULL;
    //  If no options are set then create defaults
    if (o == NULL)
    {
        default_options = malloc(sizeof(S_Options));
        if (default_options == NULL)
            goto error;
        default_options->max_length = 0;
        default_options->dynamic = true;
        s->options = default_options;
        return s;
    }
    S_Options *options = malloc(sizeof(S_Options));
    if (options == NULL)
        goto error;
    s->options = options;
    s->options->max_length = o->max_length;
    s->options->dynamic = false; // set default
    if (o->max_length == 0)
        options->dynamic = true;
    return s;
error:
    perror("Failed to allocate memory");
    return NULL;
}

int S_Stack_destroy(Stack *stack)
{
    if (stack == NULL)
        goto ok;
    if (stack->nodes == NULL)
    {
        free(stack->options);
        free(stack);
        goto ok;
    }
    Node *currNode = NULL;
    Node *linkNode = stack->nodes;
    while (linkNode != NULL)
    {
        if (linkNode->link == NULL)
        {
            free(linkNode);
            break;
        }
        currNode = linkNode;
        linkNode = linkNode->link;
        if (currNode != NULL)
            free(currNode);
    }
    free(stack->options);
    free(stack);
    stack = NULL;
    goto ok;
ok:
    return S_OK;
}

int S_Stack_push(Stack *stack, void *data)
{
    Node *n = malloc(sizeof(Node));
    n->data = data;
    if (stack->nodes == NULL)
    {
        n->link = NULL;
        n->index = 0;
    }
    else
    {
        n->link = stack->nodes;
        n->index = stack->nodes->index + 1;
    }
    stack->nodes = n;
    stack->length++;
    return S_OK;
}

void *S_Stack_pop(Stack *stack)
{
    Node *tempPtr = NULL;
    void *dataPtr = NULL;
    if (stack == NULL || stack->nodes == NULL)
        goto exit;
    tempPtr = stack->nodes;
    if (stack->nodes->link == NULL)
    {
        dataPtr = tempPtr->data;
        free(stack->nodes);
        stack->nodes = NULL;
        stack->length--;
        return dataPtr;
    }
    stack->nodes = tempPtr->link;
    dataPtr = tempPtr->data;
    free(tempPtr);
    stack->length--;
    return dataPtr;
exit:
    return NULL;
}
