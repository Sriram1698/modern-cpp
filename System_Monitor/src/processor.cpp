#include "processor.h"

#include <iostream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::vector;

Processor::Processor()
    : prev_active_(LinuxParser::ActiveJiffies()),
      prev_idle_(LinuxParser::IdleJiffies()) {}

float Processor::Utilization() {
  long active = LinuxParser::ActiveJiffies();
  long idle = LinuxParser::IdleJiffies();

  long prev_total = prev_active_ + prev_idle_;
  long total = active + idle;

  long totald = total - prev_total;
  long idled = idle - prev_idle_;

  prev_active_ = active;
  prev_idle_ = idle;

  return (totald == 0.) ? 0. : (float(totald - idled) / float(totald));;
}