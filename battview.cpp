/*
Battview main. Simple and efficient.
Copyright: Matthew Mueller
Modified to include CPU temperature and fan RPM using ectool.
*/

#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdio>
#include <sstream>

std::string get_command_output(const std::string& cmd) {
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Check the battery capacity and status files
    std::string bat_capacity_path;
    std::string bat_status_path;
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator("/sys/class/power_supply")) {
        std::string dir_name = entry.path().filename().string();
        if (dir_name.find("BAT") == 0) {
            bat_capacity_path = entry.path() / "capacity";
            bat_status_path = entry.path() / "status";
            break;
        }
    }

    // Read battery percentage
    int percent = 0;
    if (!bat_capacity_path.empty()) {
        std::ifstream bat_file(bat_capacity_path);
        bat_file >> percent;
    } else {
        // Fallback if no battery found
        percent = -1;
    }

    // Read battery status
    std::string status = "Unknown";
    if (!bat_status_path.empty()) {
        std::ifstream status_file(bat_status_path);
        std::getline(status_file, status);  // Read the full line for status
    }

    // Construct display text
    std::string text;
    if (percent != -1) {
        text = "Battery: " + std::to_string(percent) + "% (" + status + ")";
    } else {
        text = "Battery not found";
    }

    // Get CPU temperature (assuming sensor 1 is CPU, in Kelvin)
    std::string temps_output = get_command_output("ectool temps 1");
    int cpu_temp_c = -1;
    size_t pos = temps_output.find("= ");
    if (pos != std::string::npos) {
        std::stringstream ss(temps_output.substr(pos + 1));
        int temp_k;
        if (ss >> temp_k) {
            cpu_temp_c = temp_k;
        }
    }
    text += "\nCPU Temp: ";
    if (cpu_temp_c != -1) {
        text += std::to_string(cpu_temp_c) + " C";
    } else {
        text += "N/A";
    }

    // Get fan RPM
    std::string fan_output = get_command_output("ectool pwmgetfanrpm");
    int fan_rpm = -1;
    size_t rpm_pos = fan_output.find("RPM: ");
    if (rpm_pos != std::string::npos) {
        std::stringstream ss(fan_output.substr(rpm_pos + 5));
        ss >> fan_rpm;
    }
    text += "\nFan RPM: ";
    if (fan_rpm != -1) {
        text += std::to_string(fan_rpm);
    } else {
        text += "N/A";
    }

    QLabel label(QString::fromStdString(text));
    label.setFont(QApplication::font());
    label.setAlignment(Qt::AlignCenter);
    label.setWordWrap(true);
    label.setFixedSize(200, 100);  // Adjusted size for additional info
    label.show();

    // Close after 2 seconds
    QTimer::singleShot(2000, &app, &QApplication::quit);

    return app.exec();
}
