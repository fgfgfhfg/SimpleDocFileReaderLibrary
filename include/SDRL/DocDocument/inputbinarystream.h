#ifndef INPUTBINARYSTREAM_H
#define INPUTBINARYSTREAM_H

#include <iostream>
template<typename CT = char>
class InputBinaryStream
{
private:
	std::basic_istream<CT>& _stream;

public:
    InputBinaryStream(std::basic_istream<CT>& stream)
		: _stream(stream) {}

    template<typename T>
    inline T getData()
    {
        T result;
		_stream.read(reinterpret_cast<CT*>(&result), sizeof(T) / sizeof(CT));
        return result;
    }

    template<typename T>
    inline T getData(size_t offset)
    {
		_stream.seekg(offset, std::ios_base::beg);
        T result = getData<T>();
        return result;
    }

    template<typename T>
    inline T peekData()
    {
        auto oldOffset = _stream.tellg();
        T result = getData<T>();
		_stream.seekg(oldOffset, std::ios_base::beg);
        return result;
    }

    template<typename T>
    inline T peekData(size_t offset)
    {
        auto oldOffset = _stream.tellg();
        T result = getData<T>(offset);
		_stream.seekg(oldOffset, std::ios_base::beg);
        return result;
    }

	inline void goTo(size_t offset)
	{
		_stream.seekg(offset, std::ios_base::beg);
	}

	inline void goToE(size_t offset)
	{
		_stream.seekg(offset, std::ios_base::end);
	}

	inline void ignore(size_t bytes)
	{
		_stream.ignore(bytes);
	}

	std::basic_istream<CT>& base() { return _stream; }
};

#endif // INPUTBINARYSTREAM_H
