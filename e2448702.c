#include <stdio.h>
#include <stdlib.h>
#include "the3.h"

/* Functions */
int strCompare(char* s1, char* s2)
{
	int loop1;
	int length1 = 0, length2 = 0;
	for(length1;*(s1+length1)!=0;length1++);
	for(length2;*(s2+length2)!=0;length2++);
	if(length1 != length2)
	{
		return 0;
	}
	else
	{
		for(loop1=0;loop1<=length1;loop1++)
		{
			if(*(s1+loop1) == *(s2+loop1))
			{
				continue;
			}
			else
			{
				return 0;
			}
		}
	}
	return 1;
}

void Jesus_Please_Help(char* apt_name, Apartment* street)
{
	Apartment *curr=street, *prev = NULL;
	while(!strCompare(curr->name,apt_name))
	{
		prev = curr;
		curr = curr->next;
	}
	prev->next = curr->next;
}

Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth)
{
    if(head == NULL)
    {
		Apartment* new_apartment;

        new_apartment = (Apartment*)malloc(sizeof(Apartment));
        new_apartment->name = apartment_name;
        new_apartment->flat_list = NULL;
        new_apartment->max_bandwidth = max_bandwidth;
        new_apartment->next = new_apartment; 
        head = new_apartment;
		
    }   
	
    else
    {
        int loop1,control=1;
        Apartment* new_apartment;
        Apartment *curr=head;
        for(loop1=0;loop1<index-1;loop1++)
        {
			control=0;
            curr = curr->next;
        }
        new_apartment = malloc(sizeof(Apartment));
        new_apartment->name = apartment_name;
        new_apartment->flat_list = NULL;
        new_apartment->max_bandwidth = max_bandwidth;
		
        if(curr->next == head && control)
        {
			if(index == 0)
			{
				new_apartment->next = curr;
				curr->next = new_apartment;
				head = new_apartment;
			}
			else if(index == 1)
			{
				new_apartment->next = head;
        		curr->next = new_apartment;
			}
        	
        }
        else if(index==0)
        {
        	new_apartment->next = head;
			while(!strCompare(curr->next->name,head->name))
			{
				curr = curr->next;
			}
			curr->next = new_apartment;
        	head = new_apartment;
        }
        else
        {
        	new_apartment->next = curr->next;
        	curr->next = new_apartment;
        }
    }
	
  return head;
}

int find_curr_bandwidths(Apartment* head)
{
	Flat* flat_lst;
	int sum=0;
	flat_lst = head->flat_list;
	if(flat_lst == NULL)
	{
		return 0;
	}
	while(flat_lst != NULL)
	{
		sum += flat_lst->initial_bandwidth;
		flat_lst = flat_lst->next;
	}
	return sum;
}

void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth)
{
	Flat *new_flat;
	Apartment *curr=head;
	int total_bandwidth;
	new_flat = malloc(sizeof(Flat));
	new_flat->id = flat_id;
	new_flat->is_empty = 0;
	new_flat->initial_bandwidth = 0;
	new_flat->next = NULL;
	new_flat->prev = NULL;

	while(!strCompare(curr->name,apartment_name))
	{
		curr = curr->next;
	}
	total_bandwidth = find_curr_bandwidths(curr);
	if(curr->max_bandwidth-total_bandwidth >= initial_bandwidth)
	{
		new_flat->initial_bandwidth = initial_bandwidth;
	}
	else
	{
		new_flat->initial_bandwidth = curr->max_bandwidth-total_bandwidth;
	}
	if(curr->flat_list == NULL)
	{
		curr->flat_list = new_flat;
	}
	else if(index == 0)
	{
		new_flat->next = curr->flat_list;
		curr->flat_list->prev = new_flat;
		curr->flat_list = new_flat;
	}
	else
	{
		int loop1;
		Flat* current = curr->flat_list;
		for(loop1=0;loop1<index-1;loop1++)
		{
			current = current->next;
		}
		if(current->next == NULL)
		{
			current->next = new_flat;
			new_flat->next = NULL;
			new_flat->prev = current;
		}
		else
		{
			current->next->prev = new_flat;
			new_flat->next = current->next;
			current->next = new_flat;
			new_flat->prev = current;
			
		}
	}
}

Apartment* remove_apartment(Apartment* head, char* apartment_name)
{
	Apartment *curr=head , *prev_apt = NULL;
	Flat *current , *previous=NULL;
	while(!strCompare(apartment_name,curr->name))
	{
		prev_apt  = curr;
		curr = curr->next;
	}
	current = curr->flat_list;
	if(current == NULL)
	{
		goto Linking_Step;
	}
	while(current->next != NULL)
	{
		previous = current;
		current = current->next;
	}
	
	while(previous != NULL)
	{
		Flat *temp=current;
		free(temp);
		current = previous;
		previous = previous->prev;
	}
	
	free(current);
	Linking_Step: /*LINK PART*/
	if(prev_apt)
	{
		prev_apt->next = curr->next;
	}
	else
	{
		if(!strCompare(curr->next->name,curr->name)) 
		{
			head = curr->next; 
			Jesus_Please_Help(curr->name,curr->next); 
		}
		else
		{
			head = NULL;
		}
		
	}
	free(curr);
	return head;
}


void make_flat_empty(Apartment* head, char* apartment_name, int flat_id)
{
	Apartment *curr=head;
	Flat *flat_lst;

	while(!strCompare(apartment_name,curr->name))
	{
		curr = curr->next;
	}
	flat_lst = curr->flat_list;
	while(flat_lst->id != flat_id)
	{
		flat_lst = flat_lst->next;
	}
	flat_lst->is_empty = 1;
	flat_lst->initial_bandwidth = 0;

}

int find_sum_of_max_bandwidths(Apartment* head)
{
	int sum = 0;
	if(head == NULL)
	{
		return 0;
	}
	else
	{
		Apartment *curr=head;
		while(!strCompare(curr->next->name,head->name))
		{
			sum += curr->max_bandwidth;
			curr = curr->next;
		}
		sum += curr->max_bandwidth;
		return sum;
	}
}

Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2)
{
	
	Apartment *apart1=head, *apart2=head;

	while(!strCompare(apart1->name,apartment_name_1))
	{
		apart1 = apart1->next;
	}
	while(!strCompare(apart2->name,apartment_name_2))
	{
		apart2 = apart2->next;
	}
	
	if(apart1->flat_list == NULL && apart2->flat_list == NULL)
	{
		apart1->max_bandwidth += apart2->max_bandwidth;
		apart2->flat_list = NULL;
		head = remove_apartment(apart1, apartment_name_2);
		return head;
	}
	
	else if(apart1->flat_list == NULL)
	{
		apart1->max_bandwidth += apart2->max_bandwidth;
		apart1->flat_list = apart2->flat_list;
		apart2->flat_list = NULL;
		head = remove_apartment(head, apartment_name_2);
		return head;
	}
	else if(apart2->flat_list == NULL)
	{
		apart1->max_bandwidth += apart2->max_bandwidth;
		head = remove_apartment(head,apartment_name_2);
		return head;
	}
	else
	{
		
		Flat *last_flat = apart1->flat_list;
		apart1->max_bandwidth += apart2->max_bandwidth;
		while(last_flat->next != NULL)
		{
			last_flat = last_flat->next;
		}
		last_flat->next = apart2->flat_list;
		apart2->flat_list->prev = last_flat;
		apart2->flat_list = NULL;
		head = remove_apartment(head, apartment_name_2);
		
		return head;
	}
	
}

void find_and_set_flat(int flat_id, Apartment* shift_apart, int apart_id, Apartment* head)
{
	Apartment *apart=head;
	Flat* flat=(apart->flat_list),*prev_flat=NULL;
	int id;
	id = apart->flat_list->id;
	
	while(id != flat_id)
	{
		prev_flat = flat;
		flat = flat->next;
		if(flat == NULL)
		{
			prev_flat = NULL;
			apart = apart->next;
			while(apart->flat_list == NULL)
			{
				apart = apart->next;
			}
			flat = apart->flat_list;
			id = apart->flat_list->id;
			continue;
		}
		id = flat->id;
	}
	if(prev_flat != NULL)
	{
		if(flat->next != NULL)
		{
			prev_flat->next = flat->next;
			flat->next->prev = prev_flat;
		}
		else
		{
			prev_flat->next = NULL;
		}
	}
	else
	{
		if(flat->next == NULL)
		{
			apart->flat_list = NULL;
		}
		else
		{
			apart->flat_list = flat->next;
			flat->next->prev = NULL;
		}
	}
	apart->max_bandwidth -= flat->initial_bandwidth;
	
	

	/*STEPS FOR FINDING FLAT TO SHIFT*/
	
	{
		Flat *shift_flat=shift_apart->flat_list, *prev_shift_flat = NULL;
		id = shift_apart->flat_list->id;
		while(id != apart_id)
		{
			prev_shift_flat = shift_flat;
			shift_flat = shift_flat->next;
			id = shift_flat->id;
		}
		if(prev_shift_flat != NULL)
		{
			prev_shift_flat->next = flat;
			flat->prev = prev_shift_flat;
		}
		else
		{
			shift_apart->flat_list = flat;
			flat->prev = NULL;
		}
		flat->next = shift_flat;
		shift_flat->prev = flat;
		shift_apart->max_bandwidth += flat->initial_bandwidth;
	}
	
}
void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list)
{
	Apartment *apart=head;
	while(!strCompare(apart->name,new_apartment_name))
	{
		apart = apart->next;
	}
	while(*flat_id_list != 0)
	{
		find_and_set_flat(*flat_id_list,apart,flat_id_to_shift,head);
		flat_id_list++;
	}
}
/* Functions */