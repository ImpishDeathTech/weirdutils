/*
 * data.cxx
 *
 * BSD 3-Clause License
 * 
 * Copyright (c) 2022, Christopher Stephen Rafuse
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <weirdutils/data.hxx>

#include <cctype>
#include <fstream>
#include <iomanip>

namespace weird {
// hexdump function: dumps binary bytecode in a nice, formatted text block
	void hexshit(databuffer_t value) {
		std::stringstream ss;
		std::string       printable;

		std::int32_t      indent    = 1,
				  relPos    = 0,
				  nulls     = 0,
				  zeros     = 0,
		           	  outLenA   = 0,
		           	  outLenB   = 0;

		std::uint8_t *tempBuf, 
		              tempChar;

		bool          isEmpty   = false;
		bytebuffer_t  buffer    = { (std::uint8_t*)(value.data), value.size };

		while (buffer.size > 0) {
			tempBuf   = buffer.data;
			outLenA   = buffer.size;
			printable = " [";

			if (outLenA > 16)
				outLenA = 16;

			ss << "{ " << std::setw(8) << std::setfill('0') << std::hex << tempBuf - buffer.data << " } ";
			outLenB = outLenA;

			for (relPos = 0, nulls = 0, zeros = 0; outLenB; outLenB--) {
				tempChar = *tempBuf++;


				if (tempChar == 0)
					nulls++;

				if (tempChar == '0')
					zeros++;

				ss << ' ' << std::setw(2) << std::hex << (std::uint16_t)tempChar;

				if (!isprint(tempChar))
					tempChar = '.';

				if (!(++relPos & 3))
					ss << ' ';

				printable += tempChar;	
			}

			while (ss.str().size() < 65)
				ss << ' ';

			if (nulls != 16 && zeros != 16) {
				ss << std::setfill(' ') << printable << std::setw(20 - printable.size()) << "]\n";
				std::cout << ss.str();
				isEmpty = false;
			}
			else if (!isEmpty) {
				std::cout << "{ !NULBLK! }                                                      [                ]\n";
				isEmpty = true;
			}

			ss.str("");

			buffer.data += outLenA;
			buffer.size -= outLenA;	
		}
	}
	

	void scramble(charbuffer_t& buffer_, std::vector<std::int16_t> algorithem_) {
		bytebuffer_t bytes = {
			reinterpret_cast<std::uint8_t*>(const_cast<char*>(buffer_.data)),
			0
		};

		for (auto i = algorithem_.begin(); i != algorithem_.end(); ++i) {
			for (bytes.size = 0; bytes.size < buffer_.size; bytes.size++) {
				bytes.data[bytes.size] += (*i) % 255;
			}
		}
	}
}

