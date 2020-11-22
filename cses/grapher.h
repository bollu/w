#include<graphviz/cgraph.h>
#include<graphviz/gvc.h>
#include <string>
#include <map>

GVC_t *gvc;
Agraph_t *g;
const char *TMPPATH = "/tmp/graph.dot";
const char *APPLICATION = "xdot";
std::map<int, Agnode_t *> IX2PTR; // map between node indexes and pointers.

void grapher_init() {
    gvc = gvContext();
    g = agopen((char *)"G", Agdirected, nullptr);
    agsafeset(g, (char *)"rankdir", (char *)"TB", (char *)"");
    agsafeset(g, (char *)"fontname", (char *)"monospace", (char *)"");
    agsafeset(g, (char *)"overlap", (char *)"compress", (char *)"");
    agsafeset(g, (char *)"concentrate", (char *)"true", (char *)"");
    // agsafeset(g, (char*)"penwidth", (char*)"3", (char*)"");

}


Agnode_t* grapher_v(int ix, std::string lbl) {
    auto it = IX2PTR.find(ix);
    if (it != IX2PTR.end()) { 
        agset(it->second, "label", strdup(lbl.c_str()));
        return it->second;
    }
    Agnode_t *v = agnode(g, strdup(lbl.c_str()), true);

    // agsafeset(v, (char *)"fontname", (char *)"monospace", (char *)"");
    // agsafeset(v, (char *)"shape", (char *)"none", (char *)"");
    agsafeset(v, (char *)"margin", (char *)"0", (char *)"");

    IX2PTR[ix] = v;
    return v;
};

// uses node index as label.
Agnode_t* grapher_v(int ix) { 
    return grapher_v(ix, std::to_string(ix));
}

Agedge_t* grapher_e(int ix1, int ix2, std::string lbl) {
    return agedge(g, grapher_v(ix1), grapher_v(ix2), lbl.size() ? strdup(lbl.c_str()) : nullptr, true);
};

Agedge_t *grapher_e(int ix1, int ix2) {
    return grapher_e(ix1, ix2, "");
}

void grapher_show() {
    FILE * tempf = fopen(TMPPATH, "w");
    agwrite(g, tempf);
    fclose(tempf);
    
    // run command
    std::string cmd(APPLICATION); cmd += " "; cmd += TMPPATH;
    system(cmd.c_str());

}