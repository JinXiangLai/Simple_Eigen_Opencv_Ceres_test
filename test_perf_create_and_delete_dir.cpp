#include <filesystem>
#include <iostream>
#include <string>

using namespace std;

int main() {
    const string folder_name("test_perf_folder");
    if (!filesystem::exists(folder_name)) {
        cout << "create: " << folder_name << endl;
        filesystem::create_directories(folder_name);
    }
    if (filesystem::exists(folder_name)) {
        filesystem::remove_all(folder_name);
        cout << "delete: " << folder_name << endl;
    }
    return 0;
}