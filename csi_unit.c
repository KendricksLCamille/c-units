//
// Created by kendricks on 12/10/23.
//

#include "csi_unit_implementation.h"

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quantity/csi_quantity.h"
#include "prefix/csi_prefix.h"
#include "lib/sds-master/sds.h"



typedef struct list
{
    csi_unit* list;
    size_t size;
    CSI_MAGINITUDE_TYPE multiplier;
} list_t;

CSI_MAGINITUDE_TYPE get_base_unit_multiplier(const csi_unit* dimmension)
{
    CSI_MAGINITUDE_TYPE denominator_multiplier = csi_prefix_to_magnitude(dimmension->type->base_unit->prefix);
    CSI_MAGINITUDE_TYPE numerator_multiplier = csi_prefix_to_magnitude(dimmension->prefix);
    return CSI_MAGINITUDE_TYPE_DIVIDE(numerator_multiplier, denominator_multiplier);
}
void find_and_increment_then_multiple(struct list* list, const csi_unit* dimmension, const _Bool negative)
{
    for (size_t i = 0; i < list->size; i++)
    {
        const csi_unit dimmension2 = list->list[i];

        if (dimmension2.type == dimmension->type)
        {
            list->multiplier = CSI_MAGINITUDE_TYPE_MULTIPLY(get_base_unit_multiplier(dimmension),
                                                            get_base_unit_multiplier(&dimmension2));
            const int power2 = dimmension2.power + (negative? -1 : 1) * dimmension->power;
            list->list[i].power = power2;
            return;
        }
    }
    list->list = realloc(list->list, (list->size + 1) * sizeof(csi_unit));
    if (list->list == NULL)
    {
        errno = ENOMEM;
        return;
    }
    memcpy(&list->list[list->size], dimmension->type->base_unit, sizeof(csi_unit));
    list->list[list->size].power *= negative? -1 : 1;
    list->size++;
}
list_t* breakdown(const csi_unit* dimmensions, list_t* list)
{
    if (list == NULL)
    {
        list = malloc(sizeof(list_t));
        list->multiplier = CSI_MAGINITUDE_TYPE_ZERO;
    }
    
    for (size_t i = 0; i < dimmensions->number_unit_in_numerator; i++)
    {
        const csi_unit* dimmension = dimmensions->numerator[i];
        if (dimmension->type == NULL)
        {
            breakdown(dimmension, list);
        }
        else
        {
            find_and_increment_then_multiple(list, dimmension, false);
        }
        if(errno == ENOMEM) return NULL;
    }
    
    for (size_t i = 0; i < dimmensions->number_unit_in_denominator; i++)
    {
        const csi_unit* dimmension = dimmensions->denominator[i];
        if (dimmension->type == NULL)
        {
            breakdown(dimmension, list);
        }
        else
        {
            find_and_increment_then_multiple(list, dimmension, true);
        }
        if(errno == ENOMEM) return NULL;
    }
    
    return list;
}

_Bool is_lists_equal(const list_t* list1, const list_t* list2)
{
    if(list1->size!= list2->size) return false;
    for (size_t i = 0; i < list1->size; i++)
    {
        const csi_unit l1 = list1->list[i];
        for (size_t j = 0; j < list2->size; j++)
        {
            const csi_unit l2 = list2->list[j];
            if (l1.type == l2.type && l1.power == l2.power) goto success;
        }
        return false; // If not a single match is found, return false.
        success:
    }
    return true;
}
char* list_to_string(const list_t* list)
{
    sds str = sdsempty();
    for (size_t i = 0; i < list->size; i++)
    {
        const csi_unit dimmension = list->list[i];
        if (i > 0) str = sdscat(str, " * ");
        str = sdscat(str, dimmension.symbol);
        if(dimmension.power!= 1)
        {
            str = sdscat(str, "^");
            str = sdscatfmt(str, "%i", dimmension.power);
        }
    }

    char* result = strdup(str);
    sdsfree(str);
    return result;
}

char* get_dimmensions_string(const csi_unit* dimmensions)
{
    list_t* list = breakdown(dimmensions, NULL);
    if (errno == ENOMEM) return NULL;

    // remove all elements with a power of 0
    for (size_t i = 0; i < list->size; i++)
    {
        const csi_unit dimmension = list->list[i];
        if (dimmension.power == 0)
        {
            for (size_t j = i; j < list->size - 1; j++)
            {
                // use memcpy to copy the last element to the current element
                memcpy(&list->list[j], &list->list[j + 1], sizeof(csi_unit));
            }
            list->size--;
            i--;
        }
    }

    char* result = list_to_string(list);
    if(errno == ENOMEM) return NULL;
    free(list);
    return result;
}
void print_dimmensions(const csi_unit* dimmensions)
{
    printf("Quntity: %s\n", dimmensions->derived_quantity);
    printf("Name: %s\n", dimmensions->name);
    printf("Symbol: %s\n", dimmensions->symbol);
    printf("Breakdown: %s\n", get_dimmensions_string(dimmensions));
}