## generate GCov report
* configure, build and run tests with CMake using `GCov` variant
* run `lcov -c -d build/code/transaction/test/CMakeFiles/test_direct_registry.dir/ -d build/code/transaction/CMakeFiles/transaction.dir/ -o build/gcov.info`
* run `genhtml -o build/gcov_report build/gcov.info`
* open `build/gcov_report/index.html` with a browser