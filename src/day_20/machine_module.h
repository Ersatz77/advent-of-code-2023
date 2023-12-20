#ifndef AOC_2023_DAY_20_MACHINE_MODULE_H
#define AOC_2023_DAY_20_MACHINE_MODULE_H

#include <unordered_map>
#include <vector>
#include <string>

namespace aoc
{
    enum class MachinePulseType
    {
        LOW,
        HIGH
    };

    struct MachinePulse
    {
        std::string source;
        std::string destination;
        MachinePulseType type;
    };

    enum class MachineModuleType
    {
        BROADCAST,
        FLIP_FLOP,
        CONJUNCTION,
        NONE
    };

    class MachineModule
    {
    public:
        MachineModule();
        MachineModule(const std::string& name, const MachineModuleType type);

        std::vector<MachinePulse> trigger(const MachinePulse& pulse);

        void add_output(const std::string& name) { m_outputs.push_back(name); }
        void watch(const std::string& name) { m_watching[name] = MachinePulseType::LOW; }

        std::vector<std::string> outputs() const { return m_outputs; }
        std::unordered_map<std::string, MachinePulseType> watching() const { return m_watching; }

    private:
        std::string m_name;
        MachineModuleType m_type;
        MachinePulseType m_state;

        std::vector<std::string> m_outputs;
        std::unordered_map<std::string, MachinePulseType> m_watching;
    };

} // aoc

#endif // !AOC_2023_DAY_20_MACHINE_MODULE_H
