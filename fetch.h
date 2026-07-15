#pragma once

#define NOMINMAX
#define NOGDI
#define NOUSER

#include <sstream>
#include <vector>

#include <cpr/cpr.h>

struct celestialData
{
	float eccentricity = 0.0f;
	float semiMajorAxisLength = 0.0f;
	float inclination = 0.0f;
	float longitudeAscendingNode = 0.0f;
	float argumentOfPeriapsis = 0.0f;
	float meanAnomoly = 0.0f;
	float meanMotion = 0.0f;
};

cpr::Response apiCall(std::string targetBody)
{
	auto r = cpr::Get(
		cpr::Url{"https://ssd.jpl.nasa.gov/api/horizons.api"},
		cpr::Parameters{
			{"format",      "text"},
			{"COMMAND",     targetBody},          // target body — swap per planet
			{"OBJ_DATA",    "NO"},             // don't need the body-info block
			{"MAKE_EPHEM",  "YES"},
			{"EPHEM_TYPE",  "ELEMENTS"},
			{"CENTER",      "'500@10'"},       // heliocentric
			{"TLIST",       "2451545.0"},    // single JD — a point-in-time, set to JD2000
			{"OUT_UNITS",   "AU-D"},
			{"REF_PLANE",   "ECLIPTIC"},
			{"CSV_FORMAT",  "YES"}             // makes parsing the one output line trivial
	}
	);

	return r;
}

std::vector<float> parse(std::string text)
{
	auto start = text.find("$$SOE");
	auto end = text.find("$$EOE");

	auto offset = start + 5;  // skip "$$SOE"

	std::string line = text.substr(offset, end - offset);

	std::vector<float> fields;
	std::stringstream ss(line);
	std::string token;

	while (std::getline(ss, token, ',')) // getline() returns false at eof
	{
		try
		{
			fields.push_back(std::stof(token));
		}
		catch (...)
		{
			continue;
		}
	}

	return fields;
}

celestialData handleData(std::string celestialBody)
{
	celestialData result;
	auto response = apiCall(celestialBody);
	auto data = parse(response.text);

	result.eccentricity = data[1];
	result.inclination = data[3];
	result.longitudeAscendingNode = data[4];
	result.argumentOfPeriapsis = data[5];
	result.meanMotion = data[7];
	result.meanAnomoly = data[8];
	result.semiMajorAxisLength = data[10];

	return result;
}
