//
// Created by kendricks on 12/10/23.
//

#include "units_pointer_comparison.h"

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

const pointer_counter_t* find_pointer_in_list(const pointer_counter_t** list, const size_t size, const void* data)
{
    for (size_t i = 0; i < size; i++)
    {
        if (list[i]->data == data)
        {
            return &list[i];
        }
    }

    return NULL;
}
_Bool list_contains_pointer(const pointer_counter_t* list, const size_t size, const void* pointer)
{
    for(int i = 0; i < size; i++)
    {
        if(list[i].data == pointer) return true;
    }
    return false;
}

/*pointer_counter_t* count_occurences_of_pointer(void** list, const size_t size_of_list, size_t* output_size)
{
    pointer_counter_t* output = malloc(size_of_list * sizeof(pointer_counter_t));
    if (output == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }

    for (size_t i = 0; i < size_of_list; i++)
    {
        if (list_contains_pointer(output, size_of_list, list[i])) continue;
        
        size_t count = 1;
        for (size_t j = i + 1; j < size_of_list; j++)
        {
            if (list[i] == list[j])
            {
                count++;
            }
        }

        output[(*output_size)++] = (pointer_counter_t){list[i], count};
    }
    return output;
}*/