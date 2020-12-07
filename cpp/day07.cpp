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

std::pair<std::string, std::vector<std::pair<std::string, int>>>
parse_line(const std::string &line)
{
    auto match = std::smatch{};
    std::regex_search(line, match, std::regex("(\\w+ \\w+) bags contain"));
    auto name = match[1];
    auto chs = match.suffix().str();
    auto edges = std::vector<std::pair<std::string, int>>{};
    while (
        std::regex_search(chs, match, std::regex(" ?(\\d+) (\\w+ \\w+) bags?[,.]"))) {
        edges.emplace_back(match[2], std::stoi(match[1]));
        chs = match.suffix().str();
    }
    return {name, edges};
}

using graph_t = std::unordered_map<std::string, std::vector<std::string>>;
using graph_fwd_t =
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>;

std::unordered_set<std::string> counter(const std::string &name, const graph_t &graph)
{
    const auto &deps = graph.find(name)->second;
    auto result = std::unordered_set<std::string>(deps.begin(), deps.end());
    for (const auto &bag : deps) {
        result.merge(counter(bag, graph));
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
    while (std::getline(f, line)) {
        auto [name, deps] = parse_line(line);
        for (const auto &[inner_name, amount] : deps) {
            graph[name];
            graph[inner_name].push_back(name);
            graph_fwd[inner_name];
            graph_fwd[name].push_back({inner_name, amount});
        }
    }

    std::cout << counter("shiny gold", graph).size() << std::endl;
    std::cout << contents("shiny gold", graph_fwd) << std::endl;

    return 0;
}
