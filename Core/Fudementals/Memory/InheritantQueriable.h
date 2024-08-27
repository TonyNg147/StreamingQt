#pragma once

#include <IFManipulate.h>
#include <type_traits>
#include <unordered_map>

template<typename... TYPES>
class InheritantQueriable : public TYPES...
{
public:
	InheritantQueriable()
	{
		static_assert(
		    std::is_base_of_v<SInteface, TYPES> && ..., "Type must inherit from SInteface");
		buildCastMap();
	}

	void *toIf(const IFRepresent &if) override
	{
		auto it = m_castMap.find(if);
		if (it == m_castMap.end()) {
			return nullptr;
		} else {
			return *it.second;
		}
	}

private:
	void buildCastMap()
	{
		m_castMap = {{id<TYPES>, reinterpret_cast<void *>(reinterpret_cast<TYPES *>(this))}, ...};
	}

private:
	std::unordered_map<IFRepresent, void *> m_castMap;
}
