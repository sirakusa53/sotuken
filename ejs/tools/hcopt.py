import sys
import argparse

class PropertyKey:
    def __init__(self, name, attr):
        self.name = name
        self.attr = attr

    def equal(self, pk):
        return self.name == pk.name and self.attr == pk.attr

    def is_element(self, set):
        for k in set:
            if self.equal(k):
                return True
        return False
    
    def get_name(self):
        return self.name

    def get_attr(self):
        return self.attr

class Transition:
    def __init__(self, src, pk, dst):
        self.src = src
        self.prop_key = pk
        self.dst = dst

    def get_src(self):
        return self.src

    def get_prop_key(self):
        return self.prop_key

    def get_dst(self):
        return self.dst

class Shape:
    def __init__(self, n_embedded_slots, bc_loc, is_cached, population,
                 n_enter, n_leave, is_proto):
        self.is_entry = False
        self.n_embedded_slots = n_embedded_slots
        self.bc_loc = bc_loc
        self.is_cached = is_cached
        self.population = population
        self.n_enter = n_enter
        self.n_leave = n_leave
        self.is_proto = is_proto
        
    def dup(self):
        s = Shape(self.n_embedded_slots,
                  self.bc_loc, self.is_cached, self.population,
                  self.n_enter, self.n_leave, self.is_proto)
        s.is_entry = self.is_entry
        return s

    def get_population(self):
        return self.population

    def add_population(self, population):
        self.population += population
    
    def get_bc_loc(self):
        return self.bc_loc
        
class Property:
    def __init__(self, index, pk):
        self.index = index
        self.prop_key = pk

    def equal(self, p):
        if self.index != p.index:
            return False
        return self.prop_key.equal(p.get_key())
        
    def get_key(self):
        return self.prop_key

#    def get_name(self):
#        return self.prop_key.get_name()

class Node:
    InternalID = 1
    def __init__(self, id, name, raw_addr, n_props, n_special_props):
        self.id = id
        self.name = name
        self.raw_addr = raw_addr
        self.n_props = n_props
        self.n_special_props = n_special_props
        self.internal_id = Node.InternalID
        Node.InternalID += 1
        self.props = []
        self.shapes = []
        self.transitions = []

    def dup(self):
        n = Node(self.id, self.name, self.raw_addr,
                 self.n_props, self.n_special_props)
        n.props = [p for p in self.props]
        n.start_index = self.start_index
        return n

    def compute_start_index(self):
        self.start_index = self.n_props - len(self.props)
    
    def add_prop(self, p):
        self.props.append(p)

    def get_props(self):
        return self.props

    def get_last_prop(self):
        return self.props[-1]
    
    def set_props(self, props):
        self.props = props

    def get_id(self):
        return self.id

    def get_key(self):
        return self.id
    
    def add_shape(self, s):
        self.shapes.append(s)

    def add_shapes(self, slist):
        for s in slist:
            self.add_shape(s)

    def remove_all_shapes(self):
        self.shapes = []

    def get_shapes(self):
        return self.shapes

    def find_shape_by_bc_loc(self, bc_loc):
        ret = []
        for s in self.get_shapes():
            if s.bc_loc == bc_loc:
                ret.append(s)
        return ret

    def add_transition(self, t):
        self.transitions.append(t)

    def add_transition2(self, pk, dst):
        t = Transition(self, pk, dst)
        self.add_transition(t)

    def remove_all_transitions(self):
        self.transitions = []

    def get_transitions(self):
        return self.transitions

    def get_next_nodes(self):
        return [e.get_dst() for e in self.get_transitions()]

    def get_next_node(self, prop_name):
        for t in self.transitions:
            if (t.get_prop_name() == prop_name):
                return t.get_dst()
        return None

    def get_population(self):
        p = 0
        n_ordinary = 0
        for s in self.shapes:
            if not s.is_proto:
                n_ordinary += 1
            p += s.get_population()
        assert(n_ordinary <= 1)
        return p

    def add_population(self, population):
        ordinary_shapes = [s for s in self.shapes if not s.is_proto]
        if len(ordinary_shapes) == 1:
            ordinary_shapes[0].add_population(population)
        else:
            print("????? something wrong ?????")
            print(ordinary_shapes)
            self.shapes[0].add_population(population)

    def to_short_string(self):
        props = "{" + " ".join([p.name for p in self.props]) + "}"
        if self.bc_loc:
            return ("%d [%d %d] %s %s" %
                    (self.id, self.bc_loc[0], self.bc_loc[1], self.name, props))
        else:
            return ("%d [-1 -1] %s %s" % (self.name, self.id, props))

######
###### Parser
######
        
address_dict = {}
        
def parse_bc_loc(fun, pc):
    if fun == '-1' and pc == '-1':
        return None
    return (int(fun), int(pc))

def parse_property_map(line):
    xs = line.split(' ')
    raw_addr = xs[1]
    name = xs[11]
    n_props = int(xs[12])
    node_id = int(xs[13])
    n_special_props = int(xs[14])
    n = Node(node_id, name, raw_addr, n_props, n_special_props)
    n.is_root = xs[2] == 'R'
#    n.bc_loc = parse_bc_loc(xs[5], xs[6])
    address_dict[n.raw_addr] = n
    return n

def parse_property(line):
    xs = line.split(' ')
    index = int(xs[2])
    name = xs[3]
    attr = int(xs[4])
    p = Property(index, PropertyKey(name, attr))
    return p

def parse_shape(line):
    xs = line.split(' ')
    n_embedded_slots = int(xs[2])
    bc_loc = parse_bc_loc(xs[3], xs[4])
    is_cached = xs[5] == 'C'
    population = int(xs[6])
    n_enter = int(xs[7])
    n_leave = int(xs[8])
    is_proto = xs[9] == "1"
    s = Shape(n_embedded_slots, bc_loc, is_cached, population, n_enter, n_leave, is_proto)
    return s

def parse_transition(line):
    xs = line.split(' ')
    src = address_dict[xs[1]]
    prop_name = xs[2]
    dst = address_dict[xs[3]]
    last_prop_key = dst.get_last_prop().get_key()
    assert(last_prop_key.get_name() == prop_name)
    return Transition(src, last_prop_key, dst)

def parse_file(file):
    nodes = []
    roots = []
    transition_lines = []
    
    with open(file) as f:
        current_node = None
        for line in f:
            line = line.strip()
            if line.startswith('HC '):
                n = parse_property_map(line)
                current_node = n
                nodes.append(n)
                if n.is_root:
                    roots.append(n)
            elif line.startswith('PROP '):
                p = parse_property(line)
                current_node.add_prop(p)
            elif line.startswith('SHAPE '):
                s = parse_shape(line)
                current_node.add_shape(s)
            elif line.startswith('TRANSITION '):
                transition_lines.append(line)
            else:
                print("??? " + line)
    for n in nodes:
        n.compute_start_index()

    for line in transition_lines:
        t = parse_transition(line)
        t.src.add_transition(t)

    return roots

######
###### DOT Printer
######

class DOTPrinter:
    ROOT_ID = 10000
    
    def __init__(self, filename):
        self.filename = filename
       
    def dot_output_vertex(self, id, label):
        self.f.write("%d [label=\"%s\"]\n" % (id, label))

    def dot_output_edge(self, f, t, label):
        if label:
            self.f.write("%d -> %d [label=\"%s\"]\n" % (f, t, label))
        else:
            self.f.write("%d -> %d\n" % (f, t))

    def is_hidden(self, n):
        return False

    def output_pm_node(self, n):
        option = {}
        # name
        if n.name[0] != '(':
            label = n.name + "\n"
        else:
            label = ""
        # ID
        label += "[%d]" % n.id
        # property
        if len(n.get_props()) == 0:
            label += "(no props)"
        else:
            label += "%d %s" % (len(n.get_props()),
                                n.get_props()[-1].get_key().get_name())
        # shape
        for s in n.get_shapes():
#            if s.bc_loc:
#                label += ("\n %s %d %d %d" %
#                          (str(s.bc_loc), s.population, s.n_enter, s.n_leave))
#            else:
#                label += ("\n (int) %d %d %d" %
#                          (s.population, s.n_enter, s.n_leave))
            if s.bc_loc:
                label += ("\n %s %d" %
                          (str(s.bc_loc), s.population))
            else:
                label += ("\n (init) %d" %
                          (s.population))
            if s.is_proto:
                label += " (proto)"
            if s.is_entry:
                label += " E"
        self.dot_output_vertex(n.id, label)
        
    def output_subgraph(self, n, visited):
        if n.get_key() in visited:
            return
        visited[n.get_key()] = True

        self.output_pm_node(n)

        for t in n.get_transitions():
            if not self.is_hidden(t.dst):
                self.dot_output_edge(n.id, t.dst.id,
                                     t.get_prop_key().get_name())
                self.output_subgraph(t.dst, visited)

    def output_graph(self, roots):
        visited = {}
        self.dot_output_vertex(DOTPrinter.ROOT_ID, "(root)")
        for n in roots:
            if not self.is_hidden(n):
                self.dot_output_edge(DOTPrinter.ROOT_ID, n.id, None)
                self.output_subgraph(n, visited)

    def output(self, roots):
        with open(self.filename, "w") as f:
            self.f = f
            self.f.write("digraph G {\n")
            self.output_graph(roots)
            self.f.write("}\n")

class PDFPrinter(DOTPrinter):
    def __init__(self, filename):
        if filename.endswith(".pdf"):
            filename = filename[:-4]
        self.filename = filename
    
    def dot_output_vertex(self, id, label):
        self.g.node(str(id), label=label)

    def dot_output_edge(self, f, t, label):
        if label:
            self.g.edge(str(f), str(t), label=label)
        else:
            self.g.edge(str(f), str(t))

    def output(self, roots):
        from graphviz import Digraph
        self.g = Digraph(format='pdf')
        self.output_graph(roots)
        self.g.render(self.filename)

######
###### OHC Printer
######

class OHCPrinter:
    """
    OHC ::= G #nodes #edges #shapes #pretranses \n
            <node>+ <edge>* <shape>+ <pretrans>+
    <node> ::= N <id> <is_root> #props #edges #special_props start_index \n <prop>*
    <is_root> ::= 0 | 1
    <prop> ::= P <name> <attr>\n
    <edge> ::= E <src node id> <dst node id> <name> \n
    <shape> ::= S <node id> <alloc site> <num props> <is proto>\n
    <alloc site> ::= <fun> <pc>
    <is proto> ::= 0 | 1
    <pretrans> ::= A <node id> <alloc site> \n

    Note that #props does not include special properties, unlike
    PropertyMap.n_props in VM. Thus, the number of slots in an object
    is max(start_index + #props, #special_props + 1).
    """

    def compute_n_embedded_slots(self, n):
        def rec(n, n_slots):
            n.n_embedded_slots = n_slots
            for nn in n.get_next_nodes():
                rec(nn, n_slots)
        n_slots = max(n.start_index + len(n.get_props()),
                      n.n_special_props + 1)
        rec(n, n_slots)
    
    def collect_nodes_and_edges_rec(self, n, edges, visited):
        if n.get_key() in visited:
            return
        visited[n.get_key()] = n
        
        for t in n.get_transitions():
            edges.append(t)
            self.collect_nodes_and_edges_rec(t.dst, edges, visited)
    
    def collect_nodes_and_edges(self, roots):
        for n in roots:
            self.compute_n_embedded_slots(n)
        
        visited = {}
        edges = []
        for n in roots:
            self.collect_nodes_and_edges_rec(n, edges, visited)
        nodes = [visited[i] for i in sorted(visited.keys())]
        return nodes, edges
    
    def output(self, f, roots):
        nodes, edges = self.collect_nodes_and_edges(roots)
        shapes = [(s, n) for n in nodes for s in n.get_shapes()]
        pretranses = [(s, n) for s, n in shapes if s.is_entry]

        # <property map graph>
        # #nodes #edges
        f.write("G %d %d %d %d\n" %
                (len(nodes), len(edges), len(shapes), len(pretranses)))
        # <node>+
        for n in nodes:
            props = n.get_props()
            n_transes = len(n.get_transitions())
            is_root = 1 if n in roots else 0
            f.write("N %d %d %d %d %d %d\n" %
                    (n.id, is_root, len(props), n_transes,
                     n.n_special_props, n.start_index))
            for p in props:
                f.write("P %d %s\n" % (p.get_key().get_attr(),
                                       p.get_key().get_name()))
        # <edge>*
        for t in edges:
            f.write("E %d %d %s\n" % (t.src.id, t.dst.id,
                                      t.get_prop_key().get_name()))
        # <shape>+
        for s, n in shapes:
            is_proto = 1 if s.is_proto else 0
            if s.bc_loc == None:
                f.write("S %d -2 -2 %d %d\n" % (n.id, n.n_embedded_slots, is_proto))
            else:
                f.write("S %d %d %d %d %d\n" % (n.id, s.bc_loc[0], s.bc_loc[1], n.n_embedded_slots, is_proto))
        # <pretrans>+
        for s, n in pretranses:
            f.write("A %d %d %d\n" % (n.id, s.bc_loc[0], s.bc_loc[1]))
            
#####
##### Optimizer
#####

class Optimizer:
    BRANCH_THRESHOLD = 0.8

    def __init__(self, args):
        pass
    
    def collect_monomorphic_alloc_sites(self, roots):
        """ enumerate monomorphic alloc sites

        Args:
            roots: root nodes of a property map graph.

        Returns:
            A dict mapping {bc_loc => (Node, Shape)} where
            Node is an entrypoint of the given graph for the
            allocation site `bc_loc', and Shape belongs to Node and
            Shape's location is `bc_loc'.
        """

        alloc_sites = {} # {bc_loc => (Node, Shape)}
        for n in roots:
            for s in n.get_shapes():
                print(str(s.bc_loc) + " " + str(s.is_proto))
                if s.bc_loc:
                    if s.bc_loc not in alloc_sites:
                        alloc_sites[s.bc_loc] = n
                    elif alloc_sites[s.bc_loc] == n:
                        continue
                    else:
                        # polymorphic alloc site
                        print("polymorphic alloc site (%d %d)" % s.bc_loc)
                        alloc_sites[s.bc_loc] = False

        return {x: alloc_sites[x] for x in alloc_sites.keys()
                if alloc_sites[x] != False}

    def separate_site_specific_tree(self, bc_loc, n):
        sep_node = n.dup()
        sep_node.add_shapes(n.find_shape_by_bc_loc(bc_loc))
        for e in n.get_transitions():
            pk = e.get_prop_key()
            m = e.get_dst()
            if len(m.find_shape_by_bc_loc(bc_loc)) > 0:
                sep_m = self.separate_site_specific_tree(bc_loc, m)
                sep_node.add_transition2(pk, sep_m)
        return sep_node

    def postpone_branches(self, n):
        def accum_weight(n, weight):
            w = n.get_population()
            for m in n.get_next_nodes():
                w += accum_weight(m, weight)
            weight[n.get_id()] = w
            return w
        def find_major_transition(n):
            for e in n.get_transitions():
                m = e.get_dst()
                if (weight[m.get_id()] >
                    weight[n.get_id()] * Optimizer.BRANCH_THRESHOLD):
                    return e
            return None
        def remove_double_props(e, extra_props):
            """ Remove all edges adding a property in extra_props and shortcut
                their destination nodes.

                Args:
                    e: a transition to the entry point.

                Returns:
                    a pair of edges and population, where
                    edges are list of entrypoint edges and
                    population is the population to be added the source node.
            """

            # process subtrees
            population = 0
            edges = []
            n = e.get_dst()
            for next_edge in n.get_transitions():
                es, p = remove_double_props(next_edge, extra_props)
                edges += es
                population += p

            if e.get_prop_key().is_element(extra_props):
                # remove this transition
                return edges, population + n.get_population()
            else:
                # keep this transition
                n.remove_all_transitions()
                for next_edge in edges:
                    n.add_transition2(next_edge.get_prop_key(),
                                      next_edge.get_dst())
                    n.add_population(population)
                return [e], 0
        def move_edges(e, moving_edges):
            """ Destructively moves edges in moving_edges to the lower
                branching node in e.
            
                Args:
                    e: a transition to the entrypoint
                    moving_edges: list of edges to be added to the
                    highest lower branching node in e.

                Returns:
                    None
            """
            
            n = e.get_dst()
            extra_props = [e.get_prop_key()]
            while len(n.get_transitions()) == 1:
                # TODO: add n_enter and n_leave
                #
                e = n.get_transitions()[0]
                n = e.get_dst()
                extra_props.append(e.get_prop_key())

            # Properties in extra_props are already added. Remove
            # transitions to add them.
            edges = []
            population = 0
            for moving_edge in moving_edges:
                es, p = remove_double_props(moving_edge, extra_props)
                edges += es
                population += p

            # Add the collected edges
            n.add_population(p)
            for edge in edges:
                n.add_transition2(edge.get_prop_key(), edge.get_dst())
        def rec(n):
            # skip non-branching nodes
            while len(n.get_transitions()) == 1:
                n = n.get_next_nodes()[0]
            e = find_major_transition(n)
            if e:
                moving_edges = [x for x in n.get_transitions() if x != e]
                n.remove_all_transitions()
                n.add_transition(e)
                move_edges(e, moving_edges)
                rec(n)
            else:
                for next_node in n.get_next_nodes():
                    rec(next_node)
        def recompute_properties(n, props):
            n.set_props(props)
            for e in n.get_transitions():
                pk = e.get_prop_key()
                m = e.get_dst()
                p = Property(len(props), pk)
                recompute_properties(m, props + [p])
                    
        weight = {} # {node.id => weight}
        accum_weight(n, weight)
        rec(n)
        recompute_properties(n, n.get_props())

    def merge_trees(self, roots):
        def is_same_props(ps1, ps2):
            if len(ps1) != len(ps2):
                return False
            for i in range(len(ps1)):
                p1 = ps1[i]
                p2 = ps2[i]
                if not p1.equal(p2):
                    return False
            return True
        
        def is_equivalent_subtrees(n, m):
            if not is_same_props(n.get_props(), m.get_props()):
                return False
            if len(n.get_transitions()) != len(m.get_transitions()):
                return False
            if n.n_special_props != m.n_special_props:
                return False
            for t in n.get_transitions():
                mm = m.get_next_node(t.get_prop_name())
                if not mm:
                    return False
                if not is_equivalent_subtrees(t.get_dst(), mm):
                    return False
            return True

        def copy_shapes(n, m):
            """
            copy shapes m -> n
            """
            n.add_shapes(m.get_shapes())
            for t in n.get_transitions():
                copy_shapes(t.get_dst(), m.get_next_node(t.get_prop_name()))

        def try_merge(new_roots, n):
            for m in new_roots:
                if is_equivalent_subtrees(n, m):
                    copy_shapes(m, n)
                    return True
            return False
                  
        # TODO: bottom-up
        new_roots = []
        for n in roots:
            if not try_merge(new_roots, n):
                new_roots.append(n)

        return new_roots

    def skip_intermediate_nodes(self, n):
        while len(n.get_transitions()) == 1:
            n = n.get_transitions()[0].get_dst()
        nn = n.dup()
        for t in n.get_transitions():
            pk = t.get_prop_key()
            dst = t.get_dst()
            dst = self.skip_intermediate_nodes(dst)
            nn.add_transition2(pk, dst)
        for s in n.get_shapes():
            nn.add_shape(s)
        return nn
    
    def optimize(self, roots):
        """
        input: Array of roots of disjoint trees.
        output: Array of roots of DAGs. DAGs of two nodes can intersect.
        """

        alloc_sites = self.collect_monomorphic_alloc_sites(roots)
        print(alloc_sites.keys())
        
        separate_roots = {}
        for bc_loc in alloc_sites.keys():
            if JSON2:
                if bc_loc != (28, 13):
                    continue
            n = alloc_sites[bc_loc]
            sroot = self.separate_site_specific_tree(bc_loc, n)
            separate_roots[bc_loc] = sroot


        for bc_loc in separate_roots.keys():
            n = separate_roots[bc_loc]
            self.postpone_branches(n)
            separate_roots[bc_loc] = n

        for bc_loc in separate_roots.keys():
            n = separate_roots[bc_loc]
            n = self.skip_intermediate_nodes(n)
            separate_roots[bc_loc] = n
            
        roots = self.merge_trees(separate_roots.values())

        for n in roots:
            for s in n.get_shapes():
                s.is_entry = True
        
        print(roots)
        
        return roots

    
def rename_id_rec(n, next_id, rename_map, visited):
    if n in visited:
        return next_id
    visited.append(n)

    rename_map[n.id] = next_id
#    print("rename %d -> %d" % (n.id, next_id))
    n.id = next_id
    next_id += 1
    
    for t in n.get_transitions():
        next_id = rename_id_rec(t.dst, next_id, rename_map, visited)

    return next_id

def rename_id(roots):
    rename_map = {}
    visited = []
    next_id = 1
    for n in roots:
#        print("rename root %d" % n.id)
        next_id = rename_id_rec(n, next_id, rename_map, visited)
    return rename_map

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("input", type = str)
    ap.add_argument("--dot", action = "store", type = str)
    ap.add_argument("--pdf", action = "store", type = str)
    ap.add_argument("--keep-id", action = "store_true")
    ap.add_argument("--no-optimize", action = "store_true")
    ap.add_argument("--json2", action = "store_true")
    ap.add_argument("--ohc", action = "store", type = str)
    args = ap.parse_args()

    roots = parse_file(args.input)

    global JSON2
    if args.json2:
        JSON2 = True
    else:
        JSON2 = False

    if not args.no_optimize:
        o = Optimizer(args)
        roots = o.optimize(roots)
    if not args.keep_id:
        rename_id(roots)
    
    if args.dot:
        if args.dot.endswith(".pdf"):
            p = PDFPrinter(args.dot)
        else:
            p = DOTPrinter(args.dot)
        p.output(roots)

    if args.pdf:
        p = PDFPrinter(args.pdf)
        p.output(roots)
        
    if args.ohc:
        with open(args.ohc, "w") as f:
            printer = OHCPrinter()
            printer.output(f, roots)

main()
