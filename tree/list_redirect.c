/*
** list_redirect.c for 42sh in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/tree
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Thu May  4 14:57:16 2017 maje
** Last update Thu May  4 15:05:37 2017 maje
*/

typedef struct	s_tag
{
  char	*tag;
  int	tag;
}		t_tag;

static void    add_end(llist **list, int x)
{
  llist *new_el;
  llist *tmp;

  new_el = malloc(sizeof(llist));
  new_el->x = x;
  new_el->next = NULL;
  if (list == NULL)
    new_el = (*list);
  else
    {
      tmp = (*list);
      while (tmp->next != NULL)
	{
	  tmp = tmp->next;
	}
      tmp->next = new_el;
    }
}

int	redirect_tag(int nb, char *str, t_tag **tag)
{
  str = my_strdup(str);
}
