#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
# include <chrono>

#include <QFile>
#include <QString>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include <QProcess>

#include "src/for_each_permutation.h"
#include "../../../FieldOpt/FieldOpt/Utilities/filehandling.hpp"
#include "../../../FieldOpt/FieldOpt/Utilities/time.hpp"

using namespace std;

// ============================================================
class func_at_each_perm
{
  unsigned len;
  std::uint64_t count;
  QString file_path;

 public:

  explicit func_at_each_perm(unsigned l, QString file_path_) : len(l), count(0) {
      file_path = file_path_;
      Utilities::FileHandling::CreateFile(file_path, true);
  }

  operator std::uint64_t() const {return count;}

  // called for each permutation
  template <class It> bool operator()(It first, It last)
  {
      ++count;
      QString str;

      if (first != last)
      {
          str = QString::number(*first);
          for (++first; first != last; ++first)
          {
              str = str + " " + QString::number(*first);
          }
      }
      // \todo Collect all data into one str, then call WriteLineToFile
      // only once. ?? >> This can only be done after the main function
      // has stopped calling iter_func.operator(), which means we may
      // have to implement at the template level of the main function.
      // Whether to do this depends on whether there is a performance
      // gain from avoiding setting up the file pointer and printing to
      // disc for each combination, in compasison to storing all
      // combinations into one large string, and only print to disc
      // at the end of this process
      Utilities::FileHandling::WriteLineToFile(str, file_path);
      return false;
  }
};

// ============================================================
QString getSetFilename(const int n, int Z){

    QString n_str, Z_str;
    n_str = QString("n%1").arg(n, 3, 10, QChar('0'));

    if (Z < 1e3){
        Z_str = QString("-Z%1").arg(Z, 6, 10, QChar('0'));
    }else if(Z > 1e3 && Z < 1e6){
        Z_str = QString("-Z%1").arg(Z, 6, 10, QChar('0'));
    }else{
        Z_str = QString("-Z%1").arg(Z, 'E', QChar('0'));
    }

    QString file_path = "../combinations/" + n_str + "-C-" + Z_str + ".cSet";

    return file_path;
}

// ============================================================
std::vector<double> get_elapsed_time(QDateTime t_start){

    auto t_duration_ms = (double)time_since_milliseconds(t_start);
    std::vector<double> time_vector;

    time_vector.push_back(t_duration_ms); // milliseconds
    time_vector.push_back(t_duration_ms/1000); // seconds
    time_vector.push_back(t_duration_ms/1000/60); // minutes
    time_vector.push_back(t_duration_ms/1000/60/60); // hours
    time_vector.push_back(t_duration_ms/1000/60/60/24); // days

    return time_vector;
}

// ============================================================
void print_to_log(QString log_file, QDateTime t_start){

    // --------------------------------------------------------
    // date
    QString log_str;
    log_str = t_start.toString("dd.mm.yyyy HH:MM:SS") + "\n";

    // --------------------------------------------------------
    // cpu info
    QString cpu_str = "cat /proc/cpuinfo | grep "
        "\"model name\" -m1 | awk -F \":\" '{print $2}' ";

    QProcess process;
    process.start("bash", QStringList() << "-c" << cpu_str);

    process.waitForFinished(10);

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    // debug
    // cout << "stdout: " << stdout.toStdString() << endl;
    // cout << "stderr: " << stderr.toStdString() << endl;

    if (stdout.at(0) == QChar::fromLatin1(' '));
        stdout = stdout.mid(1);
    log_str = log_str + stdout + "\n";

    // --------------------------------------------------------
    // print to log file
    Utilities::FileHandling::WriteLineToFile(log_str, log_file);
}

// ============================================================
int main() {

    // --------------------------------------------------------
    // Select combination attributes
    const int r = 2;   // selection
    const int n = 9;   // sampling grid, 1D
    const int N = pow(n,2.0); // sampling grid, 2D
    const int Z = (N-1)*N/2; // # of possible combinations (w/reverse)

    std::vector<int> v(N);
    std::iota(v.begin(), v.end(), 0);

    auto file_path = getSetFilename(n,Z);

    // ------------------------------------------------------------
    // Print to log
    QString log_file = "../combinations/runtimes";
    std::cout << "selection, r = " << r << std::endl
              << "sampling grid (1D), n = " << n << std::endl
              << "sampling grid (2D), N = n^2 = " << N << std::endl
              << "# of combinations (reverse), Z = (N-1)*N/2 = " << Z << std::endl;

    auto t_start = QDateTime::currentDateTime();
    print_to_log(log_file, t_start);

    // ------------------------------------------------------------
    // Find combinations

    std::uint64_t count =
        for_each_reversible_permutation(v.begin(),
                                        v.begin() + r,
                                        v.end(),
                                        func_at_each_perm(v.size(),file_path));

    auto elapsed_time = get_elapsed_time(t_start);

    // ------------------------------------------------------------
    // Sanity check
    assert(count == count_each_reversible_permutation(v.begin(),
                                                      v.begin() + r,
                                                      v.end()));

    // ------------------------------------------------------------
    // Summary
    std::cout << "Found " << count << " permutations of " << v.size()
              << " objects taken " << r << " at a time.\n\n";

    std::cout << "Elapsed time: \n"
              << elapsed_time[0] << " milliseconds\n"
              << elapsed_time[1] << " seconds\n"
              << elapsed_time[2] << " minutes\n"
              << elapsed_time[3] << " hours\n"
              << elapsed_time[4] << " days\n";

    return 0;
}