#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
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

    while ((pc < code.size()) && (seen.count(pc) == 0)) {
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

auto flipper =
    std::unordered_map<std::string, std::string>{{"jmp", "nop"}, {"nop", "jmp"}};

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
    for (auto &[opcode, _] : code) {
        if (flipper.count(opcode) > 0) {
            opcode = flipper[opcode];
            const auto [term, acc] = terminates(code);
            if (term) {
                result_b = acc;
                break;
            }
            opcode = flipper[opcode];
        }
    }
    std::cout << result_b << std::endl;

    return 0;
}
