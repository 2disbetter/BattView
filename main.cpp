/*
Battview main. Simple and efficient.
Copyright: Matthew Mueller
*/

#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <fstream>
#include <string>
#include <filesystem>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // check the battery capacity file
    std::string bat_capacity_path;
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator("/sys/class/power_supply")) {
        std::string dir_name = entry.path().filename().string();
        if (dir_name.find("BAT") == 0) {
            bat_capacity_path = entry.path() / "capacity";
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

    std::string text = "Battery: " + (percent != -1 ? std::to_string(percent) + "%" : "Not found");

    QLabel label(QString::fromStdString(text));
    label.setFont(QApplication::font());
    label.setAlignment(Qt::AlignCenter);
    label.setFixedSize(150, 50);  // Make it a small window
    label.show();

    // Close after 2 seconds
    QTimer::singleShot(2000, &app, &QApplication::quit);

    return app.exec();
}