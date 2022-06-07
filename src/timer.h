#include <chrono>

namespace utils {

class Timer {
 public:
    void Start() {
        start_time_ = std::chrono::system_clock::now();
    }

    double elapsedMilliseconds() {
        std::chrono::time_point<std::chrono::system_clock> end_time = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time_).count();
    }

    double elapsedSecconds() {
        return elapsedMilliseconds() / 1000.0;
    }
 private:
    std::chrono::time_point<std::chrono::system_clock> start_time_;
};

} // namespace utils
