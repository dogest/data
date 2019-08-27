#include <stdio.h>
#include <stdlib.h>

struct vertex;

struct edge
{
  struct vertex *dest;
  struct edge *next;
  unsigned component;
};

struct vertex
{
  unsigned id;
  unsigned comp_entry;
  struct edge *nbrs;
};

struct graph
{
  unsigned n_vertices;
  struct vertex *vertices;
};

static void
add_half (struct graph *g, unsigned x, unsigned y)
{
  struct edge *e = (struct edge *) malloc (sizeof (struct edge));

  e->dest = g->vertices + y;
  e->next = g->vertices[x].nbrs;
  g->vertices[x].nbrs = e;
}

static void
add_edge (struct graph *g, unsigned x, unsigned y)
{
  add_half (g, x, y);
  add_half (g, y, x);
}

static struct graph *
new_graph (unsigned n_vertices)
{
  struct graph *ret = (struct graph *) malloc (sizeof (struct graph));

  ret->n_vertices = n_vertices;
  ret->vertices = (struct vertex *) calloc (n_vertices, sizeof (struct vertex));

  return ret;
}

static void
free_graph (struct graph *g)
{
  unsigned i;
  struct edge *e, *next;

  for (i = 0; i < g->n_vertices; i++)
    for (e = g->vertices[i].nbrs; e; e = next)
      {
	next = e->next;
	free (e);
      }
  free (g->vertices);
  free (g);
}

static struct graph *
load_graph (void)
{
  struct graph *ret;
  unsigned n_edges, i, x, y, n;

  scanf ("%d%d", &n, &n_edges);

  if (!n)
    return NULL;

  ret = new_graph (n);
  for (i = 0; i < n_edges; i++)
    {
      scanf ("%d%d", &x, &y);
      if (x >= n
	  || y >= n)
	abort ();
      add_edge (ret, x,y);
    }

  return ret;
}

static unsigned
mark_2con_entries (struct vertex *v, struct vertex *from, unsigned *actn, unsigned *actcomp)
{
  unsigned ret, reach, scc;
  struct edge *e;

  if (v->id)
    return v->id;

  ret = (*actn)++;
  v->id = ret;
  for (e = v->nbrs; e; e = e->next)
    {
      if (e->dest == from)
	continue;

      scc = *actn;
      reach = mark_2con_entries (e->dest, v, actn, actcomp);

      if (reach < ret)
	ret = reach;
      else if (reach == v->id
	       || reach == scc)
	e->component = (*actcomp)++;
    }

  return ret;
}

static unsigned
mark_2con_comp (struct graph *g)
{
  unsigned i, n = 1, ncomp = 0, simple_comp = 0;
  struct edge *e;

  for (i = 0; i < g->n_vertices; i++)
    {
      g->vertices[i].id = 0;
      for (e = g->vertices[i].nbrs; e; e = e->next)
	e->component = ~0u;
    }

  for (i = 0; i < g->n_vertices; i++)
    if (g->vertices[i].id == 0)
      {
	g->vertices[i].comp_entry = 1;
	mark_2con_entries (g->vertices + i, NULL, &n, &ncomp);
	simple_comp++;
      }

  return simple_comp;
}

unsigned
num_2con_entries (struct vertex *v)
{
  struct edge *e;
  unsigned n = 0;

  for (e = v->nbrs; e; e = e->next)
    if (e->component != ~0u)
      n++;

  return n + 1 - v->comp_entry;
}

int
main(void)
{
  struct graph *g;
  unsigned i, simple_comp, max, ac;

  while (1)
    {
      g = load_graph ();
      if (!g)
  	return 0;

      simple_comp = mark_2con_comp (g);
      max = 0;

      for (i = 0; i < g->n_vertices; i++)
	{
	  ac = simple_comp + num_2con_entries (g->vertices + i) - 1;

	  if (ac > max)
	    max = ac;
	}
      free_graph (g);
      printf ("%d\n", max);
    }
}

