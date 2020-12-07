#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

const std::string PATH = "../../data/day07.txt";

using graph_t = std::unordered_map<std::string, std::vector<std::string>>;
using graph_fwd_t =
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>;

std::unordered_set<std::string> counter(const std::string &name, const graph_t &graph)
{
    const auto &deps = graph.find(name)->second;
    auto result = std::unordered_set<std::string>(deps.begin(), deps.end());
    for (const auto &dep : deps) {
        result.merge(counter(dep, graph));
    }
    return result;
}

int contents(const std::string &name, const graph_fwd_t &graph, bool starting = true)
{
    auto result = starting ? 0 : 1;
    const auto &deps = graph.find(name)->second;
    for (const auto &[bag, count] : deps) {
        result += count * contents(bag, graph, false);
    }
    return result;
}

int main()
{
    auto f = std::ifstream{PATH};
    auto line = std::string{};
    auto graph = graph_t{};
    auto graph_fwd = graph_fwd_t{};
    auto match = std::smatch{};

    const auto begin_regex = std::regex("(\\w+ \\w+) bags contain");
    const auto deps_regex = std::regex(" ?(\\d+) (\\w+ \\w+) bags?[,.]");

    while (std::getline(f, line)) {
        std::regex_search(line, match, begin_regex);
        const auto outer_name = match[1];
        auto rest = match.suffix().str();

        auto matches_begin = std::sregex_iterator(rest.begin(), rest.end(), deps_regex);
        auto matches_end = std::sregex_iterator();
        for (auto i = matches_begin; i != matches_end; ++i) {
            std::smatch match = *i;

            graph[outer_name];
            graph[match[2]].emplace_back(outer_name);

            graph_fwd[match[2]];
            graph_fwd[outer_name].emplace_back(match[2], std::stoi(match[1]));
        }
    }

    std::cout << counter("shiny gold", graph).size() << std::endl;
    std::cout << contents("shiny gold", graph_fwd) << std::endl;

    return 0;
}
