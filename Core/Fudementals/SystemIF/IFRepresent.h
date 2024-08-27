#pragma once
#include <string>

class IFRepresent
{
public:
	IFRepresent() = delete;

	IFRepresent(const char *name)
	    : m_name{name}
	{
	}

	IFRepresent(const IFRepresent &o)
	    : m_name{o.m_name}
	{
	}

	std::string getName() const
	{
		return m_name;
	}

	bool operator==(const IFRepresent &o) const
	{
		return o.m_name == m_name;
	}

	IFRepresent &operator=(const IFRepresent &o)
	{
		m_name = o.m_name;
		return *this;
	}

	bool operator!=(const IFRepresent &o) const
	{
		return !operator==(o);
	}

	bool operator<=(const IFRepresent &o) const
	{
		return m_name <= o.m_name;
	}

private:
	std::string m_name;
};
