#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include <scn/scn.h>
#include <scn/tuple_return.h>

const std::string PATH = "../../data/day08.txt";
using instruction_t = std::pair<std::string, int>;

std::pair<bool, int> terminates(const std::vector<instruction_t> &code)
{
    size_t pc = 0;
    std::unordered_set<size_t> seen{};
    int acc = 0;

    while (true) {
        if ((pc >= code.size()) || (seen.count(pc) > 0)) {
            break;
        }

        seen.insert(pc);
        const auto &[opcode, arg] = code[pc];
        if (opcode == "acc") {
            acc += arg;
            ++pc;
        } else if (opcode == "jmp") {
            pc += arg;
        } else if (opcode == "nop") {
            ++pc;
        }
    }
    return {pc >= code.size(), acc};
}

int main()
{
    std::vector<instruction_t> code;
    std::ifstream f(PATH);
    std::string line;
    while (std::getline(f, line)) {
        const auto [_, opcode, arg] = scn::scan_tuple<std::string, int>(line, "{} {}");
        code.emplace_back(opcode, arg);
    }

    const auto [_, result_a] = terminates(code);
    std::cout << result_a << std::endl;

    int result_b = 0;
    for (size_t i = 0; i != code.size(); ++i) {
        if (code[i].first == "jmp") {
            code[i].first = "nop";
            const auto [term, acc] = terminates(code);
            if (term) {
                result_b = acc;
                break;
            }
            code[i].first = "jmp";
        }
    }
    std::cout << result_b << std::endl;

    return 0;
}
