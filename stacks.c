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
    char *err_str = "Failed to allocate memory";
    S_Options *default_options;
    Stack *s = malloc(sizeof(Stack));
    if (s == NULL)
        perror(err_str);
    s->length = 0;
    s->curr_index = 0;
    s->top_index = 0;
    s->nodes = NULL;
    s->top = NULL;
    //  If no options are set then create defaults
    if (o == NULL)
    {
        default_options = malloc(sizeof(S_Options));
        if (default_options == NULL)
            perror(err_str);
        default_options->max_length = 0;
        default_options->dynamic = true;
        s->options = default_options;
        return s;
    }
    s->options = malloc(sizeof(S_Options));
    if (s->options == NULL)
        perror(err_str);
    s->options->max_length = o->max_length;
    s->options->dynamic = false; // set default
    if (o->max_length == 0)
        s->options->dynamic = true;
    return s;
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
        n->index = stack->nodes->index++;
    }
    stack->nodes = n;
    stack->length++;
    return S_OK;
}

void S_push(Node *curr_node, void *data)
{
    Node *n = malloc(sizeof(Node));
    if (n != NULL)
    {
        n->data = data;
        n->link = curr_node;
    }
}