// Copyright 2014 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Delay line.

#ifndef STMLIB_DSP_DELAY_LINE_H_
#define STMLIB_DSP_DELAY_LINE_H_

#include "stmlib/stmlib.h"

#include <algorithm>

namespace stmlib {

template<typename T, int max_delay>
class DelayLine {
 public:
  DelayLine() { }
  ~DelayLine() { }
  
  void Init() {
    std::fill(&line_[0], &line_[max_delay], T(0));
    delay_ = 1;
    write_ptr_ = 0;
  }
  
  inline void set_delay(size_t delay) {
    while (delay >= max_delay) delay >>= 1;
    delay_ = delay;
  }

  inline void Write(const T& sample) {
    write_ptr_ = (write_ptr_ + 1) % max_delay;
    line_[write_ptr_] = sample;
  }
  
  inline const T& Read() const {
    return line_[(write_ptr_ - delay_ + max_delay) % max_delay];
  }
  
 private:
  size_t write_ptr_;
  size_t delay_;
  T line_[max_delay];
  
  DISALLOW_COPY_AND_ASSIGN(DelayLine);
};

}  // namespace stmlib

#endif  // STMLIB_DSP_DELAY_LINE_H_
