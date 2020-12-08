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

int main()
{
    std::vector<instruction_t> code;
    std::ifstream f(PATH);
    std::string line;
    while (std::getline(f, line)) {
        const auto [_, opcode, arg] = scn::scan_tuple<std::string, int>(line, "{} {}");
        code.emplace_back(opcode, arg);
    }

    size_t pc = 0;
    std::unordered_set<size_t> seen{};
    int acc = 0;

    while (true) {
        if (seen.count(pc) > 0) {
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

    std::cout << acc << std::endl;
    return 0;
}
