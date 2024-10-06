/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#include "prefix.h"
#define EXTERN extern
#include "header.h"

#ifdef LOAD_HCG

struct loaded_pm {
  PropertyMap *pm;
  Shape *proto_os;
  int as_fun;
  int as_pc;
};

static struct loaded_pm* loaded_pms;
static int n_loaded_pms;

void install_pretransition_hidden_class()
{
  int i;
  for (i = 0; i < n_loaded_pms; i++) {
    AllocSite *as;
    PropertyMap *pm;
    int n_embedded_slots;
    if (loaded_pms[i].as_fun < 0)
      /* builtin classes */
      continue;
    pm = loaded_pms[i].pm;
    as = &INSN_CACHE(loaded_pms[i].as_fun, loaded_pms[i].as_pc).alloc_site;
    n_embedded_slots = pm->n_props == 0 ? 1 : pm->n_props;
    as->shape = property_map_find_shape(pm, n_embedded_slots, 0, 0);
    as->pm = pm;
    assert(as->shape != NULL);
  }
}

PropertyMap *find_loaded_property_map(int builtin_id)
{
  int i;
  for (i = 0; i < n_loaded_pms; i++)
    if (loaded_pms[i].as_fun == -1 && loaded_pms[i].as_pc == builtin_id)
      return loaded_pms[i].pm;
  assert(0);
  return NULL;
}

Shape *find_loaded_prototype_os(int builtin_id)
{
  int i;
  for (i = 0; i < n_loaded_pms; i++)
    if (loaded_pms[i].as_fun == -1 && loaded_pms[i].as_pc == builtin_id)
      return loaded_pms[i].proto_os;
  assert(0);
  return NULL;
}

/*
 * load optimized hidden class
 */
void load_hcg(Context *ctx, char *filename)
{
  FILE *fp;
  char _buf[1000], * buf = _buf + 2;
  int n_pms, n_trans, n_shapes, n_pretrans;
  int i;
  PropertyMap **pms;
  Shape **proto_oss;
  int line = 0;
  
#define NEXT_LINE(c) do {                         \
    line++;                                       \
    if (fgets(_buf, sizeof _buf, fp) == NULL) {   \
      LOG_ERR("broken ohc file");                 \
      exit(1);                                    \
    }                                             \
    assert(_buf[0] == c && _buf[1] == ' ');       \
  } while(0)
  
  if ((fp = fopen(filename, "r")) == NULL)
    LOG_ERR("load_hcg");

  NEXT_LINE('G');
  sscanf(buf, "%d %d %d %d", &n_pms, &n_trans, &n_shapes, &n_pretrans);
  pms = (PropertyMap **) alloca(sizeof(PropertyMap*) * n_pms);
  proto_oss = (Shape **) alloca(sizeof(Shape*) * n_pms);
               
  /* property maps */
  for (i = 0; i < n_pms; i++) {
    int id, is_root, n_user_props, n_edges, n_special_props, start_index;
    int n_props;
    uint8_t flags = PM_FLAG_REUSE;
    PropertyMap *pm;
    int j;

    NEXT_LINE('N');
    sscanf(buf, "%d %d %d %d %d %d",
           &id, &is_root, &n_user_props, &n_edges,
           &n_special_props, &start_index);
    assert(id - 1 == i);
    if (is_root)
      flags |= PM_FLAG_ROOT;
    n_props = start_index + n_user_props;
#ifdef DEBUG
    {
      char *name = (char *) malloc(10);
      sprintf(name, "reuse%d", id);
      pms[i] = pm = new_property_map(ctx, DEBUG_NAME(name),
                                     n_special_props, n_props,
                                     n_special_props - start_index, JS_EMPTY,
                                     flags);
    }
#else /* DEBUG */    
    pms[i] = pm = new_property_map(ctx, DEBUG_NAME("reuse"),
                                   n_special_props, n_props,
                                   n_special_props - start_index, JS_EMPTY,
                                   flags);
#endif /* DEBUG */
    proto_oss[i] = NULL;

    /* properties */
    for (j = 0; j < n_user_props; j++) {
      char *p, *q;
      Attribute attr;
      JSValue name;
      NEXT_LINE('P');
      for (p = buf; *p != ' '; p++)
        ;
      *p++ = '\n';
      attr = atoi(buf);
      for (q = p; *q != '\n'; q++)
        ;
      *q = '\0';
      name = cstr_to_string(ctx, p);
      property_map_add_property_entry(ctx, pm, name,
                                      start_index + j, attr);
    }
  }

  /* transitions */
  for (i = 0; i < n_trans; i++) {
    int src_id, dst_id;
    PropertyMap *src, *dst;
    JSValue name;
    int n;
    char *p;
    NEXT_LINE('E');
    sscanf(buf, "%d %d%n", &src_id, &dst_id, &n);
    src = pms[src_id - 1];
    dst = pms[dst_id - 1];
    for (p = buf + n; *p != '\n'; p++)
      ;
    *p = '\0';
    name = cstr_to_string(ctx, buf + n + 1);
    property_map_add_transition(ctx, src, name, dst);
  }

  /* shapes */
  for (i = 0; i < n_shapes; i++) {
    int pm_id, as_fun, as_pc;
    PropertyMap *pm;
    int n_embedded_slots;
    int n_extension;
    int is_proto;
    NEXT_LINE('S');
    sscanf(buf, "%d %d %d %d %d",
           &pm_id, &as_fun, &as_pc, &n_embedded_slots, &is_proto);
    pm = pms[pm_id - 1];
    assert(n_embedded_slots >= 1);
    if (pm->n_props <= n_embedded_slots)
      n_extension = 0;
    else
      n_extension = pm->n_props - n_embedded_slots + 1;
#ifdef DEBUG
    if (is_proto) {
      char *name = (char *) malloc(20);
      sprintf(name, "reuse-proto%d,%d", as_fun, as_pc);
      proto_oss[pm_id - 1] =
          new_object_shape(ctx, DEBUG_NAME(name), pm,
                           n_embedded_slots, n_extension, 1);
    } else {
      char *name = (char *) malloc(20);
      sprintf(name, "reuse%d,%d", as_fun, as_pc);
        new_object_shape(ctx, DEBUG_NAME("reuse"), pm,
                         n_embedded_slots, n_extension, 0);
    }
#else /* DEBUG */
    if (is_proto)
      proto_oss[pm_id - 1] =
        new_object_shape(ctx, DEBUG_NAME("reuse-proto"), pm,
                         n_embedded_slots, n_extension, 1);
    else
      new_object_shape(ctx, DEBUG_NAME("reuse"), pm,
                       n_embedded_slots, n_extension, 0);
#endif /* DEBUG */
  }

  /* pre-transitions */
  loaded_pms =
    (struct loaded_pm*) malloc(sizeof(struct loaded_pm) * n_pretrans);
  n_loaded_pms = n_pretrans;
  for (i = 0; i < n_pretrans; i++) {
    int pm_id, as_fun, as_pc;
    PropertyMap *pm;
    NEXT_LINE('A');
    sscanf(buf, "%d %d %d", &pm_id, &as_fun, &as_pc);
    pm = pms[pm_id - 1];
    loaded_pms[i].as_fun = as_fun;
    loaded_pms[i].as_pc = as_pc;
    loaded_pms[i].pm = pm;
    loaded_pms[i].proto_os = proto_oss[pm_id - 1];
  }
#undef NEXT_LINE
  
  fclose(fp);
}


#endif /* LOAD_HCG */

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
