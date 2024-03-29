#pragma once
#include "igCore.h"
#include <fstream>
#include <assert.h>

class igFile
{
public:

	enum igSeek
	{
		IGSEEK_SET,
		IGSEEK_CUR,
		IGSEEK_END
	};

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
	inline constexpr void Validate(T* container)
	{
		if constexpr (HasValidation<T>::value) {
			container->Validate();
		}
	}
	
	// This function reads T from buffer. 
	// If T has a function called 'bool Validate(const char* errormsg)' then it executes this function on the struct.
	template<typename T>
	T Read()
	{
		T* pStruct = reinterpret_cast<T*>(GetBuffer());
		m_BufferPos += sizeof(T);
		Validate(pStruct);
		return *pStruct;
	}

	// Reads string from buffer and align to an even number
	char* ReadString()
	{
		const igUInt stringLength = (strlen(GetBuffer()) + 2) & -2; // Align number up to an even one
		char* buffer = GetBuffer();
		m_BufferPos += stringLength;
		return buffer;
	}

	void Seek(igUInt amount, igSeek mode)
	{
		switch (mode)
		{
		case IGSEEK_SET:
			m_BufferPos = amount;
			break;
		case IGSEEK_CUR:
			m_BufferPos += amount;
			break;
		case IGSEEK_END:
			m_BufferPos = m_BufferSize - amount;
			break;
		}
	}

public:

	char* GetBuffer() const { return &m_Buffer[m_BufferPos]; }
	igUInt GetSize() const { return m_BufferSize; }
	igUInt Tell() const { return m_BufferPos; }

private:
	char* m_Buffer;
	igUInt m_BufferSize;
	igUInt m_BufferPos;
};

