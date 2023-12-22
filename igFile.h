#pragma once
#include "igCore.h"
#include <fstream>
#include <assert.h>

class igFile
{
public:

	igFile(const char* filepath)
	{
		std::ifstream file(filepath, std::ios::binary | std::ios::ate);
		m_BufferSize = file.tellg();
		file.seekg(0, std::ios::beg);
		m_Buffer = (char*)malloc(m_BufferSize);
		file.read(m_Buffer, m_BufferSize);
		file.close();
		
		m_BufferPos = 0;
	}

	virtual ~igFile()
	{
		free(m_Buffer);
	}

	template <typename T, typename = int>
	struct HasValidation : std::false_type { };

	template <typename T>
	struct HasValidation <T, decltype(&T::Validate, 0)> : std::true_type { };

	template<typename T>
	inline constexpr bool Validate(T* container, const char*& errormsg)
	{
		if constexpr (HasValidation<T>::value) {
			return container->Validate(errormsg);
		}
		else {
			return true;
		}	
	}
	
	// This function reads a struct from buffer. 
	// If it has a Function called 'bool Validate(const char* errormsg)' then it executes this function on the struct.
	template<typename T>
	T* ReadStruct()
	{
		T* pStruct = reinterpret_cast<T*>(&m_Buffer[m_BufferPos]);
		m_BufferPos += sizeof(T);
		const char* errormsg = "";
		if (!Validate(pStruct, errormsg)) {
			printf(errormsg);
		}
		return pStruct;
	}

protected:

	char* GetBuffer() const { return m_Buffer; }
	igUInt GetSize() const { return m_BufferSize; }
	igUInt Tell() const { return m_BufferPos; }

private:
	char* m_Buffer;
	igUInt m_BufferSize;
	igUInt m_BufferPos;
};

