#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(const int pid)
    : pid_(pid),
      u_name_(LinuxParser::User(pid)),
      cmd_(LinuxParser::Command(pid)) {}

// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  int up_time = LinuxParser::UpTime();
  int process_up_time = LinuxParser::UpTime(pid_);

  int active_time = LinuxParser::ActiveJiffies(pid_);
  int total_time = up_time - process_up_time;

  utilization_ = float(active_time) / float(total_time);
  return utilization_;
}

// TODO: Return the command that generated this process
string Process::Command() { return cmd_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return u_name_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime() - LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator>(Process const& a) const {
  return this->utilization_ > a.utilization_;
}