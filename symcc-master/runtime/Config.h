// 主要做配置文件操作

#ifndef CONFIG_H
#define CONFIG_H

#include <string>

struct Config {
  /// Should we allow symbolic data in the program?
  bool fullyConcrete = false;

  /// The directory for storing new outputs.
  std::string outputDir = "/tmp/output";

  /// The input file, if any.
  std::string inputFile;  // 输入文件

  /// The file to log constraint solving information to.
  std::string logFile = "";

  /// Do we prune expressions on hot paths?
  bool pruning = false;

  /// The AFL coverage map to initialize with.
  ///
  /// Specifying a file name here allows us to track already covered program
  /// locations across multiple program executions.
  std::string aflCoverageMap = "";  // 存储AFL获取到的代码覆盖的细节

  /// The garbage collection threshold.
  ///
  /// We will start collecting unused symbolic expressions if the total number
  /// of allocated expressions in the target program exceeds this number.
  ///
  /// Collecting too often hurts performance, whereas delaying garbage
  /// collection for too long might make us run out of memory. The goal of this
  /// empirically determined constant is to keep peek memory consumption below
  /// 2GB on most workloads because requiring that amount of memory per core
  /// participating in the analysis seems reasonable.
  size_t garbageCollectionThreshold = 5'000'000;
};

/// The global configuration object.
///
/// It should be initialized once before we start executing the program and
/// never changed afterwards.
extern Config g_config;

/// Populate g_config from the environment.
///
/// The function will throw std::runtime_error if the value of an environment
/// variable used for configuration cannot be interpreted.
void loadConfig();

#endif
