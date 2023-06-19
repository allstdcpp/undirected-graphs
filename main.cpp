#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class graph {
public:
    using edges_t = std::vector<std::vector<int>>;
    using value_type = std::vector<std::vector<int>>::value_type;
    using iterator = edges_t::iterator;
    using const_iterator = edges_t::const_iterator;

    graph(int vertices);
    void add_edge(int v, int w);
    iterator begin() { return edges_.begin(); }
    const_iterator end()  const { return edges_.end(); }
    const_iterator begin() const { return edges_.begin(); }
    iterator end() { return edges_.end(); }
    const_iterator cbegin() const { return edges_.cbegin(); }
    const_iterator cend() const { return edges_.cend(); }
    [[nodiscard]] int vertices() const noexcept;
    [[nodiscard]] int edges() const noexcept;
    [[nodiscard]] std::vector<int> const& adjacent_vertices(int v) const noexcept;
private:
    std::vector<std::vector<int>> edges_;
    int vertices_{};
    int edge_count_{};
};

graph::graph(int vertices) 
    : vertices_{vertices} 
{
    edges_.resize(vertices_);
}

void graph::add_edge(int v, int w) {
    edges_[v].push_back(w);
    edges_[w].push_back(v);

    ++edge_count_;
}

std::vector<int> const& graph::adjacent_vertices(int v) const noexcept{
    return edges_[v];
}

int graph::edges() const noexcept {
    return edge_count_;
}

int graph::vertices() const noexcept {
    return vertices_;;
}

std::ostream& operator<< (std::ostream& o, graph const& g) {
    for(auto i = 0; i < g.vertices(); ++i) {
        for(auto const& j : g.adjacent_vertices(i)) {
            o << i << " -> " << j << "\n";
        }
    }
    return o;
}

class depth_first_search {
public:
    depth_first_search(graph const& g, int s)
        : g_{g},
          start_{s}
    {
        visited_.resize(g_.vertices());
        parents_.resize(g_.vertices());

        dfs(s);
    }
    [[nodiscard]] bool exists(int v)  const noexcept {
        auto e = visited_[v];
        return e;
    }
    [[nodiscard]] std::vector<int> path(int v) const noexcept {
        std::vector<int> results;

        if(!exists(v))
            return results;
        
        results.push_back(v);

        auto parent = parents_[v];

        while(parent != start_) {
            results.push_back(parent);
            parent = parents_[parent];
        }

        results.push_back(start_);
        std::reverse(std::begin(results), std::end(results));

        return results;
    }
    ~depth_first_search() = default;
private:

    void dfs(int v) {
        visited_[v] = true;

        for(auto const& e : g_.adjacent_vertices(v) ) {
            if(!visited_[e]) {
                dfs(e);
                parents_[e] = v;
            }
        }
    }

    graph const& g_;
    int start_{};
    std::vector<bool> visited_{};
    std::vector<int> parents_{};
};

class breath_first_search {
public:
    breath_first_search(graph const& graph, int s) 
        : g_{graph},
          start_{s}
    {
        visited_.resize(graph.vertices());
        parents_.resize(graph.vertices());
        distance_.resize(graph.vertices());

        bfs(s); 
    }

    [[nodiscard]] bool exists(int v)  const noexcept {
        auto e = visited_[v];
        return e;
    }

    [[nodiscard]] std::vector<int> path(int v) const noexcept {
        std::vector<int> results;

        if(!exists(v))
            return results;
        
        results.push_back(v);

        auto parent = parents_[v];

        while(parent != start_) {
            results.push_back(parent);
            parent = parents_[parent];
        }

        results.push_back(start_);
        std::reverse(std::begin(results), std::end(results));

        return results;
    }

    ~breath_first_search() = default;
private:

    void bfs(int v) {
        
        std::queue<int> q{};
        q.push(v);
        auto distance = 0;

        visited_[v] = true; 
        distance_[v] = 0; 
        parents_[v] = -1;
        
        while(!q.empty()) {
            auto t = q.front();
            ++distance;
            q.pop();

            for(auto const& e : g_.adjacent_vertices(t)) {
                if(!visited_[e]) {
                    q.push(e);
                    parents_[e] = t;
                    visited_[e] = true;
                    distance_[e] = distance;
                }
            }
        }

    }

    graph const& g_;
    int start_{};
    std::vector<bool> visited_{};
    std::vector<int> parents_{};
    std::vector<int> distance_{};
};

class connected_components {
public:
    connected_components(graph const& graph);
     
private:
    void dfs(int v) {

    }

    graph const& g_;
    std::vector<int> components_ids_;
    std::vector<bool> visited_;
    int count_{};
};

int main(int argc, char** argv) {

    graph g{13};
    g.add_edge(0,5);
    g.add_edge(4,3);
    g.add_edge(0,1);
    g.add_edge(9,12);
    g.add_edge(6,4);
    g.add_edge(5,4);
    g.add_edge(0,2);
    g.add_edge(11,12);
    g.add_edge(9,10);
    g.add_edge(0,6);
    g.add_edge(7,8);
    g.add_edge(9,11);
    g.add_edge(5,3);

    std::cout << g;
    std::cout << std::endl;

    breath_first_search s{g, 0};

    std::cout << "path from 0 -> 3: " << s.exists(3) << std::endl;
    std::cout << "path from 0 -> 7: " << s.exists(7) << std::endl;

    auto path = s.path(3);

    std::cout << "path: (0 - 3): ";

    for(auto const& e: path) {
        std::cout << e << " ";
    }

    std::cout << std::endl;

    return EXIT_SUCCESS;
}
