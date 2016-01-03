#ifndef LOG_H
#define LOG_H

#include <iostream>

class Log {

	public:
		enum class Level {LOG, WARNING, ERROR};
		template <typename T>
		static void write(const T& value)
		{
		    std::cout << value << std::endl;
		}

		template <typename U, typename... T>
		static void write(Level level, const U& head, const T&... tail)
		{
			switch(level) {
				case Level::LOG:
					std::cout << "[LOG] ";
					break;

				case Level::WARNING:
					std::cout << "[WARNING] ";
					break;

				case Level::ERROR:
					std::cout << "[ERROR] ";
					break;
			}
		    std::cout << head;
		    write(tail...);
		}

		template <typename U, typename... T>
		static void write(const U& head, const T&... tail)
		{
			write(Level::LOG, head, tail...);
		}


	private:

};

#endif