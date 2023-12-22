#include "day_20/machine_module.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace aoc
{
    MachineModule::MachineModule() :
        m_type(MachineModuleType::NONE), m_state(MachinePulseType::LOW)
    {
    }

    MachineModule::MachineModule(const std::string& name, const MachineModuleType type) :
        m_name(name), m_type(type), m_state(MachinePulseType::LOW)
    {
    }

    std::vector<MachinePulse> MachineModule::trigger(const MachinePulse& pulse)
    {
        std::vector<MachinePulse> result;

        if (m_type == MachineModuleType::BROADCAST)
        {
            for (const auto& output_name : m_outputs)
            {
                result.emplace_back(m_name, output_name, pulse.type);
            }
        }
        else if (m_type == MachineModuleType::FLIP_FLOP && pulse.type == MachinePulseType::LOW)
        {
            m_state = (m_state == MachinePulseType::LOW) ? MachinePulseType::HIGH : MachinePulseType::LOW;
            for (const auto& output_name : m_outputs)
            {
                result.emplace_back(m_name, output_name, m_state);
            }
        }
        else if (m_type == MachineModuleType::CONJUNCTION)
        {
            m_watching[pulse.source] = pulse.type;

            m_state = MachinePulseType::LOW;
            for (const auto& [_, watched_state] : m_watching)
            {
                if (watched_state != MachinePulseType::HIGH)
                {
                    m_state = MachinePulseType::HIGH;
                    break;
                }
            }

            for (const auto& output_name : m_outputs)
            {
                result.emplace_back(m_name, output_name, m_state);
            }
        }

        return result;
    }

} // aoc
