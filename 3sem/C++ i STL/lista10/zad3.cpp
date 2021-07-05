#include<iostream>
#include <filesystem>
#include <chrono>
#include<ctime>
namespace fs = std::filesystem;

template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
              + system_clock::now());
    return system_clock::to_time_t(sctp);
}

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        fs::path path(argv[1]);
        if (fs::exists(argv[1])) {
            std::cout << fs::canonical(path) << "\n";
            if (!fs::is_directory(path))
                std::cout << fs::file_size(path) << "\n";

            auto time = fs::last_write_time(path);
            //std::time_t ctime = decltype(time)::clock::to_time_t(time);
            std::time_t ctime = to_time_t(time);
            std::tm tm = *std::localtime(&ctime);
            std::wstringstream wss;
            wss << std::put_time(&tm, L"%F %T");
            std::wcout << wss.str() << std::endl;
        }
    }
    return 0;
}
//compile g++ -std=c++17 zad3.cpp -o zad3