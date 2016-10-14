#ifndef INTERLEAVER_USER_HPP
#define INTERLEAVER_USER_HPP

#include <fstream>
#include <algorithm>

#include "Tools/Display/bash_tools.h"

#include "../Interleaver.hpp"

template <typename T>
class Interleaver_user : public Interleaver<T>
{
private:
	const std::string filename;

public:
	Interleaver_user(int size, const std::string filename, const std::string name = "Interleaver_user")
	: Interleaver<T>(size, 1, name), filename(filename) { gen_lookup_tables(); }

protected:
	void gen_lookup_tables()
	{
		std::ifstream file(filename.c_str(), std::ios::in);

		if (file.is_open())
		{
			long long read;

			file >> read;
			if (read == (long long)this->pi.size())
			{
				for (auto i = 0; i < (int)this->pi.size(); i++)
				{
					file >> read;
					if (read >= 0 && read < (long long)this->pi.size())
					{
						auto found = false;
						auto j = 0;
						while(j < i && !found)
						{
							if (this->pi[j] == read)
								found = true;
							j++;
						}

						if (!found)
							this->pi[i] = (T)read;
						else
						{
							std::cerr << bold_red("(EE) The interleaver value is wrong, it already exists elsewhere")
							          << bold_red(" (read: ") << bold_red(std::to_string(read))
							          << bold_red("), exiting.") << std::endl;
							file.close();
							std::exit(-1);
						}
					}
					else
					{
						std::cerr << bold_red("(EE) The interleaver value is wrong (read: ")
						          << bold_red(std::to_string(read)) << bold_red(", required: < ")
						          << bold_red(std::to_string(this->pi.size())) << bold_red("), exiting.") << std::endl;
						file.close();
						std::exit(-1);
					}
				}

				for (auto i = 0; i < (int)this->pi_inv.size(); i++)
					this->pi_inv[this->pi[i]] = i;
			}
			else
			{
				std::cerr << bold_red("(EE) The interleaver size is wrong (read: ") << bold_red(std::to_string(read))
				          << bold_red(", required: ") << bold_red(std::to_string(this->pi.size()))
				          << bold_red("), exiting.") << std::endl;
				file.close();
				std::exit(-1);
			}

			file.close();
		}
		else
		{
			std::cerr << bold_red("(EE) Can't open \"") << bold_red(filename) << bold_red("\" file, exiting.")
			          << std::endl;
			std::exit(-1);
		}
	}
};

#endif	/* INTERLEAVER_USER_HPP */

