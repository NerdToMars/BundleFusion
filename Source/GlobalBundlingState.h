#pragma once

#include "stdafx.h"

#include <vector>
#include <string>
#include <list>


#define X_GLOBAL_BUNDLING_APP_STATE_FIELDS \
	X(bool, s_enableDetailedTimings) \
	X(unsigned int, s_maxNumImages) \
	X(unsigned int, s_submapSize) \
	X(unsigned int, s_widthSIFT) \
	X(unsigned int, s_heightSIFT) \
	X(unsigned int, s_maxNumKeysPerImage) \
	X(unsigned int, s_maxNumCorrPerImage) \
	X(unsigned int, s_numNonLinIterations) \
	X(unsigned int, s_numLinIterations) \
	X(unsigned int, s_downsampledWidth) \
	X(unsigned int, s_downsampledHeight) \
	X(std::string, s_outputDirectory) 

using namespace ml;

#ifndef VAR_NAME
#define VAR_NAME(x) #x
#endif

#define checkSizeArray(a, d)( (((sizeof a)/(sizeof a[0])) >= d))

class GlobalBundlingState
{
public:

#define X(type, name) type name;
	X_GLOBAL_BUNDLING_APP_STATE_FIELDS
#undef X

		//! sets the parameter file and reads
		void readMembers(const ParameterFile& parameterFile) {
		m_ParameterFile = parameterFile;
		readMembers();
	}

	//! reads all the members from the given parameter file (could be called for reloading)
	void readMembers() {
#define X(type, name) \
	if (!m_ParameterFile.readParameter(std::string(#name), name)) {MLIB_WARNING(std::string(#name).append(" ").append("uninitialized"));	name = type();}
		X_GLOBAL_BUNDLING_APP_STATE_FIELDS
#undef X


			m_bIsInitialized = true;
	}

	void print() const {
#define X(type, name) \
	std::cout << #name " = " << name << std::endl;
		X_GLOBAL_BUNDLING_APP_STATE_FIELDS
#undef X
	}

	static GlobalBundlingState& getInstance() {
		static GlobalBundlingState s;
		return s;
	}
	static GlobalBundlingState& get() {
		return getInstance();
	}


	//! constructor
	GlobalBundlingState() {
		m_bIsInitialized = false;
	}

	//! destructor
	~GlobalBundlingState() {
	}

	Timer	s_Timer;

private:
	bool			m_bIsInitialized;
	ParameterFile	m_ParameterFile;
};